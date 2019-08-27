#include <stdlib.h>
#include <stdio.h>

#define ERROR 0
#define OK 1
#define OVERFLOW -2

#define LIST_INIT_SIZE 100 // ���Ա�洢�ռ�ĳ�ʼ������
#define LISTINCREMENT 10 // ���Ա�洢�ռ�ķ�������

typedef int Status; 
typedef int ElemType; 

//>>>>>>>>>>>>>>>>>>>>>>>�й����Ա������>>>>>>>>>>>>>>>>>>>>>>>>> 
typedef struct{
	ElemType *elem;
	int length;
	int listSize;
}Sqlist;

Status InitList_Sq(Sqlist &L){
	//����һ���յ����Ա�
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem)
		exit(OVERFLOW);
	L.length = 0;
	L.listSize = LIST_INIT_SIZE;
	return OK; 
}

Status ListInsert_Sq(Sqlist &L,int i,ElemType e){
	//��˳����ϵĵ�i��Ԫ�غ͵�i-1��Ԫ���м����Ԫ��
	if(L.length >= L.listSize){
		printf("�ռ�����");
		return ERROR; 
	} 
	if(i == L.length){
		L.elem[i] = e;
		L.length++;
		return OK;
	}
	if(i<0 || i>L.length-1){
		printf("�����Ԫ�طǷ�!");
		return ERROR; 
	}
	for(int j = L.length;j >= i;j--){
		L.elem[i] = L.elem[j-1];
	} 
	L.elem[i] = e;
	L.listSize++;
	return OK;
}

Status ListDelete_Sq(Sqlist &L,int i,ElemType &e){
	if(i<0 || i>L.length){
		printf("ɾ����Ԫ�طǷ�!");
		return ERROR;
	}
	e = L.elem[i];
	for(int j = i;j<L.length-i-1;j++) 
		L.elem[j] = L.elem[j+1];
	L.length--;
	return OK;
}

void PrintList(Sqlist L){
	for(int i = 0;i < L.length;i++){
		printf("%d",L.elem[i]);
		if(i == L.length-1)
			continue;
		printf(",");
	}
	printf("\n");
} 

//>>>>>>>>>>>>>>>>>>>>>>>>�й��ݼ�������>>>>>>>>>>>>>>>>>>>>>>>>>> 

void PowerSet(int i,int n,Sqlist listA,Sqlist &listB){
	//��n��Ԫ�ص����м��� ,���ڵ�i��Ԫ�ص�Ҫ�벻Ҫ�γɵĶ�����
	//i������ǵ�ǰԪ�ص����� ,n�Ǽ�����Ԫ�صĸ���
	if(i == n){
		//�������һ��Ԫ�ص�ʱ��
		PrintList(listB); 
	} 
	else{
		//���Ԫ�ص�Ҫ�벻Ҫ
		//Ҫ��
		ListInsert_Sq(listB,listB.length,listA.elem[i]); 
		PowerSet(i+1,n,listA,listB);
		//��Ҫ 
		//��ԭ��ԭ���ĵط� //���ﻹԭ����Ҫ�ѵ�ǰ����list������ɾ����
		int temp;
		ListDelete_Sq(listB,listB.length,temp);
		PowerSet(i+1,n,listA,listB); 
	}
} 

int main(int argc, char** argv) {
	Sqlist listA;
	InitList_Sq(listA);
	int n,m;
	printf("�����뼯��A��Ԫ�ظ���:");
	scanf("%d",&n);
	printf("\n�����뼯��A��Ԫ��:��(1 2 3)\n"); 
	for(int i = 0;i < n;i++){
		scanf("%d",&m);
		ListInsert_Sq(listA,listA.length,m);
	}
	Sqlist listB;
	InitList_Sq(listB);
	printf("\n�ݼ����ϵĽ��Ϊ:\n\n");
	PowerSet(0,n,listA,listB);
	
	return 0;
}


