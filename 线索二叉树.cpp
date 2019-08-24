#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define ERROR 0

typedef char TElemType;
typedef int Status;
typedef enum PointerTag{Link, Thread};  //Link=0表示指针，Thread=1表示线索
typedef struct BiTNode  
{
	BiTNode *lchild;
	BiTNode *rchild;
	TElemType data;
	PointerTag LTag, RTag;  //左右标志
}BiTNode,*BiTree;
 
 
Status CreateBiTree(BiTree &T)
{
	TElemType a;
	scanf("%c",&a);
	if(a == '#')
		T = NULL;
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		if(!T)
			exit(OVERFLOW);
		T->data = a;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
 
	return OK;
}
Status PrintElement(TElemType e)
{
	printf("%c",e);  //用作访问结点
	return OK;
}
 
void InThreading(BiTree &pre, BiTree &p)
{
	if(p)
	{
		InThreading(pre,p->lchild);  //左子树线索化
		if(!p->lchild)  //前驱线索
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		else
		{
			p->LTag = Link;
		}
		if(!pre->rchild)  //后继线索
		{
			pre->RTag = Thread;
			pre->rchild = p; 
		}
		else
		{
			pre->RTag = Link;
		}
		pre = p;  //保持pre指向p的前驱
		InThreading(pre,p->rchild);  //后子树线索化
 
	}
}
 
Status InOrderThreading(BiTree &Thrt, BiTree &T)
{
	//中序遍历二叉树T，并将其中序线索化，Thrt指向头结点
	BiTree pre;  //设一指针指向刚访问过的结点
	Thrt = (BiTree)malloc(sizeof(BiTNode));
	if(!Thrt)
		exit(OVERFLOW);
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;  //右指针回指
	if(!T)
		Thrt->lchild = Thrt;  //若二叉树空，则左指针回指
	else
	{
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(pre,T);  //中序遍历进行中序线索化
		pre->rchild = Thrt;  
		pre->RTag = Thread;  //最后一个结点线索化
		Thrt->rchild = pre;
		Thrt->RTag = Thread;
	}
	return OK;
}
 
Status InOrderTraverse_Thr(BiTree T, Status(*Visit)(TElemType e))
{
	//T指向头结点，头结点的左链lchild指向根结点，可参见以上线索化算法
	//中序遍历二叉树线索树T的非递归算法，对每个数据元素调用函数Visit
	BiTree p;
	p = T->lchild;  //p指向根结点
	while(p != T)
	{
		while(p->LTag == Link)
			p = p->lchild;
		if(!Visit(p->data))
			return ERROR;  //访问其左子树为空的结点
		while(p->RTag == Thread && p->rchild != T)
		{
			p = p->rchild;
			Visit(p->data);//访问后继结点
		}
		p = p->rchild;
	}
	return OK;
}
int main()
{
	BiTree T;
	printf("以先序的顺序输入一棵二叉树，#表示空树:\n");
	CreateBiTree(T);
	printf("线索化后的中序输出:\n");
	BiTree Thrt;  //线索化的头结点
	InOrderThreading(Thrt, T);
	InOrderTraverse_Thr(Thrt,PrintElement);
	printf("\n");
 
	return 0;
}
