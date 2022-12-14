#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "led.h"

static unsigned int ledvalue = 0;
static int fd = 0;
int ledonoff(int lednum, int onoff)
{
	int i = 1;
	i = i<<lednum;
	ledvalue = ledvalue& (~i);
	if(onoff != 0)
	{
		ledvalue |= i;
	}
	write(fd,&ledvalue,4);
}

int ledalloff(void)
{
	ledonoff(0,0);
	ledonoff(1,0);
	ledonoff(2,0);
	ledonoff(3,0);
	ledonoff(4,0);
	ledonoff(5,0);
	ledonoff(6,0);
	ledonoff(7,0);
}

int led0s1b(void)
{
	ledonoff(4,1);
		sleep(2);
}

int led0s2b(void)
{
	ledonoff(4,1);
	ledonoff(5,1);
		sleep(2);
}

int led0s3b(void)
{
	ledonoff(4,1);
	ledonoff(5,1);
	ledonoff(6,1);	sleep(2);
}

int led1s0b(void)
{
	ledonoff(0,1);
		sleep(2);
}

int led1s1b(void)
{
	ledonoff(0,1);
	ledonoff(4,1);
		sleep(2);
}

int led1s2b(void)
{
	ledonoff(0,1);
	ledonoff(4,1);
	ledonoff(5,1);
		sleep(2);
}

int led2s0b(void)
{
	ledonoff(0,1);
	ledonoff(1,1);
	sleep(2);
}

int led2s1b(void)
{
	ledonoff(0,1);
	ledonoff(1,1);
	ledonoff(4,1);
	sleep(2);
}

int led3s0b(void)
{
	ledonoff(0,1);
	ledonoff(1,1);
	ledonoff(2,1);
	sleep(2);
}

int ledlibinit(void)
{
	fd = open("/dev/periled", O_WRONLY);
	ledvalue = 0;
}

int ledlibexit(void)
{
	ledvalue = 0;
	ledonoff(0,0);
	close(fd);
}
