# Spark工作机制

## 1、调度

- 用统一的系统进行资源分配
- 集群概述
  - Driver程序
    - 就是用户编写的spark程序
    - 每个driver程序包含一个代表集群环境的SparkContext对象，并与之交互
  - SparkContent对象
    - 担负着与集群沟通的责任
      - 分配CPU,内存
      - 启动worker node
      - 分发程序代码
      - 分发任务task到各个执行器
  - 集群管理器，spark支持三种集群部署
    - standalone: 资源管理器是Master
    - Hadoop YARN: 适合多集群同时部署管理，主流的
    - Apache Mesos
- Worker
  - 每个节点上，负责管理本节点的进程
- Task
  - 执行器上执行的最小单元
- 调度资源分配策略
  - 静态分配：一次分配资源，过程中不变
  - 动态分配：多程序共享资源，不用资源时归还
- Spark程序内部的调度
  - 不同线程提交的Job可以并行执行

## 2、内存管理

- 若某RDD不止一次被用到，就可以持久化他
- 使用persist函数配合其他参数
- 共享变量
  - 广播变量，用SparkContext.broadcast()创建，每个节点上都有一个缓存
  - 计数器，只能增加。只有Driver可以读，RDD没意义

## 3、容错机制

- 将计算转换为有向无环图
- 由于map,filter这些创建RDD的操作是粗粒度的，不用存储真正的数据
  - **<u>若某个分区丢失，只要重新计算该分区</u>**
- 窄依赖：父分区为一个子分区
  - 只要重新计算丢失的那一块数据，成本小
- 宽依赖：父分区为多个子分区
  - 冗余计算
- 有些场景容错会更复杂
- Master节点失效，和Slave节点失效，看不懂了

## 4、监控管理

- 每个Driver的SparkContext会在localhost:4040默认端口启动一个web界面
- 默认只有在程序运行时看到，希望程序结束后看到
  - 设置:spark.eventLog.enable=true
- 还可以通过JSON接口，开发人员可以自己开发可视化展示形式

## 5、Spark程序配置管理



# Spark内核

## 1、核心数据结构RDD

- 像Array，list这种可以顺序遍历的：**数据集合 Resilient Distributed <u>Dataset</u>**
- RDD成员被水平切割为许多小数据块，**分散在集群多个节点**
- RDD分布是弹性的：比如groupby就要将相同key元素汇聚到一起，RDD分布从而完全重组
- RDD只读不改
- 一般来说计算是流水式：新的RDD生成，抛弃旧的
  - 但可以指定某个RDD缓存在内存，避免重复计算
- RDD可以重新计算得到，用计算来恢复数据
- RDD对象分为5部分：（明天再看）





# Spark流式计算

- 处理周期短，但是7x24小时不断计算
- 实时流式计算，Spark通过Spark Streaming组件提供支持
- spark streaming按周期将数据分成多个批次，提交给spark核心来计算
- 简单示例
  - 启动TCP服务，用户手工输入文本；Spark通过tcp socket读取文本，统计词频，5秒计算一次并输出
  - 如启动端口9999后，启动spark-shell
    - spark-shell中
      - `val ssc = new StreamingContext(sc, Seconds(5))`
      - `val lines = ssc.socketTextStream("localhost",9999)`
      - 中间是正常的wordcount代码
      - `ssc.start()` 这里正式启动计算
      - `ssc.awaitTermination()` 等待执行结束
    - 上面完成后，可以输入文本了: "hello world !!!"
    - 返回spark-shell界面于是就有输出
      - (hello, 1)  (world, 1)  (!!!, 1)

#### 中间好长讲原理的部分真不想看了呜呜

#### 应用场景：类似百度统计的流式实时系统

























