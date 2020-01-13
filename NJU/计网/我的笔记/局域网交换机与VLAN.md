# 局域网交换机与VLAN

## 1、Switching，什么是交换

- 交换就是两个基本功能
  - 根据MAC地址，建立和维护switching tables
  - switching frames，从interface发到destination
- symmetric switching对称交换
  - 交换机上所有端口带宽一样
  - 多用在终端到终端的网络中
  - 会有性能瓶颈
- asymmetric switching非对称交换
  - 不同端口带宽不同
  - 非对称交换机中要有memory buffering
    - 即使用内存存储数据的方式
  - 多用在客户/服务器模型中
- memory buffering
  - 使用交换机中内存的一部分，存储data和destination，直到被转发出对应的Port
  - port-based memory buffering
    - 数据包存储在每个端口独自享有的队列（内存）中
    - 当一个端口很忙时，可能会由于目的端口堵塞，于是源端口后面的帧不得正常发送
  - shared memory buffering
    - 所有端口共享内存
    - 动态分配各个窗口所需要的缓存内存量
- switching methods转发方式
  - store and forward存储转发
    - switch获取整个frame
    - 发去destination之前进行CRC校验
  - cut-through直通
    - 上一种转发方式会有delay
    - fast-forward switching
      - 在forwarding之前，只检查destination的MAC
      - 没有error checking
    - fragment free
      - 在forwarding之前，会读取前64B，从而减少error
      - 过滤掉大多数error
      - check collisions
      - （不太懂）
- 交换机种类
  - 二层、三层、四层交换
  - multilayer switching多层交换

## 2、The spanning-tree protocol生成树协议

### 背景

- 网络环路
  - 原因
    - 提供冗余
      - 我怀疑是为了防止某个交换机突然挂了
    - configuration配置错误
  - loop在桥接网络中的后果
    - broadcast loops
    - bridge-table corruption
- L2 Loops
  - broadcast和第二层环路结合，会非常危险
    - 以太网帧 没有TTL field
    - 他一旦开始loop，一般除非关了交换机，出不来的
    - 给交换机CPU带来巨大的负担

### Overview of STP

- 主要功能
  - 在 switched/bridged网络中，容许redundant paths的存在**(path不是loop)**
  - 但不会造成loop延迟的影响
- 大概怎么实现
  - 计算出一个稳定的spanning-tree网络拓扑
- 用的frame
  - spanning-tree frames
  - 又叫：BPDU (bridge protocol data units)
  - 只能在switch之间传播
  - 这种帧是用来决定 生成树的拓扑
  - BPDU结构![](C:\Users\刘鹏程12138\Desktop\计网复习笔记\BPDU格式.PNG)
- 想法
  - 创造出一个根节点 root bridge
  - 整个树结构从这个root bridge开始
  - 不属于这个树结构的 **redundant links** 被隔绝
  - 被隔绝的link上，要传送frame会被拒绝
  - switch通过交换BPDU，来形成这个树结构
- four-step decision大概情况
  - lowest root BID(Bridge Identification)
    - 决定哪个是root bridge
  - lowest path cost to root bridge
    - 找出这个root bridge多远
  - lowest sender BID
    - 发送这个BPDU的bridge，他的BID是多少
  - lowest port ID
    - 这个BPDU是来自哪个port的
- BID: Bridge Identification
  - BID: 8B
    - 高2B：bridge的优先级
      - 范围从 0-65535，默认为32768
    - 低6B：分配给switch的mac地址
  - cost：越低越好
- root switch
  - 拥有最小BID的switch被指定为root switch
  - 如果优先级都是默认的32768，MAC地址最小的当root
- path cost
  - 用于衡量bridge之间的距离（逻辑上的）
  - 距离越小越好
  - 如bandwidth: 4 Mbps   cost: 250
    - 10Gbps    cost:  2
