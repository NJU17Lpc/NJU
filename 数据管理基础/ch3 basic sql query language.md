# ch3 basic sql query language

## **create a table** for CAP database

- create customers

`CREATE TABLE customers(`

`	cid CHAR(4) NOT NULL`,	//不能出现空值

`cname VARCHAR(13),`

`city VARCHAR(20),`

`discnt REAL,` //real为四个字节的实数，相当于float in C

`PRIMARY KEY(cid));`

- 其他table的语句，示例

`percent SMALLINT`

`price DOUBLE PRECISION`

## **select statement** 翻译之前学习的关系代数

- ( R **where** Condition )[A1, A2, A3]

`SELECT A1, A2, A3`

`FROM R`

`WHERE Condition`

- ( ( R1xR2xR3 ) where Condition ) [A1, A2, A3] 这种笛卡尔积的表示，给我别样的感受哈哈

`SELECT A1, A2, A3`

`FROM R1, R2, R3`

`WHERE Condition`

- JOIN

  - Head(R) = { A1, A2, A3, B1, B2, B3 }
  - Head(S) = { B1, B2, B3, C1, C2, C3 }
  - ( ( R join S ) where Condition ) [A1, A2, A3]

  `SELECT A1, A2, A3`

  `FROM R, S`

  `WHERE Condition and`

  `R.B1 = S.B1 and R.B2 = S.B2 and R.B3 = S.B3`

- Theta-Join我没看懂在干嘛

- 例子

  - Find aid and names of agents that are based in New York

  `SELECT aid, aname`

  `FROM agents`

  `WHERE city="New York";`

  - Display all values of customers in table CUSTOMERS

  `SELECT *`

  `FROM customers;`

  - Select product ids of products for which orders are placed

  `SELECT distinct pid FROM orders;`

  如果用这个 `SELECT pid FROM orders;` 就会出现大量重复值

  - Retrieve all ( cname, aname ) pairs where the customers places an order through the agent

  `SELECT distinct cname, aname`

  `FROM customers, orders, agents`

  `WHERE customers.cid = orders.cid and orders.aid = agents.aid;`

  - Retrieve all ( cname, aname ) pairs where the customers places an order through the agent (题目和上一题一样，但这里试用一下别名alias)

  `SELECT distinct cname, aname`

  `FROM customers c, order o, agents a`

  `WHERE c.cid = o.cid and o.aid = a.aid;`

  - 再用一条题体会一下，别名的简洁性和明确性

  `SELECT ordno, dollars, o.qty*p.price*(1-c.discnt*0.01) as mydollars`

  `FROM customers c, orders o, products p`

  `WHERE c.cid = o.cid and o.pid = p.pid;`

  - List all pairs of customer cids based in the same city

  `SELECT c1.cid, c2.cid`

  `FROM customers c1, customers c2`

  `WHERE c1.city = c2.city and c1.cid < c2.cid;`

  - <u>**Find pids of products ordered by at least two customers**</u>

  `SELECT distinct pid`

  `FROM order x1, order x2`

  `WHERE x1.pid = x2.pid and x1.cid < x2.cid;`

  或者

  `SELECT distinct pid`

  `FROM orders x1, orders x2`

  `WHERE x1.pid = x2.pid and x1.cid <> x2.cid;`

  - **<u>get cids and names of customers ordering a product for which an order is placed by agent a06(这一条我很奇怪为什么用两个orders表)</u>**

  `SELECT distinct c.cid, c.name`

  `FROM orders o1, orders o2, customers c`

  `WHERE o1.aid = 'a06' and o1.pid = o2.pid and o2.cid = c.cid;`

  我觉得我自己这样写就行了

  `SELECT distinct c.cid, c.name`

  `FROM orders o, customers c`

  `WHERE o.aid = 'a06' and o.cid = c.cid;`然后我发现不太对劲

  我想知道WHERE语句对顺序的控制，and两边是同时进行的，还是从前往后的

