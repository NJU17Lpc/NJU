# RDD

- Resilient Distributed Dataset 弹性分布式数据集，是spark最基本的数据抽象
- RDD有
  - 一组分片(partition)
    - 数据集的基本单位
  - 计算每个分区的函数
  - 做分片的函数
  - 存储每个partition的优先位置preferred location
    - 移动数据不如移动计算，把计算任务分配到相应分片
  - RDD之间的依赖关系
    - RDD每次转换都会生成一个新的RDD，即使部分数据损失也可以重新计算
- RDD执行是lazy，比如直到collect()的时候才会触发之前的处理
  - val textFile = sc.textFile("README.md")
    - SparkContext对象的textFile函数接收文本文件为输入，创建**新的RDD**
  - val words = textFile.flatMap( line=>line.split(" ") )
    - flatMap是**<u>接收一个函数</u>**，对**当前RDD所有成员**调用这个函数，并**返回新的RDD**
  - val wordPairs = words.map( word=>(word, 1) )
    - <u>**与flatMap不同，map输入一个RDD，输出一个RDD**</u>
    - **<u>flatMap，对每个输入（函数），输出的是一个集合，一到多</u>**
  - val wordCounts = wordPairs.reduceByKey( (a, b)=>a+b )
  - wordCounts.collect()
    - 将RDD分布在各个节点的数据拉回到**Driver程序本地**

### 传递函数参数,上面使用的匿名函数适用于小片段代码，下面的是传递单例对象object的静态方法

- 修改上面的flatMap

`object MyFunctions{`

​	def lineSplit (line: String): Array[String] = {line.split(" ")}

`}`

`val words=textFile.flatMap(MyFunctions.lineSplit)`

- 修改上面的map
  - 这里使用的**普通类**的方法不太建议使用，还要序列化
  - 序列化原因：计算代码是要从Driver程序分发到各个计算节点的，需要序列化，传输，反序列化
    - 之前的匿名函数和object对象都具备序列化

`class MyClass extends java.io.Serializable{`

​	def wordMap(word: String): (String, Int) = { (word, 1) }

`}`

`val wordPairs = words.map(myclass.wordMap)`

#### 对RDD的函数调用，实际不在本地运行；即使单机跑，也是在单独的进程上跑

`var counter=0  var data=Seq(1,2,3)  var rdd = sc.parallelize(data)`

`rdd.foreach(x=>counter+x) println(counter)`

- counter被序列化，传输到计算节点，到了那边后反序列化为新的counter
- 只有计算节点上的counter会增加，Driver程序的counter不变

#### RDD有两类操作

- Transformantion
  - 接受一个RDD输入，返回一个新的RDD
  - map(func)
  - flatMap(func)
  - filter(func)
  - mapPartition(func), mapPartitionsWithIndex(func)
    - (和map类似，但作用对象是整个RDD分区)
  - sample(withReplacement, fraction, seed)
  - union(otherDataset) 和其他RDD合并，不去重，类型要一直
  - distinct([numTasks])  去RDD去重
  - groupByKey([numTasks])  不进行func的进一步操作
  - reduceByKey(func, [numTasks])
  - sortByKey([ascending], [numTasks])
  - join(otherDataset, [numTasks]) 对(K, V)  (K, W)进行操作返回(K, (V, W))
- Action
  - 输出不是RDD，不是分布式，直接回送到Driver程序
  - reduce(func)  对RDD成员用func进行reduce操作，并发执行，最后结果只有一个值
  - collect() 将RDD读取回Driver，但是RDD不能太大
  - count() 返回RDD成员数量
  - first() =take(1)
  - take(n) 返回RDD前n个成员
  - saveAsTextFile(path) 将RDD转换为文本(toString)保存至。。。
  - countByKey() 对key计数，返回（K, int）
  - foreach(func)  对RDD每个成员进行func，没有返回值

#### 打包提交

spark-shell是用于调试的，调好后需要编译链接，**<u>打包成jar包</u>**，最后提交到集群





















