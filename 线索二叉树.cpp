#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define ERROR 0

typedef char TElemType;
typedef int Status;
typedef enum PointerTag{Link, Thread};  //Link=0��ʾָ�룬Thread=1��ʾ����
typedef struct BiTNode  
{
	BiTNode *lchild;
	BiTNode *rchild;
	TElemType data;
	PointerTag LTag, RTag;  //���ұ�־
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
	printf("%c",e);  //�������ʽ��
	return OK;
}
 
void InThreading(BiTree &pre, BiTree &p)
{
	if(p)
	{
		InThreading(pre,p->lchild);  //������������
		if(!p->lchild)  //ǰ������
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		else
		{
			p->LTag = Link;
		}
		if(!pre->rchild)  //�������
		{
			pre->RTag = Thread;
			pre->rchild = p; 
		}
		else
		{
			pre->RTag = Link;
		}
		pre = p;  //����preָ��p��ǰ��
		InThreading(pre,p->rchild);  //������������
 
	}
}
 
Status InOrderThreading(BiTree &Thrt, BiTree &T)
{
	//�������������T��������������������Thrtָ��ͷ���
	BiTree pre;  //��һָ��ָ��շ��ʹ��Ľ��
	Thrt = (BiTree)malloc(sizeof(BiTNode));
	if(!Thrt)
		exit(OVERFLOW);
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;  //��ָ���ָ
	if(!T)
		Thrt->lchild = Thrt;  //���������գ�����ָ���ָ
	else
	{
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(pre,T);  //���������������������
		pre->rchild = Thrt;  
		pre->RTag = Thread;  //���һ�����������
		Thrt->rchild = pre;
		Thrt->RTag = Thread;
	}
	return OK;
}
 
Status InOrderTraverse_Thr(BiTree T, Status(*Visit)(TElemType e))
{
	//Tָ��ͷ��㣬ͷ��������lchildָ�����㣬�ɲμ������������㷨
	//�������������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
	BiTree p;
	p = T->lchild;  //pָ������
	while(p != T)
	{
		while(p->LTag == Link)
			p = p->lchild;
		if(!Visit(p->data))
			return ERROR;  //������������Ϊ�յĽ��
		while(p->RTag == Thread && p->rchild != T)
		{
			p = p->rchild;
			Visit(p->data);//���ʺ�̽��
		}
		p = p->rchild;
	}
	return OK;
}
int main()
{
	BiTree T;
	printf("�������˳������һ�ö�������#��ʾ����:\n");
	CreateBiTree(T);
	printf("����������������:\n");
	BiTree Thrt;  //��������ͷ���
	InOrderThreading(Thrt, T);
	InOrderTraverse_Thr(Thrt,PrintElement);
	printf("\n");
 
	return 0;
}
