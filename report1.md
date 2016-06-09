#the screenshot of the result of my programme<br>
![whole result](http://ww1.sinaimg.cn/mw1024/e840e60cgw1f4oy1xzy55j20k50csdn8.jpg "程序运行结果显示姓名学号和输出频率")<br>
![](http://ww2.sinaimg.cn/mw1024/e840e60cgw1f4oy1y657uj20k002y0uj.jpg "wc命令显示字符数目")<br>
![](http://ww4.sinaimg.cn/mw1024/e840e60cgw1f4oy1yipycj20k202wmz1.jpg "wc命令显示行数")<br>
![](http://ww1.sinaimg.cn/mw1024/e840e60cgw1f4oy1xz0joj20k303fq5a.jpg "grep命令显示指定带有4的行")<br>
##the analyse of the result<br>
在代码中通过修改printHello函数，令其参数为(std::string word1,std::string word2,double n)，分别表示姓名，学号，输出频率（此处令为0.5）。<br>
输出时从0s开始一直到5s每隔0.5s持续输出我的个人信息，结果如上图所示，最后使用wc和grep命令对输出结果进行统计。<br>
###SOME QUESTION<br>
如何实现既能通过./waf同时输出结果，还能通过wc输出行数，尝试过将|wc -X 改为&wc -X等等发现并没有卵用。<br>