## Subqueries

- queries can be nested
- 有一些functions: 比如AVG
- 例子

`SELECT cid, cname, discnt`

`FROM customers`

`WHERE discnt<(SELECT AVG(discnt) FROM customers);`

- The IN Predicate

  - Retrieve cids of customers who place orders with agents in Duluth or Dallas

    - 第一种SQL，SLOW

    `select distinct cid`

    `from orders o, agents a`

    `where a.aid = o.aid and `

    `			(a.city = 'Duluth' or a.city = 'Dallas');`

    - 第二种SQL，FAST

    `select distinct cid from orders`

    `where aid IN (`

    `select aid from agents`

    `where city = 'Duluth' or city = 'Dallas'); `

    - 我看第一种无脑笛卡尔积，遍历要做大约2n-3n次运算
    - 第二种先筛选范围，遍历为n-2n次运算，前面的aid IN需要的次数就很少了

  - Get all information concerning agents based in Duluth or Dallas

    `SELECT *`

    `FROM agents`

    `WHERE city IN {'Duluth', 'Dallas'}`

  - Get the names and discounts of all customers who place orders through agents in Duluth or Dallas这个太长了，我直接截图了

    ![](E:\NJU的各种\NJU\数据管理基础\notes\Resources\例题1.PNG)

  - find the names of customers who order product p05
  
    - sql 1 这是多表联接查询
  
    `SELECT distinct cname` 
  
    `FROM customers c, orders o`
  
    `WHERE c.cid=o.cid and o.pid='p05'`
  
    - sql 2  这是相关子查询
  
    `SELECT distinct cname`
  
    `FROM customers c`
  
    `WHERE 'p05' IN ( select pid from orders o where o.cid=c.cid )`
  
    - sql 3  这是独立子查询
  
    `SELECT distinct cname`
  
    `FROM customers c`
  
    `WHERE cid IN (select cid from orders o where o.pid='p05')`
  
  - Find ordno values for all orders placed by customers in Duluth through agents in New York
  
    `SELECT ordno`
  
    `FROM orders`
  
    `WHERE  ( cid, aid ) IN ( SELECT cid,aid from customers c, agents a`
  
    `where c.city='Duluth' and a.city='New York' )`
  
- Quantified Comparison : **<u>量化比较</u>**

  - **{ SOME|ANY|ALL }**
  - **IN is SOME**
  - **NOT IN is <>ALL**
  - find aid values of agents with a minimum percent commission

  `SELECT aid FROM agents`

  `WHERE percent<=ALL( select percent from agents )`

  - find all customers who have the same discount as that of any of the customers in Dallas or Boston

  `SELECT cid, cname`

  `FROM customers`

  `WHERE discnt = SOME ( select discnt from customers where city='Dallas' or city='Boston' )`

  - get cid values of customers with discnt smaller smaller than those of any customers who live in Duluth (**<u>用ALL不是用ANY</u>**)

  `SELECT cid, cname FROM customers`

  `WHERE discnt < ALL( select discnt from customers where city='Duluth' )`

- The EXISTS predicate

  - EXISTS is true **<u>if and only if</u>** the subquery returns a non-empty set

  - NOT EXISTS is true **<u>if and only if</u>** the subquery returns an empty set
  - retrieve all customer names where the customer places an order through agent a05

  ```mysql
  `SELECT distinct c.cnames`
  `FROM customers c`
  `WHERE EXISTS ( SELECT * FROM orders x where c.cid=x.cid and x.aid='a05' )`
  ```

  - get cid values of customers who order both products p01 and p07

  ```mysql
  SELECT distinct x.cid
  
  FROM orders x
  
  WHERE pid = 'p01' and EXIST ( SELECT * FROM orders y
  
  Where y.cid=x.cid and y.pid='p07' )
  
  
  ```


从下面开始都放在一个代码块里面

