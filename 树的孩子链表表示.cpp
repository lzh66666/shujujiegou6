#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 20
#define OK 1
typedef char TElemType;
typedef int Status;

//孩子表示法
typedef struct CTNode{
    int child;//链表中每个结点存储的不是数据本身，而是数据在数组中存储的位置下标
    struct CTNode * next;
}ChildPtr;

typedef struct {
    TElemType data;//结点的数据类型
    ChildPtr* firstchild;//孩子链表的头指针
}CTBox;

typedef struct{
    CTBox nodes[MAX_SIZE];//存储结点的数组
    int n,r;//结点数量和树根的位置
}CTree;

Status InitTree(CTree &T){
	ChildPtr *p,*q;
    printf("输入节点数量：\n");
    scanf("%d",&(T.n));
    for(int i=0;i<T.n;i++){
        printf("输入第 %d 个节点的值：\n",i);
        fflush(stdin);
        scanf("%c",&(T.nodes[i].data));
        T.nodes[i].firstchild=(ChildPtr*)malloc(sizeof(ChildPtr));
        T.nodes[i].firstchild->next=NULL;
 		
        printf("输入节点 %c 的孩子节点数量：\n",T.nodes[i].data);
        int num;
        scanf("%d",&num);
        if(num!=0){
            p = T.nodes[i].firstchild;
            for(int j = 0 ;j<num;j++){
                q=(ChildPtr*)malloc(sizeof(ChildPtr));
                q->next=NULL;
                printf("输入第 %d 个孩子节点在顺序表中的位置",j);
                scanf("%d",&(q->child));
                p->next=q;
                p=p->next;
            }
        }
    }
    return OK;
}
 
void findKids(CTree T,char a){
    int j=0;
    ChildPtr *p;
    for(int i=0;i<T.n;i++){
        if(T.nodes[i].data==a){
            p=T.nodes[i].firstchild->next;
            while(p){
                j = 1;
                printf("%c ",T.nodes[p->child].data);
                p=p->next;
            }
            break;
        }
    }
    if(j==0){
        printf("此节点为叶子节点");
    }
}
 
int main(int argc, char** argv)
{
	char ch;
    CTree T;
    InitTree(T);
    T.r=0;
    printf("请输入你想找结点：\n");
    scanf("%c",&ch);
    printf("找出节点 %c 的所有孩子节点：",ch);
    findKids(T,ch);
    return 0;
}


