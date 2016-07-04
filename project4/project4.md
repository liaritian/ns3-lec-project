## 设计要求
1. 搭建拓扑：两个wifi网络，各有6个sta，1个ap；实现两个wifi网络之间的通信
2. 场景范围：500m*500m
3. 传播模型为：
    ConstantSpeedPropagationDelayModel
4. Mac类型为：NqosWifiMacHelper（没有QoS保障的Mac层机制）
5. 移动模型为随机游走模型，设定初始位置为两个六边形，边长10m，sta在6个顶点上，ap在六边形中间；两个六边形中心相距50m
6. packet size为512byte，包间隔为100ms
## 实现过程
1. 拓扑搭建：同之前的project一样，只不过这次通过使用for循环来建立两个本质相同的拓扑，在for循环前先声明容器

            std::vector<NodeContainer> staNodes;
            std::vector<NetDeviceContainer> staDevices;
            std::vector<NetDeviceContainer> apDevices;
            std::vector<Ipv4InterfaceContainer> staInterfaces;
            std::vector<Ipv4InterfaceContainer> apInterfaces;
在for循环当中，进行节点创建，信道创建，设备安装，协议栈安装和分配地址，包括设置场景范围等各个细节，在for循环结束前，使用push_back将建立信息存储到相关容器，便于之后调用相关容器进行客户端与服务器的简历工作。

        staNodes.push_back (wifiStaNodes);
        apDevices.push_back (apDevice);
        apInterfaces.push_back (apInterface);
        staDevices.push_back (staDevice);
        staInterfaces.push_back (staInterface);
2. 场景范围：设置场景范围在设置移动模型时进行设置，具体设置方式如下：

        mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                                 "Bounds", RectangleValue (Rectangle (0, 500, 0, 500)),
                                 "Distance", DoubleValue(30));
3. 传播模型：在创建信道时，可以对于信道设置传播时延为ConstantSpeedPropagationDelayModel，设置方式如下：

        YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
        channel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");  
4. Mac类型设置：同之前的实验3一样，此处不赘述。
5. 设置移动模型与初始位置，AP的位置设置通过一条语句进行设置，STA的设置通过循环完成，实现方法与上次设置速度时方法差不多，实现方式如下：

        mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
        mobility.Install (wifiApNode.Get(i));

        Ptr<ConstantPositionMobilityModel> mob = wifiApNode.Get(i)->GetObject<ConstantPositionMobilityModel>();
        mob->SetPosition(Vector(225.0 + i*25.0, 250.0, 0.0));

        for (uint n = 0; n < wifiStaNodes.GetN(); n++)
        {
         Ptr<RandomWalk2dMobilityModel> mob = wifiStaNodes.Get(n)->GetObject<RandomWalk2dMobilityModel>();
         switch (n)
         {
         case 0: mob->SetPosition(Vector(216.3 + i*25, 255.0, 0.0));break;
         case 1: mob->SetPosition(Vector(216.3 + i*25, 245.0, 0.0));break;
         case 2: mob->SetPosition(Vector(225.0 + i*25, 240.0, 0.0));break;
         case 3: mob->SetPosition(Vector(233.7 + i*25, 255.0, 0.0));break;
         case 4: mob->SetPosition(Vector(233.7 + i*25, 245.0, 0.0));break;
         case 5: mob->SetPosition(Vector(225.0 + i*25, 260.0, 0.0));break;
         }
        }
6. packsize和包间隔的发送时间设置同实验一，只需要在创建客户端的时候设置packsize和interval即可，顺带把Maxpacketc调高一点（发送包裹数），代码如下：

        UdpEchoClientHelper echoClient (staInterfaces[0].GetAddress(0), 9);
        echoClient.SetAttribute ("MaxPackets", UintegerValue (20));
        echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.1)));
        echoClient.SetAttribute ("PacketSize", UintegerValue (512));

## 运行结果
1. 初始状态拓扑图
![](http://i2.piimg.com/567571/86c49a715001dd1c.png)
2. 运行状态拓扑图
![](http://i2.piimg.com/567571/29e9e696965f8c07.png)
3. 终端显示数据包发送图
![](http://i2.piimg.com/567571/73cd740eb8168090.png)
4. matlab图表
![](http://i2.piimg.com/567571/4ff791a3dd8d619e.jpg)
![](http://i2.piimg.com/567571/d4e481e1e0e195b2.jpg)

## 遇到的问题
1. 对于网桥的疑惑，之前学长说不使用P2P实现，于是在一开始我设置的csma节点来进行两个wifiAP之间的通信，完全可行，但是后来想了想好像其实和P2P是一样的，然后去找了一下关于网桥的相关内容，发现了一个wifi-wired-bridging.cc的一个例子，在例子中，他用网桥将两个wifi的AP通过csma信道连在了一起。但是，我个人感觉这和直接用csma信道把两个AP相连好像没什么区别，无非就是把csma的ip地址给到了网桥而已，一直不是很理解。还有是如果不使用有线信道的话，还可以使用什么来完成，一开始百度到了无线网桥这个东西，后来发现模块里没有。现在还没有解决。
2. 对于vector的不理解，由于之前没有面向对象的编程的经验。所以对容器，类什么的理解比较肤浅，在这个设计当中，使用了vector是仿照之前提到的那个例子的，我自己的理解是，这个容器相当于一个数组，只不过这个数组可以通过循环来存储对应的类的内容，在之后我想调用比如说我之前创建的第一个循环中的东西的时候，就可以通过调用相关的容器里的类来进行调用。
3. 当我使用网桥的时候，必须要把全局路由那句话注释掉。查了百度google也没查到原因。
## 算是一点感想吧
NS3的入门培训其实我自己感觉任务虽然都完成了，但是欠缺的地方还有很多，尤其是英语和对面向对象的编程的理解上，基础很不扎实，对于网络的一些模型理解也会存在一些偏差，但是实现的过程还是相当有趣的。自己还会继续努力学习，争取能够更快理解。最后，谢谢游师兄和曾师兄。
