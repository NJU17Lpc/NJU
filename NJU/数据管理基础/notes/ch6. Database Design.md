# chapter 6. Database Design

- database design指导我们
  - analyze an enterprise
  - list the data items for a database
  - decide how to place these data items columns in relational tables
- 比如设计一个学生课程数据库时
  - 考虑
    - 学生的attributes: sno, sname...
    - 课程的attributes: cno, cname...
    - 二者共同的attributes: grade
  - 把他们放进一个table: R(sno, sname, dept, sage...)
    - 这种SCG database感觉很不好，问题很多
  - 问题
    - 数据冗余: 只有一两项不同，却整个都存下来了: waste of disk space
    - 修改异常: waste of time; user容易出错
    - 删除异常: 有可能丢失一些信息:比如删除一个人的信息，顺带把课程信息删了，因为二者绑定在一起
    - 插入异常: 插入失败

### 6.1 Introduction to E-R concepts

###### 是什么

- **abstract** way to **describe** a database
- **more intuitive, less mechanical**

###### E-R model基本情况

- 三个基本的data classification objects
  - entity(实体)
    - 通常一个实体是映射到一个relational table上,代表一系列objects
    - 每一行是一个entity instance代表一个特定的object
  - attribute
    - 用来表述一个entity或者relationship
    - 一些特殊的attributes
      - **identifier: candidate key**候选键，要能**唯一确认**一个entity instance
        - 可以是**一个或者多个**attributes
      - **primary identifier主键**
      - descriptor: non-key attribute: Students.age
      - **composite** attribute:比如Students的一个属性student_name包括三个属性Iname\fname\midititial
      - **multi-valued** attribute: 一个人会有许多个hobbies
    - 作图
      - entity用矩形表示Employees
      - single-valued attribute用一条连线加一个⚪表示
      - composite attribute:组合表示
      - multi-valued...: 用double line
  - relationship
    - 将entities and attributes转换为relations的规则
      - rule 1
        - 一个entity映射到一个table上
        - single-valued映射到columns
        - composite attributes映射到多个simple columns
      - rule 2
        - multi-valued attribute映射到自己的table
          - 这个在ORDBMS不成立
    - E-R Diagrams中relationships的示例
      - instructors **teaches** course_sections
      - employees **works_on** projects
        - works_on是一个relationship，他还需要一个额外的attribute: percent表示这个employee实体花在project实体上时间的百分比
      - employees **manages** employees

### 6.2 E-R Diagrams的一些details

- cardinality
  - **<u>max-card(E, R)</u>** 每个点如果最多有1个出边，则结果为1；如果有点多个出边，结果N
    - 结果为1: E is said to have **<u>single-valued participation(单值参与)</u>** in the **relation R**
    - 结果为N: E is said to have **<u>multi-valued participation(多值参与)</u>** in the **relation R**
    - **<u>多对一联系中，多是有单值的这一方</u>**
  - min-card(E, R) 最少一个出边，结果为1；如果有点没有出边，则0
    - 结果为1: E is said to have **<u>mandatory participation(强制参与)</u>** in the **relation R**
    - 结果为0: ...**<u>optional participation(可选参与)</u>**
  - **<u>card(E, R) = (x, y)  if min-card(E, R)=x and max-card(E, R)=y</u>**
  - 这个(x, y)是要画在diagram里面的
- 一些特殊的relationship
  - one to one relationship: both entities都是single-valued
  - many to one:一个single一个multi
  - many to many:都是multi
- 将binary relationships转成relations
  - 这里是**<u>transformation rule 3: N-N relationships</u>**
    - 当E F加入了many-to-many binary relationship时，这个关系映射到一个representative table T里面，有这个T来做E F之间的转换
      - 转换的时候可以添加一些额外的信息来描述关系
    - 比如 
      - employees(eid)
      - projects(prid)
      - works_on(eid, pid, percent)
  - **<u>transformation rule 4</u>**
    - 当两个实体参与多对一的二元联系时，不能像多对多联系那样直接映射成表T
    - 我们假设F具有max-card(F, R)=1，则单值参与，即多对一中多的一方。那么从F转化的关系表T中应该包括从实体E转换出的关系表的主属性列，**T中每一行**都通过一个**外键**联系到**E的一个实例**
      - 我的理解是：多对一中，如果在一中引入多，会有很多麻烦；但在多中引入一，就好多了
    - **需要多一点题目参考**
  - transformation rule 5
    - 1-1 relationship
      - 可选参与(optional on one side)
        - 参与一对一二元联系时，双方都是可选的 min=0
        - （其实我没看懂这个）：§**Represent as two tables, foreign key column in one with mandatory participation: column defined to be NOT NULL.**
      - 强制参与(mandatory on both sides)
        - min=1
        - 这种情况最好把两个实体对应两个表合成一个，避免使用外键

### 6.3 其他E-R概念

###### 属性的基数

- card(A, E)=(x, y)来标记E-R图中**<u>属性-实体</u>**中的连接，来显示属性的基数
  - min-card(A, E)=x, max-card(A, E)=y
  - (0, ?)表示我不必指示not null，因为这个是可选的: midinitial
  - (1, ?)表示强制性的: id, name
  - (?, 1)表示单值参与: id
  - (?, N)表示多值: hobbies
  - 我感觉要注意分清**属性和实体的对应区分，一般实体是中心**

###### 弱实体weak entities

- 如果一个实体，他的所有实例，都通过一个联系R，依赖于另一个实体的实例而存在
- 那么这个实体叫弱实体，另一个叫强实体
- **<u>（讲道理我还是没看懂）</u>**

###### 泛化层次generalization hierarchies

- 思想是
  - 多个**<u>有公共属性</u>**的实体，可以泛化为一个更高层次的超类型实体
  - 或者，一个一般化实体，可以分解成低层次的子类型实体
- 整个目的是：将属性放在适当的层次，避免每个实例都要使用具有大量空值的公共实体
- 比如：将员工区分为经理和非经理，经理拥有单独的属性：开销报告，非经理有单独的属性。二者都属于员工，员工的id属性被二者共同拥有
  - **<u>这一点在对象关系数据库中用继承来表达</u>**
- 这玩意好像不需要深入看，一个简单的继承实现就是插入控制，我感觉这个方法挺zz
- 看到ppt68











