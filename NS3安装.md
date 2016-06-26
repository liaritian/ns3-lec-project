## NS3安装过程
#### NS3安装预先设置Ubuntu环境，执行在终端以下命令<br>
      sudo apt-get install gcc g++ python
      sudo apt-get install mercurial
      sudo apt-get install bzr
      sudo apt-get install gdb valgrind
      sudo apt-get install gsl-bin libgsl0-dev libgsl0ldbl
      sudo apt-get install flex bison
      sudo apt-get install g++-3.4 gcc-3.4
      sudo apt-get install tcpdump
      sudo apt-get install sqlite sqlite3 libsqlite3-dev
      sudo apt-get install libxml2 libxml2-dev
      sudo apt-get install libgtk2.0-0 libgtk2.0-dev
      sudo apt-get install vtun lxc
      sudo apt-get install uncrustify
      sudo apt-get install doxygen graphviz imagemagick
      sudo apt-get install texlive texlive-pdf texlive-latex-extra texlive-generic-extra texlive-generic-recommended
      sudo apt-get install texinfo dia texlive texlive-pdf texlive-latex-extra texlive-extra-utils texlive-generic-recommended
      sudo apt-get install python-pygraphviz python-kiwi python-pygoocanvas libgoocanvas-dev
      sudo apt-get install libboost-signal-dev libboost-filesystem-dev

#### 安装NS3
+ 下载NS3安装包并解压,我下载的3.22版本格式为ns-allinone-3.22.tar.bz2<br>
在终端运行以下命令进行解压缩：（也可以直接用归档管理器解压）<br>
      bzip2 -d ns-allinone-3.13.tar.bz2
      tar xvf ns-allinone-3.13.tar


+ 命令终端进入解压缩文件夹 执行命令<br>

      ./build.py

+ 进入ns-3.13目录使用waf构建<br>

      ./waf -d optimized configure
      ./waf -d debug configure
      ./waf
      ./waf -d debug --enable-sudo configure

+ 脚本运行 进入ns-3.13目录<br>

      ./waf --run hello-simulator
      屏幕输出hello simulaotor
