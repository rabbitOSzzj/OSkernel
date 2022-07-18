BITS 16
[global printInPos] ;在鼠标光标处打印一个字符串
[global putchar] ;输出一个字符到屏幕
[global getchar] ;获得键盘的输入
[global clearScreen] ;清屏
[global powerOff] ;关机
[global systime] ;获得时间
[global drawpic] ;画图片

drawpic: ;画图片
    pusha
    popa
    retf

systime: ;获得时间
    pusha
    mov al,4 ;小时
    out 70h,al
    in al,71h
    mov ah,al
    mov cl,4 ;minutes
    shr ah,cl
    and al,00001111b
    add ah,30h
    add al,30h
    mov dx,ax
    mov al,dh
    mov bh,0
    mov ah,0Eh
    int 10h
    mov al,dl
    mov bh,0
    mov ah,0Eh
    int 10h
    popa
    retf

powerOff: ;关机
    mov ax,5307h
    mov bx,0001h
    mov cx,0003h
    int	15h

getchar: ;使用16号中断，获取键盘输入
    mov	ah,0 ;功能号
    int 16h ;调用16号中断
    mov	ah,0 ;读取键盘输入，al放的是键盘输入的字符，同时将ah变为0，为返回值做准备
    retf

putchar: ;在鼠标光标处打印一个字符
    pusha
    mov bp,sp
    add bp,16+4 ;参数地址
    mov al,[bp] ;al是要打印的字符
    mov bh,0 ;bh是页码
    mov ah,0Eh ;0Eh是中断
    int 10h ;调用10号中断
    popa
    retf

printInPos: ;在指定位置显示字符串
    pusha
    mov si,sp ;si是字符串地址
    add si,16+4 ;首个参数地址
    mov ax,cs
    mov ds,ax
    mov bp,[si] ;bp指向字符串的偏移地址
    mov ax,ds ;es:bp指向的字符串地址
    mov es,ax ;使es=ds
    mov cx,[si+4] ;cx是字符串的长度
    mov ax,1301h ;ah=13(功能号),al=01h表示字符串显示完毕后，光标应置于字符串尾部
    mov bx,0007h ;0号页，黑底白字
    mov dh,[si+8] ;行号为0
    mov dl,[si+12] ;列号为0
    int 10h ;调用10号中断，显示一行字符
    popa
    retf

clearScreen: ;清屏
    push ax
    mov ax,0003h
    int 10h ;调用10号中断，清屏
    pop ax
    retf