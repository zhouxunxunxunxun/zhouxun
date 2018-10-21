#include<stdio.h>
#define maxsize 100
#define N 8

int board[8][8];//定义棋盘
int arr1[8] = {1,-1,-2,2,2,1,-1,-2};
int arr2[8] = {2,-2,1,1,-1,-2,2,-1};

struct Stack{
    int i;
    int j;
    int director;//存储方向
}stack[maxsize];
int top = -1;

void initLocation(int x,int y);//起始坐标函数
int tryPath(int i,int j);//探寻路径函数
void display();//输出路径函数

void initLocation(int x,int y){
    int x1,y1;//定义棋盘的横纵坐标变量
    top++;//指向第一个栈首
    stack[top].i = x;//横坐标进栈
    stack[top].j = y;//纵坐标进栈
    board[x][y] = top+1;
    x1 = stack[top].i;
    y1 = stack[top].j;
    if(tryPath(x1,y1))
        display();
    else
        printf("无解！！");
}

int tryPath(int i,int j){
    //各点的八个方向按权值递增排列
    int find,director,number,min;//临时变量
    int i1,j1,h,k,s;
    int a[8],b1[8],b2[8],d[8];
    while(top > -1){//栈没空
        for(h = 0;h < 8;h++){//用数组a[8]记录当前位置的下一个位置的可行路径的条数
            number = 0;
            i = stack[top].i+arr1[h];
            j = stack[top].j+arr2[h];
            b1[h] = i;
            b2[h] = j;
            if(board[i][j]==0&&i>=0&&i<8&&j>=0&&j<8){
                    for(k=0;k<8;k++){
                        i1 = b1[h] + arr1[k];
                        j1 = b2[h] + arr2[k];
                        if(board[i1][j1]==0&&i1>=0&&i1<8&&j1>=0&&j1<8)
                            number++;//记录条数
                    }
                    a[h] = number;
            }

        }
        for(h=0;h<8;h++){//根据可行路径条数小到大按下表排序放入数组d[8]中
            min = 9;
            for(k = 0;k < 8;k++)
                if(min > a[k]){
                    min = a[k];
                    d[h] = k;
                    s = k;
                }
            a[s] = 9;
        }
            //马走过的路径，合法，则进栈
            director = stack[top].director;
            if(top >=63)
                return 1;
            find = 0;//表示没有找到下一个位置
            for(h = director+1;h<8;h++){//向八个方向探寻
                i = stack[top].i+arr1[d[h]];
                j = stack[top].j+arr2[d[h]];
                if(board[i][j]==0&&i>=0&&i<8&&j>=0&&j<8){
                    find = 1;//找到了下一个位置
                    break;
                }
            }
            if(find == 1){//找到位置，进栈
                stack[top].director=director;
                top++;
                stack[top].i=i;
                stack[top].j=j;
                stack[top].director=-1;
                board[i][j] = top+1;
            }else{//没有找到位置，清楚棋盘内的位置
                board[stack[top].i][stack[top].j] = 0;
                top--;
            }
        }
        return 0;
}
void display(){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("\t%d",board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    int i,j;
    int x,y;
     for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            board[i][j] = 0;
        }
     }
     for(;;){
       printf("please input point(1<=x<=8 and 1<=y<=8)\n");
       printf("x = ");
       scanf("%d",&x);
       printf("y = ");
       scanf("%d",&y);
       if(x>=1&&x<=8&&y>=1&&y<=8)
            break;
       printf("you are wrong");
     }
     printf("begin with %d board:\n\n",8*(x-1)+y);
     initLocation(x-1,y-1);
     return 0;
}
