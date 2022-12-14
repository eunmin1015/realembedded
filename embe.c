#include <getopt.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>
#include <linux/fb.h>
#include <time.h>

#include "led.h"
#include "fnd.h"
#include "acc.h"
#include "button.h"
#include "touch.h"
#include "buzzer.h"
#include "textlcd.h"
#include "colorled.h"
#include "Temperature.h"
#include "bitmap.h"
#include "embe.h"

BUTTON_MSG_T B;
TOUCH_MSG_T recvMsg;
int msgID;
int fd;
int userBall[3] = {0,}; // 사용자의 볼을 저장할 int형 배열 

int setInit(void){
	
	bitmainfunc("set.bmp");
	
    pwmLedInit();
	ledlibinit();
	buzzerInit();
	buttonInit();
	touchInit();
   //각 기기 초기 설정
	text("Embedded System", "TEAM PROJECT");
	sleep(1);
	
	fnd(000000,MODE_STATIC_DIS );
	
	int ondo = 0;
	ondo = getTem() - 5;
	char temperature[20];
	sprintf(temperature, "temperature : %d", ondo);
   //온도를 읽어오고 textlcd 에 띄우기 위해서 문자열 저장
   
	if(ondo < 20) 
		{ bitmainfunc("COld.bmp"); text(temperature, "COLD TO WORK");}
	else if(ondo >= 20 && ondo < 26)
		{bitmainfunc("Good.bmp"); text(temperature, "GOOD TO WORK!");}
	else 
		{bitmainfunc("Hot.bmp"); text(temperature, "HARD TO WORK!");}
    //온도에 맞는 안내메세지를 textlcd에 띄움
    
	sleep(2);
	
	return 0;
}


int setExit(void){
	pwmInactiveAll();
	ledlibexit();
	buzzerExit();
	buttonExit();
	//열어놓은 파일 전부 종료

		
}
int userBallarrinput(int a)
{
	if(userBall[0] == 0)
	{
		userBall[0] = a;
	}
	else if (userBall[0] != 0 && userBall[1] == 0)
	{
		userBall[1] = a;
	}
	else if(userBall[0] != 0 && userBall[1] != 0 && userBall[2] == 0)
	{
		userBall[2] = a;
	}
	else
	{
		printf("입력이 완료되었습니다");
		printf("배열 -> %d %d %d",userBall[0],userBall[1],userBall[2]);
		return 1;
	}
}


int userballinsert(void)
{
		int statement0 =0;
		int statement1 =0;
		int statement2 =0;
		int statement3 =0;
		int statement4 =0;
		int statement5 =0;
		int statement6 =0;
		int statement7 =0;
		int statement8 =0;
		int statement9 =0;
		int cnt = 0;
	
	while(1){
		  msgrcv(msgID, &recvMsg, sizeof(TOUCH_MSG_T)- sizeof(long int), 0, 0);
		        switch (recvMsg.keyInput)
        {
            case 999: 
                    if(recvMsg.pressed==1)
                { 
                    if((0 < recvMsg.x) && (recvMsg.x  < 320) && (0<recvMsg.y) && (recvMsg.y<200) && statement0!=1)  //1
					{
						printf("입력완료");
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(1);
						cnt++;
						continue;
                    }
                    else if((320 < recvMsg.x )&& (recvMsg.x  < 671) && (0<recvMsg.y )&& (recvMsg.y<200) && statement1 != 1) //2
                     {
						printf("입력완료");
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(2);
						cnt++;
						continue;
					}
                    else if ((671 < recvMsg.x) && (recvMsg.x  < 1024) && (0<recvMsg.y) && (recvMsg.y<200) && statement2!=1) //3
                    {
						printf("입력완료");
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(3);
						cnt++;
						continue;
					}
					else if ((0 < recvMsg.x) && (recvMsg.x  < 320) && (200<recvMsg.y )&& (recvMsg.y<400) && statement3!=1) //4
                    {
						printf("입력완료");
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(4);
						cnt++;
						continue;
					}
                    else if ((320 < recvMsg.x )&& (recvMsg.x  < 671) && (200<recvMsg.y) && (recvMsg.y<400) && statement4!=1) //5
                    {
						printf("입력완료");
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(5);
						cnt++;
						continue;
					}
                    else if ((671 < recvMsg.x) && (recvMsg.x  < 1024)&& (200<recvMsg.y) && (recvMsg.y<400) ) //6
                    {
						printf("입력완료");
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(6);
						cnt++;
						continue;
					}
                    else if ((0 < recvMsg.x) && (recvMsg.x  < 320) && (400<recvMsg.y )&& (recvMsg.y<600) &&statement6!=1) //7
                    {
						printf("입력완료");
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(7);
						cnt++;
						continue;
					}
                    else if ((320 < recvMsg.x )&& (recvMsg.x  < 671)&& (400<recvMsg.y) && (recvMsg.y<600) && statement7!=1)  //8
                    {
						printf("입력완료");
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(8);
						cnt++;
						continue;
					}
                    else if ((671 < recvMsg.x) && (recvMsg.x  < 1024) && (400<recvMsg.y) && (recvMsg.y<600) &&statement8!=1)  //9
                    {
						printf("입력완료");
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(9);
						cnt++;
						continue;
					}
				
break;
    }
    	if(cnt == 3)
    	return 0;
}
}
}

