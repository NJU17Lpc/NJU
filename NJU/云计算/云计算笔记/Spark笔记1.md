# Spark笔记1

#### 概览

- is a fast and general engine for large-scale data processing
- 快：mapreduce计算比hadoop快100x倍
- 易用：支持scala\java\python\R开发
- 功能强：spark sql/streaming/graphx/mllib
- 更加通用：
  - 适用于多种不同的集群管理框架standalone, YARN
  - 适用于多种不同的数据存储方法HDFS, MongoDB

#### 集群管理框架

- standalone mode: 原生集群管理功能：任务调度、资源分配等
- hadoop Yarn: hadoop第二个版本架构，将资源管理和任务管理剥离开
- Apache Mesos: 从分布式计算节点上抽象CPU, memory, storage等等resources给其他框架使用
- EC2：Amazon EC2云平台，提供了安装spark\shark\HDFS的集群，可以直接登录上去当成自己的集群

#### 存储方式

- HDFS
- **HBase: 基于HDFS的非关系型数据库(NoSQL)**
- Mongodb：基于分布式存储的数据库，介于关系型与非关系型数据库之间

- Cassendra: 基于列的分布式数据库，易于扩展、模式灵活、按照范围查询

#### MapReduce

- 为什么使用MR: 实现横向扩容
  - 自动并行和分布、容错性强、便于调度、检查、监控
- 什么时候用
  - 一个值计算依赖于前一个值
  - 需要同步处理共享数据
  - 几个操作依赖于其他操作
  - 基本计算处理器敏感

#### Hadoop vs Spark

- Hadoop是开源MapReduce的应用实现，是纯粹的MapReduce框架
  - 适合单趟计算，先map再reduce
- Spark不是专门的MapReduce框架，但支持MapReduce框架的功能
  - 可以是任意DAG，一个DAG可以包含多个阶段 vs Hadoop单趟
- 二者都为大数据处理提供：可读性、可伸缩性、分布式处理、并行化

#### Spark原理

##### 1、Driver程序

- driver是spark应用的入口程序
- 在集群模式下用户开发的Spark程序称为Driver



- 应用的执行位置：Local、集群
- 应用部署模式：
  - 集群模式：在网络远离计算节点的本机上提交Spark程序，到集群内部执行
  - 客户端模式：在靠近计算节点的机器上执行程序，可以选择客户端模式，就是通过spark提供的shell执行

##### 2、SparkContext

记住这个图：driver里面有sc，sc和cluster manager以及worker node都有交互，cluster和worker node也有交互，worker Node里面有Executor\cache\task

- 每个driver都有一个SC对象，实现CPU、内存等资源分配
- 程序启动后，SC会告诉集群管理器Cluster Manager在work Node上创建执行器
  - **程序代码会发送到对应的Worker Node上**
  - **SC分发任务Task到各个执行器**

##### 3、名词

- Application: 独立的Spark程序
- Master: Cluster Manager
- Worker
- 执行器Executor: Spark程序在对应计算节点上启动的专属线程，来执行Task
- Job: 一次RDD Action称为一个Job
- Stage: 介于Job和Task之间，是一个Task集合
- Task: 在执行器上执行的最小单元，例如 **某个计算节点**，对**一个RDD分区**，进行Transformation操作

##### 4、具体执行过程

这边内容其实优点复杂，但要背图，感觉可以考

