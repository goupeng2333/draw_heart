#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

const float U = 0.1;
const float V = 0.053;

const char love_word[4] = {'l','o','v','e'};
int colors[5] = {10,11,12,13,14};
const int z[] = {32,32,0xba,0xc6,0xba,0xc6,44,0xce,0xd2,0xcf,0xb2,0xbb,0xb6,0xc4,0xe3,33,32,32};// GBK编码

void SetColor(unsigned short ForeColor,unsigned short BackGroundColor){
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,(ForeColor%16 )| (BackGroundColor %16*16));
}

void swap(int *a, int *b){
    if( a!= b){
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

void shuffle(int *array, int array_size){
    for(;array_size >1;array_size--){
        swap(array + (rand() % array_size), array + array_size -1);
    }
}

int if_in_heart(float x, float y){

    return ((( x*x + y*y -1) * (x*x + y*y -1) * (x*x + y*y -1) - (x*x * y*y *y)) <= 0);
}

void print_love(){
    static int s;
    s &= 3;
    SetColor(colors[s],0);
    putchar(love_word[s]);
    s++;
}


void draw_heart(){
    int i;
    float x,y;
    // y是纵坐标
    // x是横坐标
    for(y=1.3;y>=-1.1;y-=U){
        // 逐行打印
        for(x=-2;x<1.4;x+=V){
            // 从左到右打印
            if(if_in_heart(x,y)){
                // 在心形范围内
                if(y>=1.3-10*U || y<=1.3-11*U){
                    // 当高度没有到达或者超过了中文区域，全部显示英文
                    print_love();
                }
                else{
                    // 打印中文所在行
                    for(i=0;i<44;i++){
                        if(i<=12||i>=33){
                            // 在中文的左侧或者右侧
                            print_love();
                        }
                        else{
                            // 打印中文
                            SetColor(colors[4],0);
                            printf("%c",z[i-15]);
                        }
                    }
                    break;
                }
            }
            else{
                // 不在心形范围内，打印空格符号
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(){
    srand(time(NULL));
    draw_heart();
    printf("%c%c%c%c%c%c%c%c%c%c%c%c!",0xb0,0xb4,0xc8,0xce,0xd2,0xe2,0xbc,0xfc,0xbc,0xcc,0xd0,0xf8);
    getchar();
    while(1){
        system("cls");
        shuffle(colors,5);
        draw_heart();
        Sleep(1000);
        system("cls");
    }
}