int baseballgame(void){
	int fd;
	int computerBall[3]; // 컴퓨터의 볼을 저장할 int형 배열 
	int i, j, k; // 반복을 위한 변수 
	int temp; // 난수 중복 체크를 위한 변수 
	int count = 1; // 회차를 확인할 변수 9회까지 가능 
	int strike = 0; // 스트라이크의 수를 세기 위한 변수 
	int ball = 0; // 볼의 수를 세기 위한 변수 
	int cnt = 0;
	
	bitmainfunc("Baseball_Start1.bmp");
	text("GAME START", "        ");
	sleep(5);
	
	srand((unsigned)time(NULL)); 
	for (i = 0; i < 3; i++) 
	{ 
		temp = (rand() % 9) + 1; // temp변수에 현재 랜덤 값을 저장 //왜... 1~6이죠?
		computerBall[i] = temp; // temp값을 컴퓨터의 볼에 저장 
    	for (j = 0; j < i; j++){ // 현재 추가된 만큼 반복하며 
        	if (temp == computerBall[j] && i != j) // 만약 현재 temp값과 이전에 넣은 값 중 동일한 게 있다면 
            	i--; // i의 값을 줄여 다시 이전으로 돌아가도록
		}
	}
	
		
	while (1) // 숫자야구 게임 시작 

  	{ 	bitmainfunc("Keypad2.bmp");
		text("inning start!", "   ");	
    	printf("[%d회차 숫자야구]\n", count); 
    	ledonoff(count-1,1);
		printf("computer num -> %d,%d,%d\n",computerBall[0],computerBall[1],computerBall[2]);
		
		userballinsert();
    	printf("user num -> %d,%d,%d\n",userBall[0],userBall[1],userBall[2]);
    	while(1)
    	{
			text("inning start!", "insert num");
			
	printf("저장된 숫자 %d %d %d", userBall[0],userBall[1],userBall[2]);
	
	if(userBall[0] < 1 || userBall[0] > 9 || userBall[1] < 1 || userBall[1] > 9 || userBall[2] < 1 || userBall[2] > 9) 

{ // 입력한 숫자가 1 ~ 9 숫자가 아니면 다시 입력받도록 

printf("범위 외의 숫자를 입력하시면 안됩니다.\n"); 

continue; 

} 

else if(userBall[0] == userBall[1] || userBall[0] == userBall[2] || userBall[1] == userBall[2]) 

{ // 입력한 숫자 중에 중복된 게 있으면 다시 입력받도록 

printf("중복된 숫자를 입력하시면 안됩니다.\n"); 

continue; 

} 

break; // 아무 문제 없을 경우 반복 종료 
}
		ball = 0;
		strike = 0;
      	for (i = 0; i < 3; i++) // computerBall 1~3번째에 따라 각 userBall 1~3번째를 확인하기 위한 반복 
          	for (j = 0; j < 3; j++) 
              	if (computerBall[i] == userBall[j]) // computerBall과 userBall의 값이 같다면 
                  	if (i == j) // 같은 위치일 경우 
                    	strike++; // 스트라이크 개수 증가 
                  	else // 다른 위치일 경우
                      	ball++; // 볼 개수 증가 

  /*----------------------- 확인한 결과를 출력 -----------------------------*/

  printf("[결과]스트라이크 : %d, 볼 : %d\n\n", strike, ball); //
if(strike == 3) // 만약 스트라이크 개수가 3개이면 승리 
{ 
	buzzerPlaySong(musicScale[0]);
				pwmSetPercent(0,0);
				pwmSetPercent(0,1);
				pwmSetPercent(0,2);
				usleep(500000);
			buzzerPlaySong(musicScale[2]);
				pwmSetPercent(0,0);
				pwmSetPercent(100,1);
				pwmSetPercent(100,2);
				usleep(500000);
			buzzerPlaySong(musicScale[4]);
				pwmSetPercent(0,0);
				pwmSetPercent(0,1);
				pwmSetPercent(0,2);
				usleep(500000);
			buzzerPlaySong(musicScale[5]);
				pwmSetPercent(0,0);
				pwmSetPercent(100,1);
				pwmSetPercent(100,2);
				usleep(500000);
			buzzerStopSong();
				pwmSetPercent(0,0);
				pwmSetPercent(0,1);
				pwmSetPercent(0,2);
				usleep(500000);
				pwmSetPercent(0,0);
				pwmSetPercent(100,1);
				pwmSetPercent(100,2);

printf("***** 승리했습니다. *****\n\n"); 
//userBall[0] = 0;
//userBall[1] = 0;
//userBall[2] = 0;



break; 

} 

else if(count == 8) // 만약 9회차인데도 승리하지 못하면 패배 

{ 

printf("***** 패배했습니다.. 정답 : %d %d %d *****\n\n", computerBall[0], computerBall[1], computerBall[2]); 

break; 

}

bitmainfunc("baseball_yesno.bmp"); 


      count++; 
}
  	return 0;

}



