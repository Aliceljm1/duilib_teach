# 简介
此项目来源于github,用于我公司[安徽戴特教育科技有限公司](http://www.datedu.cn/)新人入职培训Duilib, 目前的第一个修改后的示范demo是ListDemo.
主要目的是通过相关代码起到入门介绍的作用，其中也包括c++和visual studio的相关知识

算法学习好去处
https://github.com/Aliceljm1/100C

c语言刷题好去处
http://www.dotcpp.com/oj/problemset.html


学习目标：
1.基础的c/c++语法知识
2.良好的编码规范，包括类名，函数名，参数变量名。表意准确，简洁，可读性强，一眼就知含义
3.初步的抽象层次能力，将一个复杂问题划分为若干个函数。
4.学会使用duilib创建UI窗口，编写简单的业务逻辑代码


# 课程列表

# 课程1 
学习ListDemo,如何运行代码，关键流程和相关函数OnCreate，Notify
最大化最小化的功能实现。
修改皮肤xml文件,对照“属性列表.xml”学习当前皮肤中使用了哪些属性和控件
自行修改属性，观察结果，查找并解答注释中的TODO和提问


# 课程2 
编写函数在点击search按钮之后当前窗口围绕左上角旋转，旋转半径为50，考虑多线程，定时器

# 课程3
学习布局，将《duilib入门和xml培训布局案例》文件夹中的布局文件全部拷贝到skin\\ListRes\\中，
然后修改 	CDuiString GetSkinFile() 的代码来切换布局文件，
要求自己编写要给复杂的包含垂直布局，水平布局组合的Ui文件，同时修改窗口圆角，等等熟悉，发挥自己的创作醒性



# 课程4 
讲解内容：
1.git的简单使用，fork当前教程建立自己的项目，准备提交代码
2.stdafx.h的用法，Windows的dll加载机制（显示和隐式加载dll，LoadLibrary），介绍工具depends.exe的使用
介绍procexp.exe查看进程加载的相关资源（dll, 句柄，线程，端口，权限）
3.duilib是如何被引用的

作业：
模拟qq，或者微信登陆窗口输入用户名密码，请求web接口，验证用户名密码，然后校验
自行安装node.js客户端，下载代码运行：
https://github.com/Aliceljm1/NodeDemo.git
自行搜索互联网资源查找libcurl的用发，发送HTTP请求
https://gitee.com/search?utf8=%E2%9C%93&q=libcurl++demo&type=
可以自行发挥创造性，添加一些异常处理和UI交互.


# 课程5
改用http://localhost:8081/autologin接口登陆，解析出用户信息用CUserInfo模型装载，相关解析代码放到CUserControler中，然后创建新的窗口显示这些信息
其他字段自己完善，要求新的窗口需要继承WindowImplBase，而非CWindowWnd，仔细观察区别体会优点
CUserControler中的其他函数自己实现。仔细体会使用不同的类将各个抽象层次的逻辑代码拆分出来的好处。每一层只负责一个维度的逻辑，
每个层都很纯粹，可维护性，可复用性很强。
将之前的字符串操作方法，网络访问方法都重构到对应的utils类中，保持每个类的纯粹性

# 课程6
练习抽出dll.lib库，分模块开发，将model和controler层分别拆分出lib，和dll调用。学会模块化开发
参考： vs关键配置相关信息.docx

# 课程7
练习使用sqlite数据库，将登陆成功之后服务端返回的数据存储到数据库中使用（\3rd\sqlite\sqlite3.lib）
下次启动软件自动读取数据库中的登陆历史记录，供用户选择点击直接登陆。 

# 课程8
学习wtest项目中的语法知识

# 课程9
学习errordemo的项目中的典型错误知识，包括空指针，野指针等等常见错误



# Duilib
以下为作者原文
# 
Duilib是一个Windows下免费开源的DirectUI界面库，由于简约易扩展的设计以及稳定高效的实现被各大互联网公司普遍接受，广泛应用于包括IM、视频客户端、股票行情软件、导航软件、手机辅助软件、安全软件等多个行业的众多pc客户端软件。Duilib还在不断的发展中，在文档、例子、动画、渲染引擎等多个方面将持续改进。

欢迎为Duilib提供功能改进、代码修补、bug反馈、使用文档和献计献策，让我们一起把Duilib做的更好！当然也欢迎你对duilib项目进行捐助（可以使用支付宝或微信扫码）。



