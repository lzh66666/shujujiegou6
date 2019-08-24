#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 20
#define OK 1
typedef char TElemType;
typedef int Status;

//���ӱ�ʾ��
typedef struct CTNode{
    int child;//������ÿ�����洢�Ĳ������ݱ������������������д洢��λ���±�
    struct CTNode * next;
}ChildPtr;

typedef struct {
    TElemType data;//������������
    ChildPtr* firstchild;//���������ͷָ��
}CTBox;

typedef struct{
    CTBox nodes[MAX_SIZE];//�洢��������
    int n,r;//���������������λ��
}CTree;

Status InitTree(CTree &T){
	ChildPtr *p,*q;
    printf("����ڵ�������\n");
    scanf("%d",&(T.n));
    for(int i=0;i<T.n;i++){
        printf("����� %d ���ڵ��ֵ��\n",i);
        fflush(stdin);
        scanf("%c",&(T.nodes[i].data));
        T.nodes[i].firstchild=(ChildPtr*)malloc(sizeof(ChildPtr));
        T.nodes[i].firstchild->next=NULL;
 		
        printf("����ڵ� %c �ĺ��ӽڵ�������\n",T.nodes[i].data);
        int num;
        scanf("%d",&num);
        if(num!=0){
            p = T.nodes[i].firstchild;
            for(int j = 0 ;j<num;j++){
                q=(ChildPtr*)malloc(sizeof(ChildPtr));
                q->next=NULL;
                printf("����� %d �����ӽڵ���˳����е�λ��",j);
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
        printf("�˽ڵ�ΪҶ�ӽڵ�");
    }
}
 
int main(int argc, char** argv)
{
	char ch;
    CTree T;
    InitTree(T);
    T.r=0;
    printf("�����������ҽ�㣺\n");
    scanf("%c",&ch);
    printf("�ҳ��ڵ� %c �����к��ӽڵ㣺",ch);
    findKids(T,ch);
    return 0;
}


