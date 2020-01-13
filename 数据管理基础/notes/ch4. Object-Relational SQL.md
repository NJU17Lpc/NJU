# ch4. Object-Relational SQL

### 1. Object Types: The REF Object Reference

#### 1.1 定义新的数据类型

```mysql
#创建一个姓名(name_t)类型
CREATE TYPE name_t AS OBJECT(
	Iname varchar(30),
    fname varchar(30),
    mi char(1)
);
#创建一个‘文档’类型
CREATE TYPE Document AS OBJECT(
	name varchar(50),
    author varchar(30),
    date Date
);
#对比创建一个表
CREATE TABLE customers(
	cid char(4) not null,
    cname varchar(13),
    city varchar(20),
    discnt real,
    PRIMARY KEY(cid)
);
```

#### 1.2 对象类型的使用

- 可以用对象类型来**定义表**或**对象类型中的属性**

```mysql
#使用已有的对象类型来创建新的类型或者表
#4.2.3 这个name_t是之前已经定义好的对象类型，包含Iname\fname\mi
CREATE TYPE person_t AS OBJECT(
	ssno int,
    pname name_t,
    age int
);
#4.2.2 定义表中的属性
CREATE TABLE teachers(
	tid int,
    tname name_t,
    room int
);
#使用对象数据类型来直接创建一张表 4.2.4
CREATE TABLE people OF person_t(
	PRIMARY KEY(ssno)
);
```

#### 1.3 对象值的创建、查询与更新

```mysql
#对象值的创建
##对象构造函数
name_t('Einstein','Albert','E')
##返回对象取值的函数
value(...)
##使用对象类型name_t来定义teachers表中的属性tname
Insert into teachers values
(1234, name_t('Einstein','Albert','E'), 120);

#对象值的查询
##普通查询:查询位于123房间的教师的编号和姓名
SELECT t.tid,t.tname.fname,t.tname.lname
FROM teachers t
WHERE t.room=123

#对象值的更新
##修改元组中的对象属性值，直接把这个对象换了
UPDATE people p
SET p.pname=name_t('Gould','Ben',null)
WHERE ssn0 = 123456
##修改某个对象属性值的成员属性，对这个属性值操作
UPDATE people p
SET p.pname.mi='C'
WHERE ssno=123456
##修改整个元组
UPDATE people p
SET p=person_t(
	123456,
    name_t('Gould','Glen','A'),
    55
)
WHERE ssno=123456
```

#### 1.4 对象的引用类型

###### 1.4.1 定义类型之间的引用关系

```mysql
#定义基本的对象类型customer_t, agents_t, products_t
CREATE TYPE customer_t AS OBJECT(
	cid char(4),
    cname varchar(13),
    city varchar(20),
    discnt real
);
CREATE TYPE agent_t AS OBJECT(
	aid char(3),
    aname varchar(13),
    city varchar(20),
    percent smallint
);
CREATE TYPE product_t AS OBJECT(
	pid char(3),
    pname varchar(13),
    city varchar(20),
    quantity integer,
    price double precision
);
#定义类型之间的引用关系,使用REF分别指向三个不同的元组对象
CREATE TYPE order_t AS OBJECT(
	ordno int,
    month char(3),
    cid char(4),
    aid char(3)
    pid char(3),
    qty int,
	dollars double precision,
    ordcust ref customer_t,
    ordagent ref agent_t,
    ordprod ref product_t
);
```

###### 1.4.2 创建含有引用类型的关系表

```mysql
#使用对象类型创建基本关系表
CREATE TABLE customers OF customer_t (PRIMARY KEY(cid))
CREATE TABLE products OF product_t (PRIMARY KEY(pid))
CREATE TABLE agents OF agent_t (PRIMARY KEY(aid))
#创建含有引用类型的关系表
##使用scope for子句用来限制REF属性的取值范围
CREATE TABLE orders OF order_t(
	PRIMARY KEY(ordno),
    scope for(ordcust) is customers,
    scope for(ordagent) is agents,
    scope for(ordprod) is products
);
```

整个过程大概为

- 创建基本的类型create type xxx as object
  - 为他们分别设置表格table: create table xx of xxx
- 创建引用类型，其中用ref标注引用了哪些类型
  - 为改引用类型创建表格，其中对ref用scope for来限制表格范围

