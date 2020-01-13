# RIP

#### routing information protocol 路由信息协议

- #### 是一种基于距离矢量算法的

- #### 内部网关协议，也是一种动态路由选择协议

- #### 用于自治系统内部路由信息的传递 

### V1

- 缺点
  - update时没有发送子网掩码
  - update时使用广播broadcast 255.255.255.255
  - 不支持authentication
  - 不支持VLSM和CIDR

### V2是V1的升级版本

- 特点
  - 基于跳数，距离矢量
  - 使用holddown timer来防止路由环路
  - 使用split horizon来防止路由环路
  - 用16表示infinite distance

#### 跳数（距离）

- 一个路由器到直连的网络跳数为1
- 到非直连的网络，每经过一个路由器跳数加一
- RIP只允许一条路包含15个路由器，即跳数为16时不可达

#### 交换信息

- 只和相邻路由表交换信息
- 交换的是当前路由表知道的**<u>全部信息</u>**

#### 步骤

（下一跳相等的更成最新，下一跳不等的比较距离）

- 地址为X的相邻路由器发来RIP报文
  - 报文项组成：到目的网络N，距离，下一跳路由器
  - 把下一跳地址改为X
  - 把距离字段+1
  - 最后报文项组成：到目的网络N，距离d，下一跳路由器X
- 对修改后的报文中，每一个项目
  - 若原来路由表中没有目的网络N，则把该项目添加到路由表
  - 否则
    - 若下一跳路由器地址是X，就把受到的项目替换原路由表中的项目
    - 否则（要到目的网段N，但是下一跳不是X）
      - 若受到的项目中的距离d小于路由表中的距离，则更新
      - 否则什么也不做
- 若三分钟还没有收到相邻路由表的更新路由表，则把这个相邻路由器记为不可达
  - 距离设置为16

###### 注意如果下一跳不同，距离和原来一样，不改变

- 书上就是小于才会发生变化

#### 好消息传的快，坏消息传的慢

- R1断了Net1，没来得及把更新发给R2，R2给他发Net1,2,R1
- R1以为Net1可以到了，发给R2，  Net1,3,R2
- R2发给R1    Net1,4,R1
- 知道发到16时才听 



# OSPF

#### open shortest path first 更加强壮

- 链路状态协议
  - link-states链路状态指的是  接口  和  他邻居router的关系
  - link-states的集合形成一个link-state database
  - router使用SPF算法建立起SPF Tree，他们都把自己作为根
  - router通过SPF树建立起最好的路线，并将他们放在路由表中
- 最近RFC 2328描述



#### 介绍

- 一系列享有同样 aera ID的network/routers，享有相同的link-state information
- 每条链路link被赋予一个值
- ospf要分出aera，所以有必要为每个area选出一个代表
  - 注意 只要连到广播或者NBMA类型接口时才会选举出DR，点对点和点到多点类型接口上不需要选举DR
  - **DR**
    - 是OSPF multi-access network上的一个router
    - (be elected to)用来代表网络上的所有router
  - **BDR**  Backup Designated Router
    - 备份standby
    - 如果原来的DR fail，这个就作为DR
  - DR怎么选？
    - Priority + router ID，结果最大的是DR，次大的是BDR
    - Priority默认为1，范围1-255
    - ID好像是基于网络号的 loopback IP address
    - DR是针对接口的。一个router上一个接口DR，另一个BDR也可以
- OSPF需要至少有一个Aera 0，它是一个**<u>backbone，所有其他的area必须连到aera0</u>**
  - 由于一定会有router跨越两个aera
    - ABR: Aera boder routers，是与超过一个aera有interface的router
      - 一般在aera 0和其他aera之间

#### Hello Protocol

- 用 224.0.0.5，type=1
- 一个router开始ospf时，使用固定间隔时间，发送hello
- 广播网、点对点两种网络，hello间隔默认为10秒
- NBMA网络默认30秒

#### OSPF分组类型

- hello
- database description
  - 给出自己链路状态数据中
    - **所有**链路状态项目的**简要信息**
- link state request 链路状态请求
  - 向对方请求发送某些链路的详细信息
  - 这是经过database description比较后请求缺少的**<u>详细信息</u>**
- link state update 链路状态更新
  - 用泛洪法对全网状态进行更新
- link state acknowledgement 链路状态确认
  - 对链路更新分组的确认

#### cost

- 16位数字
- 越小越好
- 选路基于path的总cost
- cost = 100000000/bandwidth

#### 过程

- Step 1  establish router adjacencies
  - routers按时间间隔发送hello
    - **发现一个neighbour就加到neighborship database**
  - 选出DR/BDR(如果可以选的话)
- Step 2  选出DR和BDR
  - 没有其他router，自己做DR，下一个接上来的做BDR
  - 如果两个或更多routers一起加进来
    - 最高优先级是DR
      - 0优先级指的是永远不做DR
    - 优先级相等，router ID最高的当选DR
      - router ID的IP应该是所有接口里面最高的
  - 但是如果已经选好了DR/BDR
    - 又加进来新的，优先级更高的
    - **<u>当前的BDR/DR不变</u>**
    - 若当前的DR和BDR都坏了，新的才会变成DR
    - 若当前的只坏了DR，则原先的BDR上位，新的router暂时当BDR
- Step 3  discover routes
  - DR/BDR 交换LSA（链路状态确认）信息，并把DBD（Database description）发给所有的DR
  - 所有的router必须等待requesting router完全更新后，进入full state
- Step 4  选路
  - 网络上每个router都用SPF算法
    - 前提是所有router有统一的link-state databases
  - 通过加上每条路径的cost建立起tree
  - 将least cost path加到路由表里面
    - 同cost的path最多可以加4个
- Step 4  维护
  - regular exchange of Hellos来探测新的neighbor或者下线的
  - 根据网络种类设定发送hello间隔
    - 速度快的10秒一次
      - broadcast   p2p
    - 速度慢的30秒一次
      - nonbroadcast multiaccess links
    - dead interval应该是说受到hello回复的时间，为hello interval的4倍

#### 注意，OSPF发送链路状态更新使用的是可靠的泛洪法，受到多个更新包，只回复确认一次。同时designated router让整个网络广播信息量大大减少