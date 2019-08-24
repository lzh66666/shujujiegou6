#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int TElemType;
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild,*rchild;	//左右孩子指针 
}BiTNode,*BiTree;

Status CreateBiTree(BiTree &T);		//构造二叉树
Status PreOrderTraverse(BiTree T);	//先序遍历递归二叉树 
Status InOrderTraverse(BiTree T);	//中序遍历递归二叉树 
Status PostOrderTraverse(BiTree T);	//后序遍历递归二叉树 

int main(int argc, char** argv) {
	BiTree T;
	printf("请按先序遍历输入二叉树：如:ABC##DE#G##F###\n");
	CreateBiTree(T);
	printf("\n按先序遍历二叉树的输出结果为：\n");
	PreOrderTraverse(T);
	printf("\n按中序遍历二叉树的输出结果为：\n");
	InOrderTraverse(T);
	printf("\n按后序遍历二叉树的输出结果为：\n");
	PostOrderTraverse(T);
	return 0;
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

Status PostOrderTraverse(BiTree T)
{
	if(T){
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c",T->data);
	}
	return OK;
 } 