###### 1.4.3 引用关系查询

```mysql
#find pid values of products that have been ordered by at least two customers
SELECT distinct x1.pid 
from orders x1,orders x2
where x1.pid=x2.pid and x1.ordcust<x2.ordcust
```

###### 1.4.4 函数与谓词

- 函数
  - 获取对象的引用指针:REF(...)
  - 返回引用指针所指对象的值:DEREF(...)
- 两个谓词
  - IS DANGLING
  - IS NULL

```mysql
#REF(...):返回对象的引用指针
##retrieve all customer names where the customer does not place an order through agent a05
SELECT c.cname FROM customers c
WHERE NOT EXISTS(
	SELECT * FROM orders x
    WHERE x.ordcust=ref(c) and x.aid='a05'
);
##获得所有通过New York的代理商发订单的顾客的cid
SELECT c.cid FROM customers c
WHERE NOT EXISTS(
	SELECT * FROM agents a WHERE a.city='New York' and
    	NOT EXISTS(
        	SELECT * FROM orders x
            WHERE x.ordcust=ref(c) AND x.ordagent=ref(a)
        )
);

#DEREF(...):检索整个被引用对象，而不仅仅是该对象的引用指针
CREATE TYPE police_officer_t AS OBJECT(
	pol_person person_t,
    badge_number integer,
    partner ref police_officer_t
);
#IS DANGLING:判断所引用的元组对象是否存在，用于检查错误的对象引用指针
#也可以用is null才判断取值为空的REF属性
#但是is dangling不等于is null，它指的是useless
#如果o.ordcust为null或者dangling，那么o.ordcust.cname is null
##4.2.14
SELECT o.cid FROM orders o
WHERE o.ordcust IS DANGLING
#或者
SELECT o.cid FROM orders o
WHERE o.ordcust<>(SELECT ref(c) FROM customers c
	WHERE c.cid=o.cid
)
```

###### 1.4.5 类型的循环嵌套定义

```mysql
#对象类型不能嵌套定义，但是REF关系可以嵌套引用
######################################这段例子比较好
CREATE TYPE police_officer_t AS OBJECT(
	pol_person person_t,
    badge_number integer,
    partner ref police_officer_t
);
CREATE TABLE police_officers OF police_officer_t(
	PRIMARY KEY(badge_number),
    scope for(partner) is police_officers
);

#retrieve the last names of all police officers who have partners over sixty years of age.
SELECT p.pol_person.pname.lname
FROM police_officers p
WHERE p.partner.pol_person.age>60
```

###### 1.4.6 其他约束

- 有关REF定义的其他约束

  - 两张表之间的相互REF关系的定义

    - 部分创建第一个对象类，只给出类型名，不详细定义
    - 详细定义第二个对象类型，其中包含对第一个类型的引用属性
    - 再详细定义第一个对象类型
    - 根据创建好的对象类型创建关系表

  - 两个具有相互REF关系的表/类型的删除

    - 在删除类型之前需要先删除表
    - 在删除类型时需要采用强制删除的方式

  - REF属性数据的加载

    ```mysql
    #方法一:不管REF属性赋值，先赋值为NULL，然后UPDATE操作修改REF属性上的取值
    UPDATE orders o
    SET ordcust=(select ref(c) from customers c 
    	where c.cid=o.cid)
    #方法二:使用带有子查询的插入操作
    INSERT INTO police_officers
    FROM people p, police_officers p0
    WHERE p.ssno=123 and p0.badge_number=990
    ```

### 2. Collection Types:nested tables and varrays

#### 2.1 Table Types and Nested Tables

```mysql
#创建一个新的表类型table type
CREATE TYPE dependents_t AS TABLE OF person_t
#使用类型dependents_t来定义表employees中的属性并形成一个嵌套表(nested table)定义
CREATE TABLE employees(
	eid int,
    eperson person_t,
	dependents dependents_t,
    primary key(eid)
)
```

- 上面建表命令在数据库中创建**两个关系表**
  - employee: 存放职工记录
  - dependents_t: 存放所有职工的家属信息，称为嵌套表
  - 一条建表命令可以定义多个nested table