/*--------------------------------------------------------------------

사용자 공 선택 함수
가속도 센서 값을 항상 1초에 한 번씩 받아옴 
버튼의 볼륨 다운 키를 누루는 신호가 들어오는 순간 가속도 센서의 값을 읽어 화면 전환, 위치 결정
결정한 위치에 따라서 공의 위치가 달라지는 화면 전환
이 함수를 부르면 공의 최종 위치가 정수형으로 반환됨.

------------------------------------------------------------------*/

int select_ball_func (void)
{	
   
	accInit(); // 가속도 센서 활성화 
	ledlibinit();
    int accel;
	int ball_num ; // 사용자가 선택한 장소에 따라 번호 메기기
	
	BUTTON_MSG_T B;
	int returnValue = 0;
	printf("hello");
	
	sleep(1);
	
	int msgID2 = msgget (1123, IPC_CREAT|0666);


	
	if (msgID2 == -1){
	printf ("Cannot get msgQueueID, Return!\r\n");
	return -1;
	}

	buttonInit();
	
	while(1)
	{
		returnValue = msgrcv(msgID2, &B, sizeof(unsigned short)*2 + sizeof(int), 0, 0);
		printf("%d/n", returnValue);
		accel = getAcc(); // 가속도 값 1초에 한 번씩 받아오기
		printf("accel: %d", accel);
		sleep(1);

        /*키트를 움직여서 공위치 선택*/
        if(accel <= -10000)
        {   
		                  bitmainfunc("soccerball_left.bmp");
                         printf(" accel : %d", accel);
	               		 ball_num = 1;
          	               sleep(1);
		}
		else if(accel >= -10000 && accel <= 10000)
		{
							bitmainfunc("soccerball_center.bmp");
            				printf(" accel : %d", accel);
							ball_num = 2;
        					sleep(1);
		}
		else if(accel >= 10000)
		{
							bitmainfunc("soccerball_right.bmp");
            				printf(" accel : %d", accel);
							ball_num = 3;
            				sleep(1);
        }

        /*원하는 위치에 공이 있으면 키를 선택해서 그 위치 고정*/
		if (B.messageNum == EV_KEY){
			switch(B.keyInput)
			{
				case KEY_VOLUMEDOWN : 
					if(B.pressed == 1)
					{
						ledonoff(1, 1);
        				printf("%d\n", accel);
        				sleep(1);
						if(accel <= -10000)
						{   
							bitmainfunc("newball_left.bmp");
           					printf(" accel : %d", accel);
							ball_num = 1;
          					sleep(1);
						}
						else if(accel >= -10000 && accel <= 10000)
						{
							bitmainfunc("newball_center.bmp");
            				printf(" accel : %d", accel);
							ball_num = 2;
        					sleep(1);
						}
						else if (accel >= 10000)
						{
							bitmainfunc("newball_right.bmp");
            				printf(" accel : %d", accel);
							ball_num = 3;
            				sleep(1);
						}
					}
			}
		}
	} 
		
		/*while (B.messageNum == EV_KEY && B.keyInput == KEY_VOLUMEDOWN && B.pressed) // 버튼이 눌릴 동안 동작
		{		
			if(accel <= -10000)
			{   
				bitmainfunc("soccerball_left.bmp");
           		printf(" select : %d", accel);
				ball_num = 1;
          		sleep(1);
			}
			else if(accel >= -10000 && accel <= 10000)
			{
				bitmainfunc("soccerball_center.bmp");
            	printf(" select : %d", accel);
				ball_num = 2;
        	sleep(1);
			}
			else if (accel >= 10000)
			{
				bitmainfunc("soccerball_right.bmp");
            	printf(" select : %d", accel);
				ball_num = 3;
            	sleep(1);
			}
			break;
		}*/
	return ball_num; // 공 번호 반환해 주기
}



