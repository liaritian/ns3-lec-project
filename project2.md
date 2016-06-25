
### 拓扑一
#### 左右两个CSMA链路各4个节点，通过中间的点对点链路连接起来,对应文件与拓扑图在`third1.cc`中
+ 首先使用`nodecontainer`创建节点，运用create来创建个数。<br>
+ 接着用helper类来创建链路，比如`PointToPointHelper`
就会创建点对点链路的信道,设置完信道参数后就通过创建device类将对应信道设备下载到节点上。<br>
+ 使用`internetStackhelper`类创建协议栈，通过install下载到各个节点上<br>
+ 然后使用`Ipv4AddressHelper`来创建IP地址，并通过`Ipv4InterfaceContainer`来创建接口并将值赋予网络设备以完成IP地址的初始化<br>
+ 设置`UdpEchoServerHelper`来设置作为初始服务器的节点与端口，设置`UdpEchoClientHelper`来设置作为客户机的节点与指向端口。最后通过`ApplicationContainer`安装相应的应用层程序给对应节点，并赋予启动时间<br>
![拓扑一运行截图](http://i1.piimg.com/567571/c6cb8e32022dbc0f.png)<br>

### 拓扑二
#### 左右两个CSMA链路各4个节点，通过中间的点对点链路连接起来，对应文件与拓扑图在`third2.cc`中
+ 相对于拓扑一，拓扑二中加了wifi信道，在创建wifi节点时要设置无线接入点AP和移动终端STA，然后接着设置信道参数如速率算法等等。<br>
![拓扑二运行截图](http://i2.piimg.com/567571/da8f3acbeff84764.png)<br>

### 移动模型
+ 此处使用`constant-velocity-mobility-model`来确定STA的移动方式，通过打开`/src/mobility/model`中的该模型源代码并没有找到具体的使用方式，查找examples也没有找到对应的使用方式。最后通过一个了类似学生与老师问答的网页找到了使用方法，但是不是很理解。代码如下：<br>
![移动模型代码](http://i2.piimg.com/567571/2b6ee47a537d2169.png)<br>

### 其他收获
+ 使用了atom编辑器，感觉异常方便，贴条两个地址，第一个是非常清晰的atom教程，第二是上传图片很方便的网址。<br>
`http://www.jianshu.com/p/f3fd881548ad`<br>
`http://yotuku.cn/`