```mysql
##retrieve all customer names where the customer does not place an order through agent a05
#sql 1
#NOT EXIST can equal to 'minus' in relational algebra 
Select distinct c.cname From customer c 
Where NOT EXIST (Select * From orders x
                Where c.cid=x.cid and x.aid='a05')               
#sql 2
Select distinct c.cname From customers c
Where c.cid NOT IN (Select x.cid From orders x
                   Where x.aid='a05')
#sql 3
Select distinct c.cname From customers c
Where c.cid <> All (Select x.cid From orderes x Where x.aid='a05')

### BETWEEN Predicate
## Find the values of customers with discnt between 6 and 10
#sql 1
Select * From customers WHERE discnt BETWEEN 6 AND 10
#sql 2
Select * From customers WHERE discnt>=6 AND discnt<=10

### IS NULL Predicate
## Find the values of customers with discnt is null
SELECT * FROM customers WHERE discnt is null
## Find the values of customers with discnt is not null
SELECT * FROM customers WHERE discnt is not null


### LIKE Predicate
### colname [NOT] LIKE val1 [ESCAPE val2]  # ESCAPE指示转义字符
### '_'指示任意single character
### '%'指示any sequence of 0 or more characters
## Retrieve all data about customers whose cname begins with the letter 'A'
Select * From customers Where cname LIKE 'A%'

## Retrieve cid values of customers whose cname does not have a third letter equal to '%'
Select cid From customers Where cname NOT LIKE '_ _\%%' ESCAPE '\'
'\%'代表%自己，第二个%是通配符
```

```mysql
## Retrieve cid values of customers whose cname begins "Tip_" and has an arbitrary number of characters following.
Select cid From customers Where cname LIKE 'Tip\_%' ESCAPE '\'
```

```mysql
## Retrieve cid values of customers whose cname starts with the sequence "ab\"
Select * From customers Where cname LIKE 'ab\%' # not true
Select * From customers Where cname LIKE 'ab\\%' ESCAPE '\' #true
```

- Examples of Subqueries (PPT 77页)

```mysql
# exp 3.4.9
# Find cid values of customers with discnt smaller than those of any customers who live in Duluth
######### 这种东西必须要使用嵌套子查询，不然无法表示该查询请求
Select cid FROM customers WHERE discnt < ALL(
					SELECT discnt
					FROM customers
					WHERE city = 'Duluth')
# can we do this with (not) exists predicate?: yes
# can we do this without a subquery?: no
# 改用not exist
Select c1.cid FROM customers c1
WHERE NOT EXIST ( //c1中不存在任何能比c2中的任意discnt大的值
	SELECT * FROM customers c2
	WHERE c2.city = 'Duluth' and
		c2.discnt <= c1.discnt)


# Find cid values of customers with discnt smaller than a customer who live in Duluth
Select cid FROM customers WHERE discnt < SOME(
					SELECT discnt
					FROM customers
					WHERE city = 'Duluth')
# can we do this with (not) exists predicate?: yes
# can we do this without a subquery?: yes
# 改用Exist
SELECT c1.cid FROM customers c1
WHERE EXISTS(SELECT * FROM customers c2
            WHERE c2.city='Duluth' and c2.discnt>c1.discnt)
# 不用子查询，这种选择稍微烧脑一点，只需要有一组比较成立就纳入结果
SELECT c1.cid FROM customers c1, customers c2
WHERE c2.city = 'Duluth' and c2.discnt>c1.discnt 
```

```mysql
# exp 3.4.10
# Retrieve all customer names where the customer places an order through agent a05
# sql 1
SELECT distinct cname FROM customer c, orders o
WHERE c.cid=o.cid and o.cid='a05'
# sql 2
SELECT distinct cname FROM customers
WHERE cid IN 
(SELECT cid FROM orders WHERE aid='a05')
# sql 3
SELECT distinct cname FROM customers c
WHERE EXISTS(SELECT * FROM orders o WHERE o.cid=c.cid and o.aid='a05')
```

