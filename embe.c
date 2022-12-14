#include <getopt.h>
#include <linux/types.h>//
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

#define MODE_COUNT_DIS "c"

BUTTON_MSG_T B;
TOUCH_MSG_T recvMsg;
int msgID;
int fd;
int userBall[3] = {0,}; // 사용자의 볼을 저장할 int형 배열 

int setInit(void){
	
	bitmainfunc("24set.bmp");
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

	


int backtothemain(void)
{
	setInit(); //각종 기기들을 키고  초기 설정을 해준다.
	bitmainfunc("24set.bmp"); //메인 메뉴 사진을 띄운다.
    while(1)
    {
		msgrcv(msgID, &recvMsg, sizeof(TOUCH_MSG_T)- sizeof(long int), 0, 0);
         
        switch (recvMsg.keyInput)
        {
            case 999: // X 341 682 Y 200 400/
                    if(recvMsg.pressed==1)
                { 
                    if(0 < recvMsg.x && recvMsg.x  < 512 && 300<recvMsg.y && recvMsg.y<500)
                    {
						bitmainfunc("24set.bmp");
                        baseballgame();
                    }
                      if(512 <recvMsg.x && recvMsg.x < 1024 && 300 <recvMsg.y && recvMsg.y < 500)
                    {
                          bitmainfunc("24set.bmp");
                        soccergame();
                    }
                }
break;
    }
	}
}

int userBallclear(void)
{
	userBall[0] = 0;
	userBall[1] = 0;
	userBall[2] = 0;
}

int baseballrestart(void)
{
	
	    while(1)
    {
		msgrcv(msgID, &recvMsg, sizeof(TOUCH_MSG_T)- sizeof(long int), 0, 0);
         
        switch (recvMsg.keyInput)
        {
            case 999: // X 341 682 Y 200 400/
                    if(recvMsg.pressed==1)
                { 
                     if(0 < recvMsg.x && recvMsg.x  < 512 && 300<recvMsg.y && recvMsg.y<500)
                    {
						baseballgame();
                    }
                      if(512 <recvMsg.x && recvMsg.x < 1024 && 300 <recvMsg.y && recvMsg.y < 500)
                    {
						backtothemain();
                    }
                }
break;
    }
	}
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
		int cnt = 0;
	
	while(1){
		  msgrcv(msgID, &recvMsg, sizeof(TOUCH_MSG_T)- sizeof(long int), 0, 0);
		        switch (recvMsg.keyInput)
        {
            case 999: 
                    if(recvMsg.pressed==1)
                { 
                    if((0 < recvMsg.x) && (recvMsg.x  < 320) && (0<recvMsg.y) && (recvMsg.y<200))  //1
					{
						
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(1);
						cnt++;
						continue;
                    }
                    else if((320 < recvMsg.x )&& (recvMsg.x  < 671) && (0<recvMsg.y )&& (recvMsg.y<200) )
                     {
						
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(2);
						cnt++;
						continue;
					}


                    else if ((671 < recvMsg.x) && (recvMsg.x  < 1024) && (0<recvMsg.y) && (recvMsg.y<200) )
                    {
						
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(3);
						cnt++;
						continue;
					}

					else if ((0 < recvMsg.x) && (recvMsg.x  < 320) && (200<recvMsg.y )&& (recvMsg.y<400))

                    {
						
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(4);
						cnt++;
						continue;
					}

                    else if ((320 < recvMsg.x )&& (recvMsg.x  < 671) && (200<recvMsg.y) && (recvMsg.y<400))

                    {
						
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(5);
						cnt++;
						continue;
					}
                    else if ((671 < recvMsg.x) && (recvMsg.x  < 1024)&& (200<recvMsg.y) && (recvMsg.y<400) ) //6
                    {
						
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(6);
						cnt++;
						continue;
					}
                    else if ((0 < recvMsg.x) && (recvMsg.x  < 320) && (400<recvMsg.y )&& (recvMsg.y<600))

                    {
						
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(7);
						cnt++;
						continue;
					}


                    else if ((320 < recvMsg.x )&& (recvMsg.x  < 671)&& (400<recvMsg.y) && (recvMsg.y<600))
                    {
						
						bitmainfunc("Keypad2.bmp");
						userBallarrinput(8);
						cnt++;
						continue;
					}

                    else if ((671 < recvMsg.x) && (recvMsg.x  < 1024) && (400<recvMsg.y) && (recvMsg.y<600))

                    {
						
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
	int count = 0; // 회차를 확인할 변수 9회까지 가능 
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
		fnd(MODE_STATIC_DIS,count+1);	
    	printf("[%d회차 숫자야구]\n", count); 
    	userBallclear();
    	//ledonoff(count-1,1);
    	ledalloff();
		printf("computer num -> %d,%d,%d\n",computerBall[0],computerBall[1],computerBall[2]);
		
		userballinsert();
    	printf("user num -> %d,%d,%d\n",userBall[0],userBall[1],userBall[2]);
    	

    	while(1)
    	{
			text("inning start!", "insert num");
			
	printf("저장된 숫자 %d %d %d", userBall[0],userBall[1],userBall[2]);
	

if(userBall[0] == userBall[1] || userBall[0] == userBall[2] || userBall[1] == userBall[2]) 

{ // 입력한 숫자 중에 중복된 게 있으면 다시 입력받도록 

printf("중복된 숫자를 입력하시면 안됩니다.\n"); 
			buzzerPlaySong(musicScale[4]);
				pwmSetPercent(0,0);
				pwmSetPercent(0,1);
				pwmSetPercent(0,2);
				usleep(500000);
				buzzerPlaySong(musicScale[4]);
				pwmSetPercent(0,0);
				pwmSetPercent(0,1);
				pwmSetPercent(0,2);
				usleep(500000);
				buzzerPlaySong(musicScale[4]);
				pwmSetPercent(0,0);
				pwmSetPercent(0,1);
				pwmSetPercent(0,2);
				usleep(500000);
				buzzerPlaySong(musicScale[4]);
				pwmSetPercent(0,0);
				pwmSetPercent(0,1);
				pwmSetPercent(0,2);
				usleep(500000);
				buzzerStopSong();
				pwmSetPercent(0,0);
				pwmSetPercent(0,1);
				pwmSetPercent(0,2);
				usleep(500000);
				pwmSetPercent(0,0);
				pwmSetPercent(100,1);
				pwmSetPercent(100,2);
				baseballgame();

break;
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
  
  if(count == 8) // 만약 9회차인데도 승리하지 못하면 패배 

{ 
				buzzerPlaySong(musicScale[7]);
				pwmSetPercent(0,0);
				pwmSetPercent(100,1);
				pwmSetPercent(100,2);
				usleep(500000);
				buzzerPlaySong(musicScale[1]);
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

printf("***** 패배했습니다.. 정답 : %d %d %d *****\n\n", computerBall[0], computerBall[1], computerBall[2]); 
bitmainfunc("baseball_yesno.bmp"); 
baseballrestart();
break; 

}
  
  else if(strike == 0 && ball == 0)
  {
	 ledalloff();
  }
  
  else if (strike == 0 && ball == 1)
  {
	  ledalloff();
	  led0s1b();
  }
  else if (strike == 0 && ball == 2)
  {
	  ledalloff();
	  led0s2b();
  }
  else if (strike == 0 && ball == 3)
  {
	  ledalloff();
	  led0s3b();
  }
  else if (strike == 1 && ball == 0)
  {
	  ledalloff();
	  led1s0b();
  }
  else if (strike == 1 && ball == 1)
  {
	  ledalloff();
	  led1s1b();
  }
  else if (strike == 1 && ball == 2)
  {
	  ledalloff();
	  led1s2b();
  }
       else if (strike == 2 && ball == 0)
  {
	  ledalloff();
	  led2s0b();
  }
     else if (strike == 2 && ball == 1)
  {
	  ledalloff();
	  led2s1b();
  }


else if(strike == 3) // 만약 스트라이크 개수가 3개이면 승리 
{ 
	led3s0b();
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
			buzzerPlaySong(musicScale[7]);
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
bitmainfunc("baseball_yesno.bmp"); 
baseballrestart();

break; 

} 
	count++; 

bitmainfunc("baseball_yesno.bmp"); 

}
  	return 0;

}


int soccerballrestart(void)
{
	
	    while(1)
    {
		msgrcv(msgID, &recvMsg, sizeof(TOUCH_MSG_T)- sizeof(long int), 0, 0);
         
        switch (recvMsg.keyInput)
        {
            case 999: // X 341 682 Y 200 400/
                    if(recvMsg.pressed==1)
                { 
                     if(0 < recvMsg.x && recvMsg.x  < 512 && 300<recvMsg.y && recvMsg.y<500)
                    {
						soccergame();
                    }
                      if(512 <recvMsg.x && recvMsg.x < 1024 && 300 <recvMsg.y && recvMsg.y < 500)
                    {
						backtothemain();
                    }
                }
break;
    }
	}
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
	
	TOUCH_MSG_T recvMsg;
	int returnValue = 0;
	
	int msgID = msgget (1122, IPC_CREAT|0666);

	if (msgID == -1){
	printf ("Cannot get msgQueueID, Return!\r\n");
	return -1;
	}

	
	while(1)
	{	
		accel = getAcc(); // 가속도 값 1초에 한 번씩 받아오기
		//printf("accel: %d", accel);
		msgrcv(msgID, &recvMsg, sizeof(TOUCH_MSG_T)- sizeof(long int), 0, 0);
		//printf("%d/n", returnValue);

		switch (recvMsg.keyInput)
        {
            case 999: 
            if(recvMsg.pressed==1)
            { 
                if((0 < recvMsg.x) && (recvMsg.x  < 1024) && (0<recvMsg.y) && (recvMsg.y<600))  
					{
						if(accel <= -10000)
						{   
							bitmainfunc("newball_left.bmp");
           					printf(" accel : %d", accel);
							ball_num = 1;
							sleep(1);
						}
						else if(accel >= -10000 && accel <= 10000)
						{
                        printf(" accel : %d", accel);
							ball_num = 2;						
                        bitmainfunc("newball_center.bmp");
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
					break;

		}
	
		


        printf("스위치 빠져나온 번호 %d \n", ball_num);

		if( 1<= ball_num && 3>= ball_num ) break;
		
		//return ball_num; // 공 번호 반환해 주기


	}
    printf("final ball num :%d \n", ball_num);
	return ball_num;
	
}


int soccergame(void)
{   
	fndDisp(0, 0);
	bitmainfunc("soccer_start.bmp");
	text("GAME START", "	");
	int score = 0; // 점수를 저장하는 변수
	int i;
		for(i=0 ; i<3 ; i++){
	 /*----------------------------- 사용자의 최종 위치 받아오기 ---------------------- */
		int player_num; // 리턴 받을 사용자의 장소 번호

		player_num = select_ball_func(); // 사용자의 장소 최종 위치 불러오기
		printf("%d\n", player_num);
		sleep(1);
	 /*--------------------------- 랜덤한 위치 받아오기 -------------------- */
		int rand_num; // 랜덤하게 받아올 숫자
		srand(time(NULL)) ;
	
		rand_num =rand() % 3 + 1; // 1, 2, 3 중 랜덤한 값을 무작위로 받아와서 저장하기

		printf("computer_num : %d\n", rand_num);
		printf("playernim : %d\n", player_num);
	 /*---------------------------------점수 조정하기-----------------------------------*/
			

		if (player_num == rand_num) // 게임 결과 비교 (승)
		{	
			bitmainfunc("Goal.bmp");
			fnd(MODE_STATIC_DIS,score+1);
			score = score + 1;
			printf ("score : %d", score);
			sleep(1);
		}

		else if (player_num != rand_num) // 패
		{	
			
				bitmainfunc("Fale.bmp");
				fnd(MODE_STATIC_DIS,score-1);
				if (score == 0 ) score = 0;
				else score = score - 1;
				printf ("score : %d", score);
				sleep(1);
		}


	}	

	bitmainfunc ("soccer_yesno.bmp");
	soccerballrestart();
	


	

	text("Finish","	");
	return 0;
}

