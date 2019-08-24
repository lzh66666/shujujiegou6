#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef char TElemType;

typedef enum PointerTag{Link,Thread};	//Link==0:ָ�룬Thread==1:���� 

typedef struct BiThrNode{
	TElemType data;
	struct BiThrNode *lchild,*rchild;
	PointerTag LTag,RTag;				//���ұ�־ 
}BiThrNode,*BiThrTree;

Status CreateBiTree(BiThrTree &T){		//�������������������нڵ��ֵ��һ���ַ������ո��ַ���ʾ���� 
	//������������ʾ�Ķ�����T
	char ch;
	scanf("%c",&ch);
	if(ch=='#')
		T=NULL;
	else{
		T=(BiThrTree)malloc(sizeof(BiThrNode));
		if(!T)
			exit(OVERFLOW);
		T->data=ch;		//���ɸ��ڵ�
		CreateBiTree(T->lchild);	//���������� 
		CreateBiTree(T->rchild); 	//���������� 
	}
	return OK; 
}



void InThreading(BiThrTree &pre,BiThrTree &p){
	if(p){
		InThreading(pre,p->lchild);		//������������
		if(!p->lchild){				//ǰ������ 
			p->LTag=Thread;
			p->lchild=pre;
		} 
		else
		{
			p->LTag=Link;
		}
		if(!pre->rchild){			//������� 
			pre->RTag=Thread;
			pre->rchild=p;
		}
		else
		{
			p->RTag=Link;
		}
		pre=p;					//����preָ��p��ǰ�� 
		InThreading(pre,p->rchild);		//������������ 
	}
}

Status InOrderThreading(BiThrTree &Thrt,BiThrTree &T){
	//�������������T,����������������,Thrtָ��ͷ��� 
	BiThrTree pre;
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
		exit(OVERFLOW);
		
	Thrt->LTag=Link;			//��ͷ��� 
	Thrt->RTag = Thread;
	Thrt->rchild=Thrt;			//��ָ���ָ
	
	if(!T)
		Thrt->lchild=Thrt;		//���������գ�����ָ���ָ
	else{
		Thrt->lchild=T;
		pre=Thrt;
		InThreading(pre,T);		//��������������������� 
		pre->rchild=Thrt;		//���һ���ڵ������� 
		pre->RTag=Thread;
		Thrt->rchild=pre;
		Thrt->RTag = Thread;
	} 
	return OK;
}

Status InOrderTraverse_Thr(BiThrTree T){
	//Tָ��ͷ���,ͷ��������lchildָ������
	//�����������������T�ķǵݹ��㷨 
	BiThrTree p;
	p=T->lchild;	//pָ������ 
	while(p != T){	//�������������ʱ,P == T 
		while(p->LTag == Link)
			p=p->lchild;
		if(p->data)
			printf("%c",p->data);
		else		//������������Ϊ�յĽ�� 
			return ERROR;
		while(p->RTag == Thread && p->rchild!=T)	//���ʺ�̽�� 
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
	printf("�밴������������������\n");
	CreateBiTree(T);
	
	BiThrTree Thrt;
	InOrderThreading(Thrt,T);
	printf("��������������������Ϊ:\n"); 
	InOrderTraverse_Thr(Thrt);
	
	return 0;
}
