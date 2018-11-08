#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <windows.h>
#define CHAR_TYPE 1
#define STRING_TYPE 2
#define INT_TYPE 3
#define DOUBLE_TYPE 4
#define FLOAT_TYPE 5

int xpos,ypos,
    get_y,get_x1,
    get_x2;
struct FORM{
    char CHAR[100];
    char STRING[1000];
    int INT;
    float FLOAT, DOUBLE;
}Form;
void move(int x,int y){
	COORD coord;coord.X=x;coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void draw_grub(int x1, int y1,int x2,int y2,char* title){
    int _y,_x;
    x1+=1; y1+=1;
    xpos=x1+1; ypos=y1+1;
    get_y=y2-1; get_x1=x1;
    get_x2=x2;
    move(x1-1,y1);
    printf("\xDA");
    for(_x=x1;_x<x2;_x++){
        move(_x,y1);
        printf("\xC4");
    }
    move(x1+2,y1);
    printf("\xB4%s\xC3",title);
    move(x2,y1);
    printf("\xBF");
    for(_y=y1+1;_y<y2;_y++){
        move(x1-1,_y);
        printf("\xB3");
    }
    move(x1-1,y2);
    printf("\xC0");
    for(_y=y1+1;_y<y2;_y++){
        move(x2,_y);
        printf("\xB3");
    }
    move(x2,y2);
    printf("\xD9");
    for(_x=x1;_x<x2;_x++){
        move(_x,y2);
        printf("\xC4");
    }
}
void draw_box(int x1, int y1,int x2,int y2){
    int _y,_x;
    x1+=1; y1+=1;
    xpos=x1+1; ypos=y1+1;
    get_y=y2-1; get_x1=x1;
    get_x2=x2;
    move(x1-1,y1);
    printf("\xDA");
    for(_x=x1;_x<x2;_x++){
        move(_x,y1);
        printf("\xC4");
    }
    move(x2,y1);
    printf("\xBF");
    for(_y=y1+1;_y<y2;_y++){
        move(x1-1,_y);
        printf("\xB3");
    }
    move(x1-1,y2);
    printf("\xC0");
    for(_y=y1+1;_y<y2;_y++){
        move(x2,_y);
        printf("\xB3");
    }
    move(x2,y2);
    printf("\xD9");
    for(_x=x1;_x<x2;_x++){
        move(_x,y2);
        printf("\xC4");
    }
}

void write(const char* txt,...){
    char data[2];
	int max=strlen(txt);
    va_list arr;

    va_start(arr,txt);
    if(ypos>get_y)
        ypos=get_y;
    move(xpos,ypos);
    if(max>(get_x2-get_x1))
    	max=(get_x2-get_x1)-1;
    for(int x=0;x<max;x++){
        if(txt[x]=='%'){
            data[0]=txt[x];
            data[1]=txt[x+1];
            x++;
        }

        if(data[1]=='d'){
            printf("%d",va_arg(arr,int));
            data[0]='\0';
            data[1]='\0';
        }else if(data[1]=='i'){
            printf("%i",va_arg(arr,int));
            data[0]='\0';
            data[1]='\0';
        }else if(data[1]=='c'){
            printf("%s",va_arg(arr,char*));
            data[0]='\0';
            data[1]='\0';
        }else if(data[1]=='s'){
            printf("%s",va_arg(arr,char*));
            data[0]='\0';
            data[1]='\0';
        }else if(data[1]=='f'){
            printf("%f",va_arg(arr,float));
            data[0]='\0';
            data[1]='\0';
        }else printf("%c",txt[x]);
    }
    ypos++;
    va_end(arr);
}
void delay(int _time){
    for(int count=0;count<(_time*1000000);count++);
}
void draw_form(char* _p,int x, int y, unsigned char type){
    char _ask[100];
    int _ask_i;
    float _ask_f;

    draw_box(x,y,x+(3+strlen(_p)),3+y);
    move(x+2,2+y);
    //printf("\x1B[34m\x1B[1m%s\x1B[0m",_p);
    printf("%s",_p);
    draw_box(x+3+strlen(_p),y,x+((strlen(_p)*4)+3),3+y);
    move(x+strlen(_p)+5,2+y);
    if(type==CHAR_TYPE){
        gets(_ask);
        strcpy(Form.CHAR,_ask);
    }else if(type==STRING_TYPE){
        gets(_ask);
        strcpy(Form.STRING,_ask);
    }else if(type==INT_TYPE){
        scanf("%i",&_ask_i);
        Form.INT=_ask_i;
    }else if(type==DOUBLE_TYPE){
        scanf("%f",&_ask_f);
        Form.DOUBLE=_ask_f;
    }else if(type==FLOAT_TYPE){
        scanf("%f",&_ask_f);
        Form.FLOAT=_ask_f;
    }
}