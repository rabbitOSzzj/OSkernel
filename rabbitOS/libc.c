//用C语言扩展内核
#include <stdint.h>
#include "./stringio.h"

const int BUFLEN = 16;
extern void clearScreen(void);
extern void printInPos(char* msg, uint16_t len, uint8_t row, uint8_t col);//在光标处打印字符串
extern void putchar(char c);//输出一个字符
extern char getchar(void);//输入一个字符
extern void powerOff(void);//关机
extern void systime(void);//获取系统时间
extern void drawPic(void);

//系统的启动页面
void startUp(){
    clearScreen();
    char* title = "carrotOS v1.0";
    char* subTitle = "made by zzj";
    char * copyright = "Copyright (c) 2022 zzj";
    char * hello = "Welcome to use carrotOS1.0 for your computer";
    char * hint = "System is already.Press Enter to continue...";
    printInPos(title,strlen(title),5,23);
    printInPos(subTitle,strlen(subTitle),6,29);
    printInPos(copyright,strlen(copyright),8,35);
    printInPos(hello,strlen(hello),15,11);
    printInPos(hint,strlen(hint),15,11);
}

//打印shell的提示符
void printPrompt(){
    char * prompt = "carrotOS #";
    print(prompt);
}

//显示提示信息
void showHelp(){
    char * help =
    "Shell for carrotOS, Version 1.0 - on x86 PC\r\n"
    "This is a shell which is used for carrotOS.These commands are defined as follows.Use `help` to see the list \r\n"
    "\r\n"
    "clear - clear the terminal \r\n"
    "time - get the current time \r\n"
    "drawpic - draw a animate pic \r\n"
    "poweroff - force shutdown the computer \r\n";
    print(help);
}

void shell(){
    clearScreen();
    showHelp();
    char cmdstr[17] = {0};
    char cmd_fstword[17] = {0};
    enum command{
        clear,
        time,
        drawpic,
        poweroff,
        help,
    };
    char* commands[]={"clear","time","drawpic","poweroff","help"};
    while (1){
        printPrompt();
        readToBuffer(cmdstr,BUFLEN);
        getFirstWord(cmdstr,cmd_fstword);
        if (strcmp(cmd_fstword,commands[clear])==0){
            clearScreen();
        }else if (strcmp(cmd_fstword,commands[time])==0){
            systime();
        }else if (strcmp(cmd_fstword,commands[drawpic])==0){
            drawPic();
        }else if (strcmp(cmd_fstword,commands[help])==0){
            showHelp();
        }else if (strcmp(cmd_fstword,commands[poweroff])==0){
            powerOff();
        }else{
            if (cmd_fstword[0]=='\0'){
                continue;
            }else{
                print(cmd_fstword);
                print(":Unknown command\r\n");
            }
        }
    }
}