/*
created by huangwenxi in 2018/1/1
///////////////////////////////////
*/
#include "dev_operations.h"
#include "gsm_driver.h"
static int core_init(void);
int main()
{
	core_init();
	gsm_main();//可以考虑新开启一个线程，看程序功能需要
}

static int core_init(void)
{
	gsm_module_init();
}