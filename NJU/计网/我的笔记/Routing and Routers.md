# Routing and Routers

# 这一章多参考网上的那一份

## 内部组成

- RAM
  - router没电或重启时RAM内容就丢失
  - 用来存储
    - Routing tables
    - ARP cache
    - Fast switching cache
    - Packet buffering
    - Packet hold queues
- NVRAM
  - Non-volatile RAM
  - router重启或没电时不丢失内容
  - 用于存储backup/startup configuration files
    - （这个叫启动配置）
- Flash
  - EEPROM(Electronically Erasable Programmable Read-only Memory)
  - 保存Cisco的IOS，可存储多种版本的IOS
  - 没电也存着
- ROM
  - 用于**POST(Power On Self Test)上电自检**
  - 执行软件程序
    - 如备份、升级

- Interfaces
  - 拥有多种物理接口
    - console  
    - auxiliary辅助口

## Router Startup Procedure

- 一种说法
  - POST检测硬件
  - 执行引导装入程序
  - 定位加载Cisco IOS
  - 定位加载启动配置文件（或进入配置模式）
- 另一种说法
  - CPU执行ROM的bootstrap loader
  - 找Cisco IOS
  - 找NVRAM的configuration文件，放入主存自行
    - 如果没有这个文件，则执行system configuration dialog  又叫setup mode
- ![](C:\Users\刘鹏程12138\Desktop\计网复习笔记\路由器的启动.png)

## Routing

- router两个基本功能
  - path determination
    - accept a packet on one interface
    - and forward it through a second interface
  - switching
    - select the most appropriate interface for forwarding a packet
- router用地址的network portion来select path
  - 只有和目标网段直连的router，才会用地址的node portion来传递数据包到正确的host
- stub network末端网络
  - 只有一条路径能连接到的网络，叫stub network
  - 这种情况下，只需要一条静态路由，不需要动态路由
- administrative distance管理距离
  - 是对路由可信度的衡量
  - 数字越大，可信度越低
  - 所以静态路由的administrative distance通常很小（可信度高）
- time to covergence
  - convergence occurs when all routers use a consistent perspective of network topology
  - after a topology changes, routers must recompute routes, which distrupts routing
  - the process and time required for router reconvergence varies in routing protocols
  - 就是说这个当所有的router都用某种连续的视角看待整个网络拓扑时，一旦拓扑上出现某些变化，routers需要一定的时间去意识到这些变化，通过某些方法把网络拓扑慢慢更新到真实情况
- routing protocols分类
  - DVP: Distance-Vector Protocol
    - router不知道整体，只知道邻居。传递路由表的copy
    - 基于Bellman-Ford算法
    - 缺点是，路由更新收敛很慢
      - 好消息传得快，坏消息传得慢
    - count to infinity解决办法（换句话是防止路由环路的方法）
      - 定义一个maximum distance来表示Infinity
      - route poisoning,router检测到network down，就出发poisoning，定义对应的network为16或unreachable
      - split horizon水平分割：
        - router从某个接口受到的更新消息不允许再从这个接口发回去，一定程度避免环路
      - hold-down timer抑制计时：
        - 一条路由信息无效后，一段时间内不再接受关于同一目的地址的路由更新
  - LSP: Link-state Protocol
    - **RFC 1583**
    - 基于SPF: Shortest path first algorithms
    - 使用
      - link-state advertisement(LSAs)
      - a topological database
      - SPF 算法，和生成树结果
      - **<u>a routing tables of path and ports to each network</u>**
    - 过程：
      - routers之间交换LSAs
      - 每个router构造一个topological database
        - 包括网络上所有的LSA
      - SPF算法运行，计算网络可达性
        - 计算出一个树形拓扑
        - 自己为root，包含到达每个网络所有可能的路径
        - 排序
      - router列出best paths
        - 再路由表中记录best paths可对应的ports
    - two link-state concerns
      - processing and memory requirements
        - LSP需要更多的存储空间和更好的运算性能
      - bandwidth requirements
        - link-state packet flooding
        - routers需要flooding来发送LSA packets到其他routers
        - 占用了数据包的带宽
    - 一些问题
      - link-state routing要保证所有的router能获取到需要的LSA packets
      - 获取到不同的LSAs sets，会计算出不同的拓扑数据
  - **Hybrid Protocols 混合协议**
    - 混合DVP和LSP
    - 例子
      - OSI的IS-IS(Intermediate System-to-Intermediate System)
      - Cisco's EIGRP(Enhanced Interior Gateway Routing Protocol)

## Routing Protocols的goals

- optimal Route
  - pick the best route
- efficiency
- rapid convergence
- flexibility