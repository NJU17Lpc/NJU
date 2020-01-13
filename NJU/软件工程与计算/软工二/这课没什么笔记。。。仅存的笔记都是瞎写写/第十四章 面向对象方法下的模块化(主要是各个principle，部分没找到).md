# 第十四章 面向对象方法下的模块化(主要是各个principle)

## 1、降低耦合的设计原则

### Global Variables Consider Harmful

### To be Explicit

### Do not Repeat

### Programming to Interface针对接口编程

- 考虑非继承的类与类的关系时
- 一方面要求**只访问对方的接口**（直接访问属性会导致公共耦合）
- 另一方面要**避免隐式访问**
- 如果能为每个类定义明确的契约（包括供接口和需接口），则可以满足上述要求
- **按照契约式设计理论**
  - 一个类的契约不仅包含**供接口和需接口**
  - 还要详细定义供接口与需接口的**前置条件、后置条件和不变式**

### The Law of Demeter迪米特法则

- you can play with yourself
- you can play with your own toys, but you can't take them apart
- you can play with toys that were given to you
- you can play with toys you've made yourself
- 中文
  - 每个单元对于其他的单元，只能拥有有限的知识，只是与当前单元紧密联系的单元
  - 每个单元只能和它的朋友交谈，不能与陌生单元交谈
  - 只和自己直接的朋友交谈
- 情形：一个对象O，有一个方法M，那么M只能调用下列对象的方法
  - O自己
  - M中的参数对象
  - 任何在M中创建的对象
  - O的成员变量
- 不可以出现a.b.method  这是隐式耦合

### Interface Segregation Principle(ISP)接口分离原则

- 将统一的接口匹配为**多个更独立的接口**
- 避免不必要的耦合，实现**接口最小化**
- 例如后端直接和UI来一套接口，就有很多不必要的耦合
  - 这时候来了许多VO就灵活了很多

### Liskov Substitution Principle(LSP) Liskov替换原则

只有存在基类和子类的关系时，LSP才存在

- 子类型必须能够替换掉基类型而起**相同的作用**
  - 如果违反了这个原则，那么父类和子类的耦合性一定比较强
  - （类和派生类一定要有相同的行为方式，一般可以用指定契约来考察）
- 在继承关系中，为了满足LSP，需要做到
  - 子类方法的前置条件必须与超类方法的前置条件相同，或者要求更少
  - 子类方法的后置条件必须与超类方法的后置条件相同，或者要求更多

### Favor Composition Over Inheritance 组合优于继承

- 只是为了复用，而不是为了组织类型差异的继承用法，往往是不符合LSP的
- 这种情况下的继承机制不应该使用，因为他不能带来减少耦合的效果
- 所以应该用组合代替继承，来**实现复用**
- **<u>再提醒，继承的时候一定要符合LSP，不要只为了代码复用而使用继承</u>**
  - 例如强行用passenger\agent来继承person，同时就继承了没必要的address
  - 这个时候可以给person组合一个role，让passenger\agent继承这个role

## 2、提高内聚的设计原则

### 集中信息与行为（记住这也是一个原则！！）

- 每个对象都会有数据信息和行为
- 这些信息和行为应该是有关联的
  - 信息联合起来能够支持行为的执行
  - 行为完成对这些信息的操纵

### Single Responsibility Principle(SRP) 单一职责原则

- 一个高内聚的类不仅要是信息内聚的，还应该是功能内聚的

- 信息与行为除了要集中之外，还要联合起来表达一个内聚的概念，而不是单纯的堆砌

- 以上就是SRP

- 补充：

  - 一个类有且只有一个职责

    - 所谓的一个职责，就是引起该类变化的一个原因

  - 如果一个类需要改变，改变他的理由永远只有一个

  - 例如把 Rectangle的draw()和area()分离开来

    