int soccergame(void)
{    	
	bitmainfunc("soccer_start.bmp");
	text("GAME START", "	");

	int i;

	for(i=0; i<3; i++) // 3판 돌리기
	{ 
	 /*----------------------------- 사용자의 최종 위치 받아오기 ---------------------- */
		int player_num; // 리턴 받을 사용자의 장소 번호

		player_num = select_ball_func(); // 사용자의 장소 최종 위치 불러오기
    
	 /*--------------------------- 랜덤한 위치 받아오기 -------------------- */
		int rand_num; // 랜덤하게 받아올 숫자
		srand(time(NULL)) ;
	
		rand_num =rand() % 3 + 1; // 1, 2, 3 중 랜덤한 값을 무작위로 받아와서 저장하기

	 /*---------------------------------점수 조정하기-----------------------------------*/
		int soccerscore = 0; // 점수를 저장하는 변수	

		if (rand_num == player_num) // 게임 결과 비교 (승)
		{
			fndDisp (soccerscore + 1, 0); 
			soccerscore = soccerscore + 1;
		}

		else if (rand_num != player_num) // 패
		{	
			if (soccerscore >= 1) // 1점 이상 획득했을 때
			{
				fndDisp (soccerscore -1, 0);
				soccerscore = soccerscore - 1;
		}

		else if (soccerscore < 1) // 0점일 때 음수로 가는 것을 방지
		{
			fndDisp (0, 0);
			soccerscore = 0;
		}
	}	

}
	

	text("Finish","	");
	return 0;
}

