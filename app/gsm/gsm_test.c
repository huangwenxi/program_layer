/*
created by huangwenxi in 2018/1/1
///////////////////////////////////
*/
#include "dev_operations.h"
int gsm_main()
{
	int ret;
	char data[120];
	ret = open("gsm");
	if(ret >= 0)
	{
		set_freq("gsm",116);
		query("gsm", data);
		printf("the freq result is %d\n", data[0]);
	}
	return 0;
}