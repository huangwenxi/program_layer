1:分层的好处
	a.代码的层次感提升，便于后期维护和项目任务分配
	b.各层只做与自己相关的事情
	c.将协议与应用逻辑分割


//2018/1/1
基本搭建好了代码的框架，一共分成三层
a.应用程序
b.核心层
c.设备相关层

增加一个新建设备的步骤：
a.新建设备相关层devnamexxx_driver.c和devnamexxx_driver.h并实现和设备相关的读写设置函数
b.在main.c->core_init()添加相关代码将设备注册到核心层来统一管理
c.devnamexxx_test.c为设备的应用层实现逻辑