#include <getopt.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR//
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>
#include <linux/fb.h>
#include <time.h>


#include "led.h"
#include "fnd.h"
#include "acc.h"
#include "button.h"
#include "buzzer.h"
#include "textlcd.h"
#include "colorled.h"
#include "Temperature.h"
#include "bitmap.h"
#include "embe.h"
#include "touch.h"

BUTTON_MSG_T B;
TOUCH_MSG_T recvMsg;
int msgID;
int fd;

int main(int argc, char* argv[]) {//
   
	setInit(); //각종 기기들을 키고  초기 설정을 해준다.
	bitmainfunc("gamestart.bmp"); //메인 메뉴 사진을 띄운다.
    while(1)
    {
		msgrcv(msgID, &recvMsg, sizeof(TOUCH_MSG_T)- sizeof(long int), 0, 0);
         
        switch (recvMsg.keyInput)
        {
            case 999: // X 341 682 Y 200 400/
                    if(recvMsg.pressed==1)
                { 
                    if(450 < recvMsg.x && recvMsg.x  < 520 && 200<recvMsg.y && recvMsg.y<430)
                    {
						bitmainfunc("gamestart.bmp");
                        baseballgame();
                    }
                      if(530 <recvMsg.x && recvMsg.x < 1024 && 200 <recvMsg.y && recvMsg.y < 430)
                    {
                          bitmainfunc("gamestart.bmp");
                        select_ball_func();
                    }
                }
break;
    }
	}
return 0;
}
