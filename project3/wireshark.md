## wireshark的安装以及一些使用
由于我用的时ubuntu15.04版本，所以直接使用<br>

    sudo apt-get install wireshark
安装完之后就可以打开图形界面了。但是为了能够在普通状态下打开dumpcap，需要添加相应的用户组。操作如下

    #sudo groupadd  wireshark
    #sudo chgrp wireshark /usr/bin/dumpcap
    #sudo chmod 4755 /usr/bin/dumpcap
    #sudo gpasswd -a *用户名*  wireshark
此时可以用普通用户登录wireshark也可以进行抓包了。<br>
运行时直接命令行输入wireshark即可。<br>
## wireshark的基本使用
+ 在抓包前设置捕捉滤波器
设置路径：
      ：capture——option
具体格式如下
      protocol | direction | host value | logic_operation | other_expression
具体参数不列举，此处设置捕捉滤波器为
      ip src host 192.168.1.105
抓取报文如下：
![](http://i1.piimg.com/567571/e9cf691cf6e09e41.png)
但是个人感觉捕捉滤波器功能并不是很科学，每次设置完滤波器还需要重新抓包，很不方便，个人更喜欢显示滤波器。
+ 设置显示滤波器
如果感觉使用捕捉滤波器捕捉到的信息依旧冗余，可以使用显示滤波器进行二次过滤，格式如下：
      protocol.string1.string2(可选) 运算符（==，！=，...） number 逻辑运算符 （下一个表达式）
这里设置如下：
      tcp.dstport == 80
则显示如下：
![](http://i4.piimg.com/567571/dad0b8c9eda817ae.png)
