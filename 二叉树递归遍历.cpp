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
	struct BiTNode *lchild,*rchild;	//���Һ���ָ�� 
}BiTNode,*BiTree;

Status CreateBiTree(BiTree &T);		//���������
Status PreOrderTraverse(BiTree T);	//��������ݹ������ 
Status InOrderTraverse(BiTree T);	//��������ݹ������ 
Status PostOrderTraverse(BiTree T);	//��������ݹ������ 

int main(int argc, char** argv) {
	BiTree T;
	printf("�밴��������������������:ABC##DE#G##F###\n");
	CreateBiTree(T);
	printf("\n�����������������������Ϊ��\n");
	PreOrderTraverse(T);
	printf("\n�����������������������Ϊ��\n");
	InOrderTraverse(T);
	printf("\n�����������������������Ϊ��\n");
	PostOrderTraverse(T);
	return 0;
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

Status PostOrderTraverse(BiTree T)
{
	if(T){
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c",T->data);
	}
	return OK;
 } 
