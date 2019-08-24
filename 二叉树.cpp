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
Status PreOrderTraverse(BiTree T);	//先序遍历递归二叉树 
Status InOrderTraverse(BiTree T);	//中序遍历递归二叉树 
Status InOrderTraverse_stack(BiTree T);	//中序遍历非递归二叉树 
Status PostOrderTraverse(BiTree T);	//后序遍历递归二叉树 
int BiTreeDeep(BiTree T);			//二叉树的深度 
int BiTreeNodeCount(BiTree T);			//二叉树中节点个数 
void PrintTree(BiTree T);			//以广义表的形式输出二叉树 

int main(int argc, char** argv) {
	BiTree T;
	printf("请按先序遍历输入二叉树：\n");
	CreateBiTree(T);
	printf("按先序递归遍历二叉树的输出结果为：\n");
	PreOrderTraverse(T);
	printf("\n按中序递归遍历二叉树的输出结果为：\n");
	InOrderTraverse(T);
	printf("\n按中序非递归遍历二叉树的输出结果为：\n");
	InOrderTraverse_stack(T); 
	printf("\n按后序递归遍历二叉树的输出结果为：\n");
	PostOrderTraverse(T);
	printf("\n二叉树的深度为：%d\n",BiTreeDeep(T));
	printf("二叉树的节点个数为：%d\n",BiTreeNodeCount(T));
	printf("以广义表的形式输出二叉树：\n");
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

Status CreateBiTree(BiTree &T){		//按先序次序输入二叉树中节点的值（一个字符），空格字符表示空树 
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