```mysql
#访问Nested table
##retrieve the nested table of all dependents of employee 101
SELECT dependents
FROM employees
WHERE eid=101
##retrieve the eids of employees with more than six dependents
SELECT eid
FROM employees e
WHERE 6<(SELECT count(*) FROM table(e.dependents))
```

- 上面使用了一个转换函数: table(...)


```mysql
#Oracle数据库没有提供nested table的相等比较运算，可以使用IN操作符来实现某些查询
##list eids of employees(there should be only one with a dependent having Social Security Number 345111)
SELECT eid
FROM employees e
WHERE 345111 IN (SELECT d.ssno FROM table(e.dependents) d);

#Oracle提供了单个对象的相等比较功能
##retrieve eids with dependents that have name given by name_t('Lukas','David','E')
SELECT eid FROM employees e
WHERE name_t('Lukas','David','E') IN
	(SELECT d.pname FROM table(e.dependents) d)
	
#Oracle不支持对嵌套表属性的统计查询，下面的是错的！！！！！！！！
SELECT count(e.dependents) FROM employees e WHERE e.eid=101

#表与自身的嵌套表的联接查询
##display all employee identifiers and their dependents' ssno values
SELECT e.eid, d.ssno
FROM employees e, table(e.dependents) d

#希望同时列出那些没有dependents职工的信息，那么可以用outer join来实现
SELECT e.eid, d.ssno
FROM employee.e, table(e.dependents)(+)d

#嵌套游标，使得查询结果的显示更清楚
##没有使用嵌套游标的版本
SELECT e.eid, d.ssno AS dep_sso
FROM employees e, table(e.dependents) d
WHERE d.age<16
##使用嵌套游标的版本
SELECT e.eid,
	cursor(SELECT d.ssno AS dep_ssno
    		FROM table(e.dependents) d
            WHERE d.age<16) dep_tab
    FROM employees e;
    
#实现对嵌套表属性的统计
##sql 1
SELECT eid,
	cursor(SELECT count(*) FROM TABLE(e.dependents))
	FROM employees e;
##sql 2
SELECT eid, (SELECT count(*) FROM TABLE(e.dependents))
FROM employees e;
##sql 3
SELECT eid, count(*)
FROM employees e, TABLE(e.dependents)
group by eid
```

#### 2.2 Array Types for VARRAYs

```mysql
CREATE TYPE extensions_t AS VARRAY(4) OF int

CREATE TABLE phonebook(
	phperson person_t,
    extensions extensions_t
);
#可以使用table(...)将也给VARRAY属性转换成一张嵌套表
```

|                | Nested table                                         | VARRAY                                     |
| -------------- | ---------------------------------------------------- | ------------------------------------------ |
| 成员排列次序   | 无序                                                 | 有序                                       |
| 成员最大数目   | 没有限制                                             | 确定的值                                   |
| 成员的存储组织 | 单独的存储表                                         | 直接存储在表中                             |
| 访问模式       | 可以对嵌套表属性insert，或者通过Update修改成员的取值 | 只能通过update语句修改整个VARRAY属性的取值 |

### 3. PL/SQL Procedures, UDFs, and Methods

```mysql
#创建对象类型point_t
CREATE TYPE point_t AS OBJECT(
	x int,
    y int
);
#创建带有成员函数的对象类型rectangle_t
CREATE TYPE rectangle_t AS OBJECT(
	pt1 point_t,
    pt2 point_t,
    member function inside(p point_t)
    	return int,
    member function area
    	return int
);
#成员函数的实现
create type body rectangle_t as
	member function area return int is
	begin
		return (self.pt2.x-self.pt1.x)*(self.pt2.y-self.pt2.y);
	end;
	...
end;

create type body rectangle_t as
	member function inside(p in point_t)
	return int is
	begin 
		if (p.x>=self.pt1.x) and (p.x<=self.pt2.x)
			and (p.y>=self.pt1.y) and (p.y<=self.pt2.y)
		then
			return 1;
		else
			return 0;
		end if;
	end;
end;
```

### Others

Exernal Functions and Packaged User-Defined Types(UDTs)

- External functions
  - 好像就是用其他程序语言实现的代码段，注册到数据库服务器后，就可以像PL/SQL定义的成员函数那样调用，使用功能
- Distinct types
  - U T是不同的type，需要用cast才能比较，需要type checking