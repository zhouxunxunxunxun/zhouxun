
#include<stdio.h>
#include<stdlib.h>
#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define BUFFERSIZE 256

typedef int Status; //函数返回状态
typedef int opndElem;  //操作数元素类型
typedef struct{//操作数栈结构定义
    opndElem *base;
    opndElem *top;
    int stacksize;
}OpndStack;

typedef char optrElem;//操作符元素类型
typedef struct{//操作符栈结构定义
    optrElem *base;
    optrElem *top;
    int stacksize;
}OptrStack;

//==========操作数栈=============//
Status InitStack_OPND(OpndStack *S);
    //构造一个空栈S
Status GetTop_OPND(OpndStack S,opndElem *e);
    //若栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE
Status Push_OPND(OpndStack *S,opndElem e);
    //插入元素e为新的栈顶元素
Status Pop_OPND(OpndStack *S,opndElem *e);
    //若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR

//==========操作符栈=============//
Status InitStack_OPTR(OptrStack *S);
    //构造一个空栈S
optrElem GetTop_OPTR(OptrStack S);
    //若栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE
Status Push_OPTR(OptrStack *S,optrElem e);
    //插入元素e为新的栈顶元素
Status Pop_OPTR(OptrStack *S,optrElem *e);
    //若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR

//============运算操作================//
void Standard(char *expression);
    //将表达式标准化
opndElem EvalueateExpression(const char *expression);
    //算数表达式求值
Status Isoperator(char c);
    //判断c是否是一个操作符
char Precede(char op1,char op2);
    //判断op1和op2优先级的高低，返回'>','<','='
opndElem operate(opndElem a,optrElem theta,opndElem b);
    //对操作数a，b进行theta运算
const char *getOpnd(const char *c,opndElem *op);
    //获得以*c开始的操作数，返回后c为操作符

