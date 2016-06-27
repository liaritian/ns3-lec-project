## 系统日志信息
首先对记录组件进行定义，如下代码：

    NS_LOG_COMPONENT_DEFINE ("ThirdScriptExample");
然后设置日志级别,此处设置成：<br>

    LogComponentEnable("UdpEchoClientApplication",LOG_LEVEL_FUNCTION);
    LogComponentEnable("UdpEchoServerApplication",LOG_LEVEL_FUNCTION);
打印结果如下：
![系统日志截图](http://i4.piimg.com/567571/b59bf4b56209d553.png)<br>
但是在看PPT中的博客时，给出了通过设置shell环境便来来使用的方法，但是尝试之后并没有起到作用。还在尝试和查资料中。<br>
## tracing信道文件
首先，在Simulator::Run()前，添加下面的代码：

    AsciiTraceHelper ascii;
    pointToPoint.EnalbeAsciiAll (ascii.CreateFileStream("first.tr"));   
先创建了一个ascii类，然后pointToPoint相当于之前我们定义的点对点信道EnableAsciiAll表示将asciitracing安装在仿真中的点对点设备上，然后ascii.CreateFileStream用来创建文件流。

## Pyviz运行截图
因为之前自己的NS3安装是使用了./waf安装的，安装之前下载了很多包，其中包括pyviz，所以直接在运行脚本代码后加 --vis即可，截图为截取信息传输时刻拓扑与发送流的方向，也可以看出，wifi的STA节点时匀速移动。![Pyviz运行截图](http://i4.piimg.com/567571/3e1f511fcb33d150.png)<br>
## matlab绘图
此处绘制客户端发送时间与服务器响应时间的关系表格<br>
![](http://i1.piimg.com/567571/fd67c20290bfca9c.jpg)
