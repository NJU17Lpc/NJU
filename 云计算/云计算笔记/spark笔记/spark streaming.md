# spark streaming注意点

- when run spark streaming program locally
  - 当要使用receiver来simultaneously receive multiple data streams时，这会占用一个线程
  - 所以线程数要大于receiver数，这样才可以Process data,( 比如用local[2] )
- 可以用ssc.socketTextStream(...)从socket里面读取
- 也可以从file system里面读取，比如HDFS API
  - streamingContext.textFileStream(dataDirectory)