//==========操作数栈===========//
Status InitStack_OPND(OpndStack *S){
    //构造一个空操作数栈S
    S->base=(opndElem *)malloc(STACK_INIT_SIZE*sizeof(opndElem));
    if(!S->base)//分配失败
    {
        printf("分配内存失败.\n");
        exit(0);
    }
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

Status GetTop_OPND(OpndStack S,opndElem *e){
    //若操作数栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE
    if(S.top==S.base){
        printf("栈为空.\n");
        return FALSE;
    }else{
        *e=*(S.top-1);
        return OK;
    }
}

Status Push_OPND(OpndStack *S,opndElem e){
    //插入元素e为新的栈顶元素
    if(S->top-S->base>=S->stacksize){//栈已满，追加存储空间
        S->base=(opndElem *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(opndElem));
        if(!S->base)
        {
            printf("重新申请空间失败.\n");
            exit(0);
        }
        S->top=S->base+S->stacksize;//更改栈顶指针
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    return OK;
}

Status Pop_OPND(OpndStack *S,opndElem *e){
    //若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR
    if(S->top==S->base){//栈为空
        printf("栈为空.\n");
        return ERROR;
    }
    *e=*(--S->top);
    return OK;
}

//==========操作符栈===========//
Status InitStack_OPTR(OptrStack *S){
    //构造一个空操作数栈S
    S->base=(optrElem *)malloc(STACK_INIT_SIZE*sizeof(optrElem));
    if(!S->base)//分配失败
    {
        printf("分配内存失败.\n");
        exit(0);
    }
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

optrElem GetTop_OPTR(OptrStack S){
    //若操作数栈不为空，则返回S的栈顶元素，并返回OK；否则返回FALSE
    optrElem e;
    if(S.top==S.base){
        printf("栈为空.\n");
    }else{
        e=*(S.top-1);
    }
    return e;
}

Status Push_OPTR(OptrStack *S,optrElem e){
    //插入元素e为新的栈顶元素
    if(S->top-S->base>=S->stacksize){//栈已满，追加存储空间
        S->base=(optrElem *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(optrElem));
        if(!S->base)
        {
            printf("重新申请空间失败.\n");
            exit(0);
        }
        S->top=S->base+S->stacksize;//更改栈顶指针
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    return OK;
}

Status Pop_OPTR(OptrStack *S,optrElem *e){
    //若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR
    if(S->top==S->base){//栈为空
        printf("栈为空.\n");
        return ERROR;
    }
    *e=*(--S->top);
    return OK;
}

//运算
int isop(char c){
    int x;
    switch(c){
        case '#':
        case '(':
        case '+':
        case '-':
        case '*':
        case '/':
        case ')':
            return 1;break;
        default:
            return 0;break;
    }
}

char compare(char op1,char op2){
    switch(op1){
        case '+':
            switch(op2){
                case '*':
                case '/':
                case '(':
                    return '<';break;
                default:
                    return '>';break;
            }
            break;
        case '-':
            switch(op2){
                case '*':
                case '/':
                case '(':
                    return '<';break;
                default:
                    return '>';break;
            }
            break;
        case '*':
            switch(op2){
                case '(':
                    return '<';break;
                default:
                    return '>';break;
            }
            break;
        case '/':
             switch(op2){
                case '(':
                    return '<';break;
                default:
                    return '>';break;
            }
            break;
        case '('://扔到栈内，优先级降到最低
            switch(op2){
                case ')':
                    return '=';break;
                default:
                    return '<';break;
            }
        case ')':
            switch(op2){
                default:
                    return '>';break;
            }
        case '#':
            switch(op2){
                case '#':
                    return '=';break;
                default:
                    return '<';break;
            }
        default:
            return '<';break;
    }
}

const char *getOpnd(const char *c,int *op){
    //获得以*c开始的操作数，返回后c为操作符
    int sum=0,tmp;
    while(0==isop(*c)){//当c不是操作符
        tmp=*c-'0';
        sum=sum*10+tmp;
        //printf("tmp=%d\n",tmp);
        c++;
    }
    *op=sum;
    //printf("getOpnd:%d\n",*op);
    return c;
}
int qiuzhi(char *expression){
    const char *c = expression;
    int data,a,b,val;
    char ch,op;
    OpndStack s1;
    OptrStack s2;
    InitStack_OPTR(&s2);//初始化操作符栈
    InitStack_OPND(&s1);
    //printf("123");
    Push_OPTR(&s2,'#');
    //printf("please input an expression:");
    while(*c!='#' || GetTop_OPTR(s2) != '#'){
        if(*c == '\0')
            break;
        if(!isop(*c)){
            c = getOpnd(c,&data);
            //printf("%d",data);
            Push_OPND(&s1,data);
            //printf("hhh");
        }
        else{
            switch(compare(GetTop_OPTR(s2),*c)){
                case '<':Push_OPTR(&s2,*c);
                        c++;break;
                case '=':Pop_OPTR(&s2,&ch);
                        c++;break;
                case '>':Pop_OPTR(&s2,&op);
                        Pop_OPND(&s1,&a);
                        Pop_OPND(&s1,&b);
                        val = operate(b,op,a);
                        Push_OPND(&s1,val);
                        //printf("hhh");
                        break;
                default:
                    break;
            }
        }
    }
    //printf("hhh");

    GetTop_OPND(s1,&val);
    return val;
}
int operate(int a,char theta,int b){
    //对操作数a，b进行theta运算，并返回运算结果
    //theta只能是四则运算符号
    int rs_i;
    switch(theta){
        case '+':
            rs_i=a+b;
            break;
        case '-':
            rs_i=a-b;
            break;
        case '*':
            rs_i=a*b;
            break;
        case '/':
            if(b==0){
                printf("errror:除数为0.");
                exit(0);
            }
            rs_i=a/b;
            break;
        default:
            printf("Is not a operator.\n");
            break;
    }
    printf("%d %c %d = %d\n",a,theta,b,rs_i);
    return rs_i;

}
void Standard(char *expression){
    //将字符串表达式标准化为算术表达式
    char *p=expression,*q;
    while(*p!='\0'){//遍历字符串
        if(*p==' '){//如果是空格，删除
            q=p;
            do{
                *q=*(q+1);
                q++;
            }while(*q!='\0');
        }
        p++;
    }
    *p++='#';
    *p='\0';
}

int main(){
    int result=0;
    char *expression=(char*)malloc(sizeof(char)*BUFFERSIZE);

    if(expression==NULL){
        printf("Sorry,memory initialize error.\n");
        exit(0);
    }
    printf("Please input an expression:\n");
    gets(expression);
    Standard(expression);
    result=qiuzhi(expression);
    printf("The result of the expression:%d\n",result);
    return 0;

}
