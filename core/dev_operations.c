/*
created by huangwenxi in 2017/12/30
///////////////////////////////////
目前将软件分层为三层
1:应用程序层
2:核心管理层
3:驱动层
文件dev_operations.c作为核心管理层。
核心管理层：
	向上提供应用程序需要调用的统一接口，向下管理不同的设备，设备可以有gsm设备，wcdma设备，tds设备，4g设备等。

*/
#include "dev_operations.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

static struct dev_operations *__dev_list_head = NULL;
static struct dev_operations *__dev_list_current = NULL;
static pthread_mutex_t *list_register_mutex=NULL;

/**********************************提供给应用程序调用的接口**************************************/
/*
将dev_operations注册到核心层管理，register_dev_oparations和unregister_dev_operations通过自，自旋锁互斥访问
p:待注册的设备操作结构指针
return:操作结果

*/
int register_dev_operations(struct dev_operations *p)
{
	struct dev_operations *list_tmp;
	if(list_register_mutex=NULL)
	{
		pthread_mutex_init(list_register_mutex,NULL);
	}
	pthread_mutex_lock(list_register_mutex);
	if(!__dev_list_head)
	{
		__dev_list_head = p;
		p->list.next = NULL;
	}
	else
	{
		list_tmp = __dev_list_head;
		while(list_tmp->list.next)
		{
			if(list_tmp->state == -1)//空闲 
			{
				list_tmp->state = 0;
				/*将p的值拷贝到list_tmp*/
				memcpy(list_tmp->name, p->name, strlen(p->name))
				list_tmp->open = p->open;
				list_tmp->read = p->read;
				list_tmp->write = p->write;
				p->list.next = NULL;
				pthread_mutex_unlock(list_register_mutex);
				return 0;
			}
			list_tmp = list_tmp->list.next;
		}
		list_tmp->list.next = p;
		p->list.next = NULL;
		pthread_mutex_unlock(list_register_mutex);
		return 0;
	}
	pthread_mutex_unlock(list_register_mutex);
	return -1;
}
/*
删除一个设备节点的时候，将该设备节点的state改为IDEL
*/
int unregister_dev_operations(struct dev_operations *p)
{
	struct dev_operations *list_tmp;
	if(list_register_mutex==NULL)
	{
		pthread_mutex_init(list_register_mutex);
	}
	pthread_mutex_lock(list_register_mutex);
	if (__dev_list_head)
	{
		/* code */
		list_tmp = __dev_list_head;
		while(list_tmp!=NULL)
		{
			if (strcmp(p->name, list_tmp->name) == 0)
			{
				list_tmp->state = -1;//空闲
				memset(list_tmp->name, 0, strlen(list_tmp->name));//name 初始化
				pthread_mutex_unlock(list_register_mutex);
				return 0;
				
			}
			list_tmp = list_tmp->list.next;
		}
	}
	pthread_mutex_unlock(list_register_mutex);
	return -1;
}

struct dev_operations* query_dev(char *dev)
{
	struct dev_operations* list_tmp;
	if (__dev_list_head)
	{
		/* code */
		list_tmp = __dev_list_head;
		while(list_tmp!=NULL)
		{
			if (strcmp(list_tmp->name,dev->name) == 0)
			{
				/* code */
				return list_tmp;
			}
			list_tmp = list_tmp->list.next;
		}
	}
	return NULL;
}
/*
des:如果当前的设备已经打开，则不再重复调用open系统调用，只是返回当前的管理设备的文件描述符
return : -1 设备节点已经被打开或者设备节点在还未注册到核心
*/

bool open(const char *dev)
{
	struct dev_operations* list_tmp;
	int fd;
	list_tmp = query_dev(dev);//在设备链表里找到该设备节点
	if (list_tmp!=NULL && list_tmp->fd < 0)//设备节点存在并且当前设备还未被打开过
	{
		/* code */
		fd = list_tmp->open(dev);//调用底层的驱动程序打开设备并返回fd
		list_tmp->fd = fd;//存放fd
		return 0;
	}
	return -1;
}
/*
des:关闭设备的设备描述符 
return : 0 代表设备关闭成功 -1 代表设备不存在或者当前不处于打开的状态或者设备关闭失败
*/

bool close(const char *dev)
{
	struct dev_oparetions* list_tmp;
	list_tmp = query_dev(dev);
	if(list_tmp!= NULL && list_tmp->fd > 0)//设备节点存在并且设备已经被打开
	{
		list_tmp->close(list_tmp->fd);
		list_tmp->fd = -1;
		return 0;
	}
	return -1;
}
/*
des:设置设备的频点信息,应用层接口
return: -1 表示设置频点信息失败 0 表示设置设备的频点信息失败
*/
bool set_freq(char *dev, const char data[])
{
	struct dev_operations* list_tmp;
	list_tmp = query_dev(dev);
	if (list_tmp!=NULL && list_tmp->fd > 0)//设备是否注册到核心管理层并且设备已经被打开
	{
		/* code */
		list_tmp->set_freq(fd, data);
		return 0;
	}
	return -1;
}
/*
des:查询设备的频点信息,应用层接口
return: -1查询设备的频点信息失败 0 查询设备的频点信息成功
*/
bool query_freq(char *dev, char data[])
{
	struct dev_operations* list_tmp;
	list_tmp = query_dev(dev);
	if (list_tmp!=NULL && list_tmp->fd >0)/设备是否注册到核心管理层并且设备已经被打开
	{
		/* code */
		list_tmp->query_freq(fd, data);
		return 0;

	}
	return -1;
}

