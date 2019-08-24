#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef char TElemType;

typedef enum PointerTag{Link,Thread};	//Link==0:指针，Thread==1:线索 

typedef struct BiThrNode{
	TElemType data;
	struct BiThrNode *lchild,*rchild;
	PointerTag LTag,RTag;				//左右标志 
}BiThrNode,*BiThrTree;

Status CreateBiTree(BiThrTree &T){		//按先序次序输入二叉树中节点的值（一个字符），空格字符表示空树 
	//构造二叉链表表示的二叉树T
	char ch;
	scanf("%c",&ch);
	if(ch=='#')
		T=NULL;
	else{
		T=(BiThrTree)malloc(sizeof(BiThrNode));
		if(!T)
			exit(OVERFLOW);
		T->data=ch;		//生成根节点
		CreateBiTree(T->lchild);	//构造左子树 
		CreateBiTree(T->rchild); 	//构造右子树 
	}
	return OK; 
}



void InThreading(BiThrTree &pre,BiThrTree &p){
	if(p){
		InThreading(pre,p->lchild);		//左子树线索化
		if(!p->lchild){				//前驱线索 
			p->LTag=Thread;
			p->lchild=pre;
		} 
		else
		{
			p->LTag=Link;
		}
		if(!pre->rchild){			//后继线索 
			pre->RTag=Thread;
			pre->rchild=p;
		}
		else
		{
			p->RTag=Link;
		}
		pre=p;					//保持pre指向p的前驱 
		InThreading(pre,p->rchild);		//右子树线索化 
	}
}

Status InOrderThreading(BiThrTree &Thrt,BiThrTree &T){
	//中序遍历二叉树T,并将其中序线索化,Thrt指向头结点 
	BiThrTree pre;
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
		exit(OVERFLOW);
		
	Thrt->LTag=Link;			//建头结点 
	Thrt->RTag = Thread;
	Thrt->rchild=Thrt;			//右指针回指
	
	if(!T)
		Thrt->lchild=Thrt;		//若二叉树空，则左指针回指
	else{
		Thrt->lchild=T;
		pre=Thrt;
		InThreading(pre,T);		//中序遍历进行中序线索化 
		pre->rchild=Thrt;		//最后一个节点线索化 
		pre->RTag=Thread;
		Thrt->rchild=pre;
		Thrt->RTag = Thread;
	} 
	return OK;
}

Status InOrderTraverse_Thr(BiThrTree T){
	//T指向头结点,头结点的左链lchild指向根结点
	//中序遍历线索二叉树T的非递归算法 
	BiThrTree p;
	p=T->lchild;	//p指向根结点 
	while(p != T){	//空树或遍历结束时,P == T 
		while(p->LTag == Link)
			p=p->lchild;
		if(p->data)
			printf("%c",p->data);
		else		//访问其左子树为空的结点 
			return ERROR;
		while(p->RTag == Thread && p->rchild!=T)	//访问后继结点 
		{
			p=p->rchild;
			printf("%c",p->data);
		}
		p=p->rchild;
	}
	return OK;
}
 
int main(int argc, char** argv) {
	BiThrTree T;
	printf("请按先序遍历输入二叉树：\n");
	CreateBiTree(T);
	
	BiThrTree Thrt;
	InOrderThreading(Thrt,T);
	printf("线索二叉树中序遍历结果为:\n"); 
	InOrderTraverse_Thr(Thrt);
	
	return 0;
}
