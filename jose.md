```c
#include<stdio.h>
#include<stdlib.h>
#define max 100

typedef struct Node{
    int id;
    int password;
    struct Node *next;
}node;

node *create();//创建循环链表
void josep(node*h,int pass);//进行约瑟夫环的运算
int isEmpty(node *h);//判空
void print(node *h);//打印


node *create(int n){
    node *h = NULL,*p,*t;
    int i,pass;
    for(i = 0;i < n;i++){
        p = (node*)malloc(sizeof(node));
        printf("请输入第%d个人的密码:",i+1);
        scanf("%d",&pass);
        p->id = i+1;
        p->password = pass;
        p->next = NULL;
        if(h == NULL){
            h = p;
        }else{
            t->next = p;
        }
        t = p;
    }
    t->next = h;
    printf("完成单向循环链表的创建！");
    return h;
}

void josep(node*h,int pass){
    int count = 0;
    int flag = 1;
    node *p1,*p2,*r;
    p1 =p2 = h;
    while(p1->next!=h)//初始化为尾结点
        p1 = p1->next;
    while(flag){
        for(count = 1;count < pass;count++){//通过前驱结点，删除结点
            p1 = p2;
            p2 =p2->next;
        }
        if(p1 == p2){//只剩一个人的时候
            flag = 0;
        }
        r = p2;
        p1->next = p2->next;
        p2 = p2->next;
        pass = r->password;
        printf("第%d个人（密码：%d）出列\n",r->id,r->password);
        free(r);
    }
    h = NULL;
    getchar();//吸收多余的换行符
}
int isEmpty(node *h){
    if(!h){
        printf("the list is empty!");
        return 1;
    }
    return 0;
}
void print(node *h){
    node *p = h;
    if(!isEmpty(h)){
        printf("--ID-- --PASSWORD--\n");
        while(p->next!=h){
            printf("%3d %7d\n",p->id,p->password);
            p = p->next;
        }
    }
}
int main(){
    int n = 0;
    int m = 0;//寻找第m个结点
    node *h = NULL;
    do{
        if(n > max){
            printf("人数过多，请重新输入！");
        }
        printf("请输入人数（最多%d个）",max);
        scanf("%d",&n);
    }while(n > max);
    printf("请输入初始密码:");
    scanf("%d",&m);
    h = create(n);
    printf("\n------------打印循环链表--------\n");
    print(h);
    printf("\n------------打印出列情况--------\n");
    josep(h,m);
    return 0;
}

```
