/*
created by huangwenxi in 2017/12/30
//////////////////////////////////
*/
#ifndef _DEV_OPERATIONS_H
#define _DEV_OPERATIONS_H

struct list_head
{
	struct dev_operations *prev;
	struct dev_operations *next;
};
struct dev_operations
{
	char *name;//设备名称
	int fd;//文件描述符
	int state;//-1 IDEL 表示该节点空闲可用，0表示该节点被占用
	bool (*open)(const char dev[]);
	bool (*close)(const char dev[]);
	bool (*set_freq)(int fd, const char data[]);
	bool (*query_freq)(int fd, char data[]);
	struct list_head list;
};

/************************提供给应用程序的接口调用************************/

//将设备操作结构体注册到核心层
int register_dev_operations(struct dev_operations *p);
int unregister_dev_operations(struct dev_operations *p)
//de
//选中操作设备
//int select_dev(const char *name);
//打开设备
bool open(const char *dev);
//读取设备数据
int read(const char *dev, char data[]);
//写设备数据
int write(const char *dev, const char data[]);

#endif