[http://blog.csdn.net/thomas0yang/article/details/](http://blog.csdn.net/thomas0yang/article/details/50352261)[50352261](http://blog.csdn.net/thomas0yang/article/details/50352261) 

[http://](http://blog.csdn.net/u011007180/article/details/52388783)[blog.csdn.net/u011007180/article/details/52388783](http://blog.csdn.net/u011007180/article/details/52388783)

[http://blog.csdn.net/zero__](http://blog.csdn.net/zero__007/article/details/53121003)[007/article/details/53121003](http://blog.csdn.net/zero__007/article/details/53121003) 

- Driver程序
  - 客户端模式下，driver在本地，不会提交给master，而是直接提交任务
  - 集群模式下，首先driver会被提交给master，master首先找一个worker运行driver
    - driver程序节点不需要和管理器太多交互，而是与worker之间交互密切

##### 5、RDD

- Job、Task、DAGScheduler的定义均依赖RDD：弹性分布式数据集
- 是spark核心数据结构
  - 和list那些一样，是一个数据结构，内容平铺，可以按顺序遍历
  - RDD是分布式存储的，可并行计算
  - RDD分布是弹性的，可使得不同数据块重新汇聚和分布
  - 只读，可缓存在内存，可重复计算获得

- RDD定义：包含五个属性
  - 分区列表：存储数据块所在的分区位置
  - 依赖列表：记录了当前这个RDD依赖于哪些其他的RDD
  - 计算函数compute，用于计算RDD各个分区的值
  - （可选）分区器：子类可以重新指定新的分区方式:Hash/Range
  - （可选）计算各个分区时优先的位置列表
- RDD种类：继承自基础的RDD类
  - HadoopRDD, newAPIHadoopRDD
  - MapperedRDD
  - FlatMappedRDD
  - FilteredRDD
  - PairedRDD
- 生成RDD: 从外部数据读入并初始化为RDD, 从Driver数据集生成(parallelized函数)，RDD操作后生成新的RDD
- RDD操作
  - Transformation
    - input: RDD, output: RDD
    - 不会真实执行计算，只是定义新RDD并设置依赖关系
    - 操作对RDD依赖关系的区分
      - 宽依赖：依赖**前一个RDD所有分区**；窄依赖：依赖**前一个RDD确定的几个分区**
      - groupByKey宽依赖；map,filter,union窄依赖
    - map, flatMap(类似map但返回多个成员), filter, union, reduceByKey(func是(v,v)=>v)
    - join, mapPartitions(func作用于整个分区，类型是Iterator<T>=>Iterator<T>)
    - words = file.flatMap(func.lineSplit)
    - wordPairs = words.map(words=>(word,1))
  - Action
    - input: RDD, output: not RDD
    - Action之后，整个从输入RDD到输出的Transformation链条会被执行
    - reduce(只有一个返回值)，collect(RDD读到Driver里面，Array类型，RDD不能太大)
    - count(返回RDD成员数量), foreach(对RDD每个成员使用func), first(返回RDD第一个成员)=take(1)
    - saveAsTextFile(path), saveAsSequenceFile(path)

##### 6、DAG Scheduler

- 把一个Spark Job转成Stage的DAG(有向无环图)
- 根据RDD和Stage关系找出找出开销最小的调度方法
  - 然后把stage用taskSet的形式提交给Task Scheduler
- 划分Job: **一次Action的所有工作，就是一个Job**
- 划分Stage: **以宽依赖为分界**，宽依赖之前所有Transformation为一个Stage
  - 一个stage包含一个或多个Transformation
  - 一个Transformation在一个RDD分区上执行一个Task
- DAG Scheduler全过程
  - 从Action开始构造Stage DAG
  - 最后的Action构造一个ResultStage
  - 填补Stage需要的输入RDD，并根据对RDD的依赖关系划分Stage
  - 知道所有的RDD依赖关系填补完整
  - 开始按照DAG计算需要的RDD
  - 将每个Stage封装成TaskSet交给TaskScheduler

##### 7、Task Scheduler

- DAG Scheduler最后一步，计算Task最佳执行位置，为每个RDD分区创建Task，将一个Stage的Task封装成TaskSet交给Task Scheduler
- 于是TaskScheduler为了跟踪task set中所有task，包括失败、重启等，就为每个stage的TaskSet创建一个**TaskSetManager**
- 上面的**TaskSetManager**需要用**SchedulerBuilder**管理，决定TaskSet调度顺序
  - FIFO Scheduler Builder/Fair Scheduler Builder
- driverEndPoint通过makeOffers找出计算资源
- TaskScheduler根据计算资源，为TaskSet中每个Task分配Executor
  1. 遍历TaskSet
  2. 用taskSetManager遍历taskSet里面的task
  3. 按照本地性分配Executor

![](C:\Users\刘鹏程12138\Desktop\云计算笔记\TaskScheduler.PNG)

![1571896823164](C:\Users\刘鹏程12138\AppData\Roaming\Typora\typora-user-images\1571896823164.png)

##### 8、资源分配

- standalone集群：最简单的集群模式
- application调度：只支持FIFO
  - 资源分配：
    - 支持静态分配：一次性分配所有资源
    - 不支持动态分配：复杂
- Job调度：FIFO/Fair
- TaskSet调度：FIFO/Fair





















