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
	struct BiTNode *lchild,*rchild;	//左右孩子指针 
}BiTNode,*BiTree;

typedef BiTree SElemType;

typedef struct{
	SElemType *base,*top;
	int stacksize;
}Sqstack;

Status InitStack(Sqstack &S);			//初始化栈 
Status Push(Sqstack &S,SElemType P);	//入栈 
Status Pop(Sqstack &S,SElemType &P);	//出栈 
Status Empty(Sqstack S);				//判空栈 

Status CreateBiTree(BiTree &T);		//构造二叉树
Status PreOrderTraverse(BiTree T);	//先序遍历非递归二叉树 
Status InOrderTraverse(BiTree T);	//中序遍历非递归二叉树 
Status PostOrderTraverse(BiTree T);	//后序遍历非递归二叉树 

int main(int argc, char** argv) {
	BiTree T;
	printf("请按先序遍历输入二叉树：\n");
	CreateBiTree(T);
	printf("\n按先序遍历二叉树的输出结果为：\n");
	PreOrderTraverse(T);
	printf("\n按中序遍历二叉树的输出结果为：\n");
	InOrderTraverse(T);
	printf("\n按后序遍历二叉树的输出结果为：\n");
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




Status CreateBiTree(BiTree &T){		//按先序次序输入二叉树中节点的值（一个字符），#字符表示空树 
	//构造二叉链表表示的二叉树T
	char ch;
	scanf("%c",&ch);
	if(ch=='#')
		T=NULL;
	else{
		T=(BiTNode *)malloc(sizeof(BiTNode));
		if(!T)
			exit(OVERFLOW);
		T->data=ch;		//生成根节点
		CreateBiTree(T->lchild);	//构造左子树 
		CreateBiTree(T->rchild); 	//构造右子树 
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
		if(P)				//访问根节点，根指针入栈，遍历左子树 
		{
			printf("%c",P->data);
			Push(S,P);
			P=P->lchild;
		}
		else				//根指针退栈，遍历右子树 
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
		if(P)			//根指针进栈，遍历左子树 
		{
			Push(S,P);
			P=P->lchild;
		}
		else			//根指针退栈，访问根节点，遍历右子树 
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
		if(P)			//根指针入栈，做标记，遍历左子树 
		{
			Push(S,P);
			flag[++index]=2;
			P=P->lchild;
		}
		else
		{
			Pop(S,P);			//根指针退栈 
			if(flag[index]==2){
				Push(S,P);		//根指针入栈 
				P=P->rchild;	//遍历右子树 
				flag[index]=1;	//标记更改 
			}
			else{
				printf("%c",P->data);	//访问根节点 
				--index;
				P=NULL;
			}	
		}
	}
	return OK;
 } 