- 五个STP状态
  - 图示![](C:\Users\刘鹏程12138\Desktop\计网复习笔记\STP的五种状态.png)
  - blocking
    - 只接受BPDU
  - learning
    - 建立bridging table
  - forwarding
    - 接或发user data，学习address
  - disabled
    - administratively down
  - listening
    - 建设"active"拓扑
- 初始化
  - network一通时，所有bridges flood
    - 全是BPDU信息
  - 然后，米娜桑一起将decision sequence应用到整个网站
- decision sequence
  - root switch decision选老大
    - 每个switch将自己作为root
    - 检查每个port获取的所有BPDUs
    - 若有BPDU的value更小
      - 替换掉自己的old value
      - 对应的BPDU发送者被认定为new root
      - （我估计被发出去的BPDU也会被改一下）
  - electing the root ports
    - 所有非根bridge必须选出一个root port
    - 这个port，必须是**最靠近root bridge的port**，**也就是开销最低**
    - 将到root bridge的link的cost累加起来（代数和），就是root path cost
  - electing the designated port 选取指定的port
    - designated port是连接到网段的一个桥接端口
      - **<u>这个端口到达根端口的路径开销最低</u>**
    - **<u>designated port和root port条件都是开销最低</u>**
      - **根端口就是和根交换机相连的端口**
      - **指定端口就是和下级交换机相连的端口**
      - **所以**
        - **root bridge上每个active的port都是一个designated port**
    - non-designated port非指定端口
      - 这种端口状态设置为阻塞
    - 非根桥进行根端口选举时，根路径开销最小的端口为指定端口
  - STP一个例子
  - ![](C:\Users\刘鹏程12138\Desktop\计网复习笔记\STP的例子.PNG)

## 3、VLAN

### 在传统的LAN

- "shared hub" 确定各个LAN
- routers segment the LAN
  - broadcast firewalls

### 现在的VLAN

- 工作在第二层、第三层
- 能控制network broadcasts
- users不用再被物理上隔离
  - be assigned by net admin
- 提供更好的网络安全保障

### VLAN (IEEE 802.1q)

- 特性

  - 是一个 逻辑上 对网络设备(network devices)的 分组(grouping)
  - 不管这些设备的物理上physical segment location在哪里
  - 一个VLAN create a single **<u>broadcast domain</u>**(**<u>分割广播域</u>**)
    - 就像一个**<u>子网</u>**一样
  - 网管使用software 在switch中建立起VLAN
  - user可以根据以下几点被grouping
    - port number
    - mac address
    - protocol being used
    - application being used

- backbone主干，用于VLAN之间的通信

  - 这个backbone速度要快
  - 一般大于100Mbps

- 在VLAN中，routers做了什么

  - 他是用来连接不同的VLAN的
  - switch划分VLAN后，不同VLAN上的user不能直接相互交流
  - 所以VLAN1和VLAN2之间需要一个router来交流

