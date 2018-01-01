/*
created by huangwenxi in 2017/12/30
///////////////////////////////////
*/
#include "receive_manager.h"
static char buf[16];
static int fd;
static bool init(void);
static int read(char data[]);
static int write(const char data[]);

static struct dev_operations gsm_dev = 
{
	.name = "arm_recv",
	.state = 0,//used
	.fd = -1,
	.open = gsm_init,
	.init = gsm_init,
	.read = gsm_read,
	.write = gsm_write,
};
/*
des:打开设备
不同的设备打开的方式不一样，gsm设备和arm通过串口连接，wcdma设备和arm通过网络丽连接，具体的
*/
static int gsm_open(char dev[])
{
	/*gsm设备打开的代码实现,串口还是网络*/

}
static int gsm_read(int fd, char data[])
{
	
}
static int gsm_write(int fd, const char data[])
{

}
static bool query_freq(int fd, char data[])
{
	int ret;
	char buf[120];
	ret = gsm_read(fd, buf);
	if (ret >= 0)
	{
		/*解包*/
	}
	/*存放查询到的频点信息存放到 data*/

}
static bool set_freq(int fd, const char data[])
{
	/*组包*/

	/*发送*/
	gsm_write(fd, data);
}

/*注册gsm 设备到核心控制层*/
 bool gsm_module_init(void)
{
	register_dev_operations(gsm_dev);
}
/*从核心控制层删除设备*/
 bool gsm_modue_exit(void)
{
	unregister_dev_operations(gsm_dev);
}