```mysql
################# example of subquery多样性
# exp 3.4.11
# get cid values of customers who order both products p01 and p07
SELECT distinct x.cid From orders x
WHERE pid='p01' and EXISTS (
	SELECT * FROM orders y
	WHERE y.cid=x.cid and y.pid='p07')
# 用IN独立子查询改写
SELECT distinct x.cid FROM orders x
WHERE pid='p01' and cid IN (
	SELECT y.cid FROM orders y
	WHERE y.pid='p07')
# 用IN相关子查询改写,这种不太会
SELECT distinct x.cid FROM orders x
WHERE pid='p01' and 'p07' IN (
	SELECT y.pid FROM orders y
	WHERE y.cid=x.cid)
# 直接多表连接查询
SELECT distinct x.cid FROM orders x, orders y
WHERE x.pid='p01' and y.pid='p07' and x.cid=y.cid
# 可以用intersect集合交，来表示
(SELECT cid FROM orders WHERE pid='p01')
INTERSECT
(SELECT cid FROM orders WHERE pid='p07')
```

```mysql
# exp 3.4.12 & 3.4.13
# Find all customer names where the customer does not place an order through agent a05
((C[cid]-(O where aid='a05')[cid]) join C)[cname]
# NOT IN可以替换为<>ALL，或者NOT EXISTS
SELECT cname FROM customers 
WHERE cid NOT IN (SELECT o.cid FROM o
                 WHERE o.aid='a05')
                 
# Find all cid, aid pairs where the customer does not place an order through the agent
SELECT cid, aid FROM customers c, agent a 
WHERE NOT EXISTS (
	SELECT * FROM orders o
	WHERE o.cid=c.cid and o.aid=a.aid)

SELECT cid, aid FROM customers c, agents a
WHERE (cid, aid) NOT IN (
	SELECT o.cid, o.aid FROM orders o)

# exp 3.4.14
# Find cids of all customers who don't place any order through agent a03
SELECT cid FROM customers WHERE cid NOT IN (
	SELECT o.cid FROM orders o WHERE o.aid='a03')
	
SELECT cid FROM customers c WHERE NOT EXISTS (
	SELECT * FROM orders o
	WHERE o.cid=c.cid and o.aid='a03')
	
# exp 3.4.15 重要的一题
# Retrieve the city names containing customers who order product p01
# 使用表连接查询
SELECT city FROM customers c, orders o
WHERE c.cid=o.cid and o.pid='p01'
# IN+独立子查询
SELECT city FROM customers WHERE cid IN (
	SELECT cid FROM orders
	WHERE pid='p01')
# IN+相关子查询
SELECT city FROM customers c
WHERE 'p01' IN (SELECT o.pid FROM orders o
               WHERE o.cid=c.cid)
# EXISTS+相关子查询
SELECT city FROM customers c
WHERE EXISTS (SELECT * FROM orders o
             WHERE o.cid=c.cid and o.pid='p01')
# SOME+独立子查询 和where cid IN一个意思
SELECT city FROM customers
WHERE cid = SOME (SELECT cid FROM orders
                 WHERE pid='p01')
# SOME+相关子查询 和where 'pid' IN (SELECT o.pid ...)
SELECT city FROM customers c
WHERE 'p01' = SOME(SELECT o.pid FROM orders o
                  WHERE o.cid=c.cid)
```

```mysql
############## example of simple select statements
# exp 2.9.1
# get the names of customers who order at least one product priced at 0.50
(((P where price=0.50)[pid] join O) join C)[cname]
SELECT cname FROM products p, orders o, customers c
WHERE price=0.5 and p.pid=o.pid and o.cid=c.cid

# exp 2.9.3
# Retrieve customers who place orders only through agent a03
O[cid]-(O where aid <> 'a03')[cid]
SELECT 01.cid FROM orders o1
WHERE o1.cid NOT IN (SELECT o2.cid FROM orders o2
                    WHERE o2.aid<>'a03')
看到ppt 102
```











