#include<stdio.h>
#include<stdlib.h>
#define maxsize 500

typedef struct//存储稀疏矩阵的非零元数据
{
    int x,y;
    int value;
}triple;
typedef struct
{
    triple data[maxsize + 1];//非零元的数组
    int rows,cols,nums;//稀疏矩阵的行数，列数及非零元个数
}maxtri;

//初始化
maxtri *init()
{
    int i = 0;
    maxtri *q;
    q = (maxtri*)malloc(sizeof(maxtri));
    q->rows = 0;
    q->cols = 0;
    q->nums = 0;
    for(i = 0;i<maxsize;i++){
        q->data[i].x = 0;
        q->data[i].y = 0;
        q->data[i].value = 0;
    }
    return q;
}
//创建和输入稀疏矩阵
void createmaxtri(maxtri *t){
    int k = 1;
    printf("请输入稀疏矩阵的行数、列数及非零元的个数:");
    scanf("%d%d%d",&t->rows,&t->cols,&t->nums);
    //printf("123");
    if(t->nums > maxsize && t->rows > 22){
        printf("非零元个数超出定义范围！出错！");
        exit(0);
    }
    for(k=1;k<=t->nums;k++){
        printf("请输入第%d个非零元素的行数、列数及其值：",k);
        scanf("%d%d%d",&t->data[k].x,&t->data[k].y,&t->data[k].value);
    }
}

//稀疏矩阵相加
void add(maxtri *m,maxtri *n,maxtri *q)
{
    int i,j,k = 1;
    //printf("123");
    if(m->rows != n->rows || n->cols!=m->cols ){
        //printf("123");
        printf("您的输入不符合矩阵相加的条件！\n");
        exit(1);
    }else{
        q->rows = m->rows;
        q->cols = n->cols;
        //printf("123");
        for(i = 1,j = 1;i <= m->rows&&j<=n->rows;){
            if(m->data[i].x == n->data[j].x){
                if(m->data[i].y == n->data[j].y){
                    q->data[k].x = m->data[i].x;
                    q->data[k].y = m->data[i].y;
                    q->data[k].value = m->data[i].value + n->data[j].value;
                    k++;i++;j++;
                }else if(m->data[i].y < n->data[j].y){
                    q->data[k].x = m->data[i].x;
                    q->data[k].y = m->data[i].y;
                    q->data[k].value = m->data[i].value;
                     k++;i++;
                }else if(m->data[i].y > n->data[j].y){
                    q->data[k].x = n->data[j].x;
                    q->data[k].y = n->data[j].y;
                    q->data[k].value = n->data[j].value;
                    k++;j++;
                }
            }else if(m->data[i].x < n->data[j].x){
                q->data[k].x = m->data[i].x;
                q->data[k].y = m->data[i].y;
                q->data[k].value = m->data[i].value;
                k++;i++;
            }else if(m->data[i].x > n->data[j].x){
                  q->data[k].x = n->data[j].x;
                  q->data[k].y = n->data[j].y;
                  q->data[k].value = n->data[j].value;
                  k++;j++;
            }
        }
        if(i!=m->nums+1){
            for(;i<=m->nums;i++){
                q->data[k].x = m->data[i].x;
                q->data[k].y = m->data[i].y;
                q->data[k].value = m->data[i].value;
                k++;
            }
        }
        if(j!=n->nums+1){
            for(;j<=n->nums;j++){
                q->data[k].x = n->data[j].x;
                q->data[k].y = n->data[j].y;
                q->data[k].value = n->data[j].value;
                k++;
            }
        }
    }
}
void sub(maxtri *m,maxtri *n,maxtri *q)
{
    int i,j,k = 1;
    if(m->rows != n->rows || n->cols!=m->cols ){
        printf("您的输入不符合矩阵相加的条件！\n");
        exit(1);
    }else{
        q->rows = m->rows;
        q->cols = n->cols;
        for(i = 1;i<=n->nums;i++){
            n->data[i].value *= -1;
        }
        add(m,n,q);
        for(i = 1;i<=n->nums;i++){
            n->data[i].value *= -1;
        }
    }
}

//输出矩阵
void print(maxtri *q)
{
    int k = 1,i,j;
    printf("运算结果为:\n");
    if(q->nums = 0)
        printf("0");
    else{
        for(i = 0;i<q->rows;i++){
            for(j=0;j<q->cols;j++){
                if(q->data[k].x == i&&q->data[k].y == j){
                    printf("%d ",q->data[k++].value);
                }else{
                    printf("0 ");
                }
            }
            printf("\n");
        }
    }
}

int main()
{
    maxtri *m,*n,*q,*p;
    m = init();
    n = init();
    q = init();
    p = init();
    //createmaxtri(m);
    int i;
    printf("请输入第一个矩阵M:\n");
    createmaxtri(m);
    printf("请输入第二个矩阵N:\n");
    createmaxtri(n);
    add(m,n,q);
    print(q);
    sub(m,n,p);
    print(p);
    return 0;
}
