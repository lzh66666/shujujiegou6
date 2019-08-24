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
Status PreOrderTraverse(BiTree T);	//��������ǵݹ������ 
Status InOrderTraverse(BiTree T);	//��������ǵݹ������ 
Status PostOrderTraverse(BiTree T);	//��������ǵݹ������ 

int main(int argc, char** argv) {
	BiTree T;
	printf("�밴������������������\n");
	CreateBiTree(T);
	printf("\n�����������������������Ϊ��\n");
	PreOrderTraverse(T);
	printf("\n�����������������������Ϊ��\n");
	InOrderTraverse(T);
	printf("\n�����������������������Ϊ��\n");
	PostOrderTraverse(T);
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




Status CreateBiTree(BiTree &T){		//�������������������нڵ��ֵ��һ���ַ�����#�ַ���ʾ���� 
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
	Sqstack S;
	BiTree P=T;
	InitStack(S);
	while(P || !Empty(S))
	{
		if(P)				//���ʸ��ڵ㣬��ָ����ջ������������ 
		{
			printf("%c",P->data);
			Push(S,P);
			P=P->lchild;
		}
		else				//��ָ����ջ������������ 
		{
			Pop(S,P);
			P=P->rchild;
		}
	}
	return OK;
} 

Status InOrderTraverse(BiTree T)
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
	int flag[50],index=-1;
	Sqstack S;
	BiTree P=T;
	InitStack(S);
	while(P || !Empty(S))
	{
		if(P)			//��ָ����ջ������ǣ����������� 
		{
			Push(S,P);
			flag[++index]=2;
			P=P->lchild;
		}
		else
		{
			Pop(S,P);			//��ָ����ջ 
			if(flag[index]==2){
				Push(S,P);		//��ָ����ջ 
				P=P->rchild;	//���������� 
				flag[index]=1;	//��Ǹ��� 
			}
			else{
				printf("%c",P->data);	//���ʸ��ڵ� 
				--index;
				P=NULL;
			}	
		}
	}
	return OK;
 } 
