#ifndef _BUTTON_H_

#define _BUTTON_H_
#define MESSAGE_ID 1123

typedef struct{
    long int messageNum;
    int keyInput;
    int pressed;
} BUTTON_MSG_T;

int buttonInit(void);
int buttonExit(void);

#endif