- VLAN中的帧会有什么作用

  - switch根据帧中的data来做决定

    - frame filtering
      - 可能会查MAC地址  也可能查第三层协议
    - frame tagging
      - **<u>核心功能：标记帧来自哪一个VLAN</u>**
      - 在frame被转发到backbone之前，把tag放在帧头部的一个特殊的地方
      - 每个switch去识别这个标记
      - frame到达目的地前，对应switch去掉这个tag
      - **<u>tag的整个过程作用在第二层</u>**，不需要人工加工

  - **每个switch创建一个filtering table**

  - 两种标准中的frame tagging

    - 都是用以太网媒介
    - IEEE 802.1Q
      - 就是在头部加一个VLAN label
      - <u>**Encapsulation No**</u>
      - <u>**Label Yes**</u>
    - **ISL(Inter-Switch Link)**
      - **Cisco的专利，再封装一遍帧，加上VLAN的信息**
      - 在data frame之前加上26B的数据
      - 在data frame之后加上4B的CRC
      - <u>**Encapsulation Yes**</u>
      - <u>**Label No**</u>

  -  VLAN怎么实现呢

    - 总体上三种
      - 静态
        - 指的是：switch上的**<u>端口</u>**都被**<u>人工指定</u>**，属于某个VLAN
        - 好处
          - 便于配置(configure)和监督(monitor)
          - 因为VLAN的各种活动都被控制好了，所以网络表现不错
      - 动态
        - 当一个station刚开始连接到一个unassigned port时
          - switch检查表中的entry(?)
          - **<u>动态地将这个port与正确的VLAN配置起来</u>**
        - 好处
          - 当总是要加入新的user时，可以减少人工配置
          - 进行集中通知(?)
      - **port-centric VLANs以端口为中心的VLAN**
        - 同一VLAN下的所有节点，接入到同一个路由器接口上
        - 或者说，接入同一个路由器端口的节点，被划分到同一个VLAN下
        - 好处
          - 让management更容易
            - 利用router加强保密性(再用一个acl)
            - packet不会泄露到(leak)其他广播域(domain)
            - VLAN很容易去admin（监管）
            - 通过router的port来指派user
    - switch上每一个port都会指定一个VLAN
      - 便于VLAN广播域的共享与隔离

  - **Access Link 接入链路**

    - 其上面只有一个VLAN的链路，这个VLAN叫做这个链路对应的端口的本地VLAN**<u>(native VLAN)</u>**
    - **<u>接到这个port的设备不知道他在一个VLAN里面</u>**

  - native VLAN**<u>本征VLAN</u>**

    - vlan1名字叫default
    - trunk接口初始认为的本征是vlan1
      - 但这个本征是可以修改的

  - **Trunk Link : Trunk链路，或主干链路**

    - 上面有**多个VLAN**的链路
    - 用于连接
      - **交换机与交换机**
      - **交换机与路由器**
    - 可以在f(Fast ethernet)口和g(Gigabit ethernet)口上跑
    - 就是在一个线上，跑多个VLAN
      - 因此VLAN要打上tag
      - 到达目的交换机后，转发到对应VLAN里面
    - trunk link可以通过设置，来确定是传所有VLAN，还是一部分VLAN
    - trunk link还有个本地VLAN(native VLAN)
      - 如果trunk link因为某个原因fail
      - trunk就用这个native VLAN
    - 好处
      - **<u>节约端口</u>**
        - 为什么节约了端口，见下图
      - 方便配置
      - 牺牲一点性能
    - ![](C:\Users\刘鹏程12138\Desktop\计网复习笔记\使用和不使用Trunk链路对比.PNG)

  - 删除VLAN

    - 当一个VLAN被删除后，原来连过去的port变成 不活跃的(inactive)
    - 这些port，会一直与被删除的VLAN相关联
      - 知道被分配给一个新的VLAN

  - CDP:

    - Cisco Discovery Protocol
    - 思科设备发现协议

  - VTP:

    - VLAN Trunking Protocol
    - VLAN中继协议

  - VLAN上的routing:  Routing Between VLANs  VLAN间路由

    - 可以使用物理接口
      - 一个接口一个VLAN
      - 没有带宽争用
      - **连接到接入模式交换机端口**
      - 成本高
      - 连接配置较为复杂
    - 也可以使用子接口
      - 多个VLAN占用一个物理接口
      - 有带宽征用
      - **连接到中继模式交换机端口**
      - 成本低
      - 连接配置较简单

  - (自己写的)**什么叫单臂路由**(router-on-a stick)

    - 就是在路由器以太网接口下配置几个子接口
    - 每个子接口对应一个VLAN
    - 当路由器的以太网口连接到一个划分VLAN的二层交换机时
    - 可以通过路由器的以太网口，实现二层交换机上多个VLAN之间的互通
    - 三层交换机VLAN之间可以互通
      - 可在三层交换机上直接配置VLAN虚接口，每个VLAN一个，并指定IP
      - 通过VLAN虚接口实现交换机各个VLAN之间的互通

    

