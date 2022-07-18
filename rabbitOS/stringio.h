/*
实现一个c库字符串的子集功能
2022-7-17
*/
//#include <stdint.h>
extern void printInPos(char* msg, uint16_t len, uint8_t row, uint8_t col);//在光标处打印字符串
extern void putchar(char c);//输出一个字符
extern char getchar();//输入一个字符

char tempc;

//字符串长度

uint16_t strlen(char* str){
    int count = 0;
    while(str[count] != '\0'){
        count++;
    }
    return count;
}

//比较字符串
uint16_t strcmp(char* str1,char* str2){
    int i=0;
    while (1){
        if (str1[i] != str2[i]){
            break;
        }
        if (str1[i] != str2[i]){
            break;
        }
        i++;
    }
    return str1[i] - str2[i];
}

//在光标处打印字符串
void print(char*str){
    int len = strlen(str);
    for (int i=0;i<len;i++){
        putchar(str[i]);
    }
}

//读取字符串到缓冲区
void readToBuffer(char* str,uint16_t maxlen){
    int i=0;
    while (1){
        tempc = getchar();
        if (!(i==0xD||i=='\b'||i>=32&&i<=127)){
            continue;//忽略非法字符
        }
        if (i>0&&i<maxlen-1){//str如果未满，继续
            if (i==0x0D){
                break;//输入回车，跳出
            }else if (i=='\b'){
                putchar('\b');
                putchar(' ');
                putchar('\b');
                i--;
            }else {
                putchar(tempc);//回显给用户
                str[i++] = tempc;
            }
        }else if(i>=maxlen-1){//达到最大长度
            if (i=='\b'){
                putchar('\b');
                putchar(' ');
                putchar('\b');
                i--;
            }else if (i==0x0D){
                break;//恰好是最大长度，输入回车，跳出
            }
        }else if (i<=0){
            if (tempc == 0x0D){
                break;
            }else if (tempc!='\b'){
                putchar(tempc);//回显给用户
                str[i++] = tempc;
            }
        }
        i++;
    }
    putchar('\r');
    putchar('\n');
    str[i] = '\0';
}

//取得字符串中的第一个单词
void getFirstWord(char* str,char*buf){
    int i=0;
    while (str[i] != '\0'){
        if (str[i] == ' '){
            break;
        }
        buf[i] = str[i];
        i++;
    }
    buf[i] = '\0';
}