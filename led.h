#ifndef _LED_H_
#define _LED_H_

int ledlibinit(void);
int ledonoff(int lednum, int onoff);
int ledallof(void);
int led0s1b(void);
int led0s2b(void);
int led0s3b(void);
int led1s0b(void);
int led1s1b(void);
int led1s2b(void);
int led2s0b(void);
int led2s1b(void);
int led3s0b(void);
int ledlibexit(void);

#define LED_DRIVER_NAME "/dev/periled"

#endif _LED_H_
