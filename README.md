# jon version 0.1
jon 是一款LINUX系统攻防工具箱，包含扫描，入侵，痕迹清理，木马，网站测试等各种黑客工具。

##安装方法(任选一种方法即可)
####方法一：
```Bash
[root@localhost jon]# yum -y install gcc autoconf cmake
[root@localhost jon]# aclocal
[root@localhost jon]# autoheader
[root@localhost jon]# automake --foreign --add-missing --copy
[root@localhost jon]# autoconf --warnings=all
[root@localhost jon]# ./configure
[root@localhost jon]# make
[root@localhost jon]# make install
```
####方法二：
```Bash
[root@localhost jon]# chmod +x autogen.sh
[root@localhost jon]# ./autogen.sh
```


##使用手册

#### -h 选项：用于指定要修改的文件的路径的，是个可选项。由于不同系统的日志存放路径不一样，可以手工指定。
```Bash
[root@localhost jon]# jon -h
jon v 0.1 for linux
Copyright (C) 2003 by jon <2182619@qq.com>

jon [-f utmpfile] -u username ip               hide username from ip in utmp file
jon [-f wtmpfile] -w username ip               hide username from ip in wtmp file
jon [-f lastlogfile] -m username ip ttyname YYYY[:MM[:DD[:hh[:mm[:ss]]]]]  modify lastlog info
```

#### -f 选项：用于指定要修改的文件的路径的，是个可选项。由于不同系统的日志存放路径不一样，可以手工指定。
默认的日志存放地点是：
```c
#define UTMPFILE "/var/run/utmp"
#define WTMPFILE "/var/log/wtmp"
#define LASTLOGFILE "/var/log/lastlog"
```

#### -u 选项: 有时候你和管理员同时在线，管理员w一下就能看到你了。使用-u选项用户躲避管理员w查看，如下：
```Bash
[root@localhost jon]# w
 21:27:25 up 5 days, 13:48,  4 users,  load average: 0.00, 0.00, 0.00
USER     TTY      FROM            LOGIN@   IDLE   JCPU   PCPU WHAT
root     tty1     -               Fri14   18:24m  0.33s  0.33s -bash
root     pts/3    192.168.1.8     20:21    6:22   0.04s  0.04s -bash
root     pts/2    192.168.1.8     20:06    0.00s  0.13s  0.00s w
root     pts/4    192.168.1.8     20:21    5:52   0.03s  0.03s -bash

我们是从192.168.1.8机器连上来的，现在隐藏下：
[root@localhost jon]# jon -u root 192.168.1.8
[root@localhost jon]# w
 21:27:46 up 5 days, 13:48,  1 user,  load average: 0.00, 0.00, 0.00
USER     TTY      FROM            LOGIN@   IDLE   JCPU   PCPU WHAT
root     tty1     -               Fri14   18:24m  0.33s  0.33s -bash
```

#### -w 选项:用于清除你的登录日志，现在上的linux日志清除工具做的很粗燥啊，这个可以指定清除某些ip过来的机器。
```Bash
[root@localhost jon]# last
root     tty1                         Wed Oct  1 21:30 - 21:30  (00:00)
root     pts/4        192.168.1.8     Wed Oct  1 21:21   still logged in
root     pts/3        192.168.1.8     Wed Oct  1 21:21   still logged in
wtmp begins Wed Oct  1 06:01:46 2008

清除192.168.1.8的登录日志：
[root@localhost jon]# jon -w root 192.168.1.8
[root@localhost jon]# last
root     tty1                         Wed Oct  1 21:30 - 21:30  (00:00)
wtmp begins Wed Oct  1 06:01:46 2008
```

#### -m 选项:用于修改上次登录地点，我们使用ssh登录的时候可能会注意到这点
```Bash
login as: root
Sent username "root"
root@192.168.1.28's password:
Last login: Wed Oct  1 21:31:40 2008 from 192.168.80.45

如果不修改lastlog的话，管理员下次登录就会提示从我们的机器IP登录。使用-m选项可以编辑这个选项：
[root@localhost jon]# jon -m root 192.168.0.0 tty10 2008:1:1:1:1:1
[root@localhost jon]#

当然，这只是个举例，在使用中各位请根据具体信息修改，下次管理员登录，登录界面就成了
login as: root
Sent username "root"
root@192.168.1.28's password:
Last login: Tue Jan  1 01:01:01 2008 from 192.168.0.0
```