# GOMOKU

简单的五子棋，期末大作业

托管到了[ Github 上。](https://github.com/Jenway/gomoku)

额，鉴于 GitHub 不是很稳定。

又 fork 到了[ Gitee 上一份。](https://gitee.com/jenway/gomoku)

## 1

Based on QT 5.9.0

## 算法

	评分表的算法。

## 作业要求

### 功能实现

* [X] 1.能够正确判断对局输赢并结束游戏。


### 文件操作

* [X] 1.能够将已进行对局的每一步信息存储到文件中。
* [X] 2.能够从文件中读取对局信息。
* [X] 3.能够将从文件中读取的信息以对局回放的形式展示出来。

### 多模式

* [X] PVP、PVE(P-first & E-first)、EVE

### 图形界面

* [X] 1.使用图形化界面的形式来实现五子棋。
* [X] 2.通过鼠标来控制棋子落点。

### 功能完善(30分)

* [X] 1.数据持久化:通过更巧妙的方法和形式来存储对局信息。

	例如使用json、xml、csv等格式存储信息。

* [ ] 2．更完善的存储操作：可以存储多个对局的信息，实现对局信息的增删改查功能。
* [X] 3．异常处理:能够对程序运行过程中出现的各种异常进行提示和处理。

	例如提示操作越界、违规、存储信息的文件遭到破坏等。

* [ ] 4. 数据处理：将存储的对局数据进行排名或记录，展示每一局的时间、步数、输赢方等信息。

	将存储的信息进行可视化处理。

* [X] 5. 软件发布：将程序打包成软件。

	例如将程序打包成exe文件，并包括程序的运行环境，确保可以在非开发环境中正常打开。

### 聪明的电脑

* [X] 1.在和人对弈时能够对弈至少20步(总步数)。
* [ ] 2．通过各种方式实现人机对弈的机器先手必胜。


### 开发中一个有意思的BUG

在一局比赛结束后读入数据时，默认是要找到上一次比赛数据尾部的标识着上一次序号的一行数据，于是很自然地，

将文件读取光标到最后一行出现目标数据之前，假设文件(CSV)的 size 为 size，那么默认的光标开始 i 为 

size - 7，不过如果当对弈步数和比赛序号同时大于两位数，就刚好找不到标识符 -> 了，程序于是卡死。

很有意思。于是把默认光标改为 size -10 ，以后如果还要在尾部添加数据恐怕，如果不在意的话，又会出 bug 吧。

# 让我重新写一遍评分表

 	**Phase 判断的顺序 Score 权重的顺序** 

   	**P4 在 P3 和 P2 之后判断  [0/1][0/1]表示一个为1一个为0**
   	**死棋 S0**
   	**可重复的中 ，以 * 在前的优先**

        
        //P0 S0 1[][][]*1/ 1[][]*[]1  / 1[][]*1/ 1[]*[]1 / 1*[]1 / 1*1
            // else +
        //P1 SA 胜利 ->   *2222  /   22*22   / 2*222
        //P2 SB下一步胜利 -> (0||2)2*22(0||2)  /  (0||2)*222(0||2)                    
        //P3 SC下一步 多半无用 -> [0|1]*222[0|1]  / [0|1]2*22[0|1] 
        //P4  SD     0*220 / 02*20 / 
        //P5  SE      [0|1]*22[0|1] / [0|1]2*2[0|1] /  
        //P6  SC     [0|2]*22[0|2]  /   [0|2]2*2[0|2]         
        //P7  SF 活的2        (0//2)[]*2[](0//2)
                    //2+1-(指数基数与P不同)
        //P8  SG   半死的2     [0|1][]*2[][0|1]
                    //2+1-
