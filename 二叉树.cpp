#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define TURE 1
#define FLASE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define MAXSIZE 100

typedef int Status;
typedef char TElemType;

typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild,*rchild;	//���Һ���ָ�� 
}BiTNode,*BiTree;

typedef BiTree SElemType;

typedef struct{
	SElemType *base,*top;
	int stacksize;
}Sqstack;

Status InitStack(Sqstack &S);			//��ʼ��ջ 
Status Push(Sqstack &S,SElemType P);	//��ջ 
Status Pop(Sqstack &S,SElemType &P);	//��ջ 
Status Empty(Sqstack S);				//�п�ջ 

Status CreateBiTree(BiTree &T);		//���������
Status PreOrderTraverse(BiTree T);	//��������ݹ������ 
Status InOrderTraverse(BiTree T);	//��������ݹ������ 
Status InOrderTraverse_stack(BiTree T);	//��������ǵݹ������ 
Status PostOrderTraverse(BiTree T);	//��������ݹ������ 
int BiTreeDeep(BiTree T);			//����������� 
int BiTreeNodeCount(BiTree T);			//�������нڵ���� 
void PrintTree(BiTree T);			//�Թ�������ʽ��������� 

int main(int argc, char** argv) {
	BiTree T;
	printf("�밴������������������\n");
	CreateBiTree(T);
	printf("������ݹ������������������Ϊ��\n");
	PreOrderTraverse(T);
	printf("\n������ݹ������������������Ϊ��\n");
	InOrderTraverse(T);
	printf("\n������ǵݹ������������������Ϊ��\n");
	InOrderTraverse_stack(T); 
	printf("\n������ݹ������������������Ϊ��\n");
	PostOrderTraverse(T);
	printf("\n�����������Ϊ��%d\n",BiTreeDeep(T));
	printf("�������Ľڵ����Ϊ��%d\n",BiTreeNodeCount(T));
	printf("�Թ�������ʽ�����������\n");
	printf("(");
	PrintTree(T);
	printf(")");
	return 0;
}

Status InitStack(Sqstack &S)
{
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

Status Push(Sqstack &S,SElemType P)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(S.base==NULL)
			exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*(S.top++)=P;
	return OK;
}

Status Pop(Sqstack &S,SElemType &P)
{
	if(S.top==S.base)
		return ERROR;
	P=*(--S.top);
	return OK; 
}

Status Empty(Sqstack S)
{
	if(S.top==S.base)
		return TURE;
	else
		return FLASE;
}

Status CreateBiTree(BiTree &T){		//�������������������нڵ��ֵ��һ���ַ������ո��ַ���ʾ���� 
	//������������ʾ�Ķ�����T
	char ch;
	scanf("%c",&ch);
	if(ch=='#')
		T=NULL;
	else{
		T=(BiTNode *)malloc(sizeof(BiTNode));
		if(!T)
			exit(OVERFLOW);
		T->data=ch;		//���ɸ��ڵ�
		CreateBiTree(T->lchild);	//���������� 
		CreateBiTree(T->rchild); 	//���������� 
	}
	return OK; 
}

Status PreOrderTraverse(BiTree T)
{
	if(T){
		printf("%c",T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
	return OK;
} 

Status InOrderTraverse(BiTree T)
{
	if(T){
		InOrderTraverse(T->lchild);
		printf("%c",T->data);
		InOrderTraverse(T->rchild);
	}
	return OK;
} 

Status InOrderTraverse_stack(BiTree T)
{
	Sqstack S;
	BiTree P=T;
	InitStack(S);
	while(P || !Empty(S))
	{
		if(P)			//��ָ���ջ������������ 
		{
			Push(S,P);
			P=P->lchild;
		}
		else			//��ָ����ջ�����ʸ��ڵ㣬���������� 
		{
			Pop(S,P);
			printf("%c",P->data);
			P=P->rchild;
		}
	}
	return OK;
}

Status PostOrderTraverse(BiTree T)
{
	if(T){
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c",T->data);
	}
	return OK;
} 
 
int BiTreeDeep(BiTree T)
{
	int l,r;
	if (T== NULL)
        return ERROR;
    if (T->lchild == NULL&&T->rchild == NULL) 
        return 1;
    l=BiTreeDeep(T->lchild);  
    r=BiTreeDeep(T->rchild);
    return (l>r ? l : r)+1;
}

int BiTreeNodeCount(BiTree T)
{
	if(T==NULL)
		return ERROR;
	return BiTreeNodeCount(T->lchild) + BiTreeNodeCount(T->rchild) + 1;
 } 
 
void PrintTree(BiTree T)
{
	if(T){
		printf("%c",T->data);
		if(T->lchild!=NULL || T->rchild!=NULL)
		{
			printf("(");
			PrintTree(T->lchild);
			if(T->lchild!=NULL && T->rchild!=NULL)
				printf(",");
			PrintTree(T->rchild);
			printf(")");
		}
	}
	
}
