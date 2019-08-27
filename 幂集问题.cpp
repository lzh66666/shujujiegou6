#include <stdlib.h>
#include <stdio.h>

#define ERROR 0
#define OK 1
#define OVERFLOW -2

#define LIST_INIT_SIZE 100 // 线性表存储空间的初始分配量
#define LISTINCREMENT 10 // 线性表存储空间的分配增量

typedef int Status; 
typedef int ElemType; 

//>>>>>>>>>>>>>>>>>>>>>>>有关线性表的运算>>>>>>>>>>>>>>>>>>>>>>>>> 
typedef struct{
	ElemType *elem;
	int length;
	int listSize;
}Sqlist;

Status InitList_Sq(Sqlist &L){
	//构造一个空的线性表
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem)
		exit(OVERFLOW);
	L.length = 0;
	L.listSize = LIST_INIT_SIZE;
	return OK; 
}

Status ListInsert_Sq(Sqlist &L,int i,ElemType e){
	//在顺序表上的第i个元素和第i-1个元素中间插入元素
	if(L.length >= L.listSize){
		printf("空间已满");
		return ERROR; 
	} 
	if(i == L.length){
		L.elem[i] = e;
		L.length++;
		return OK;
	}
	if(i<0 || i>L.length-1){
		printf("插入的元素非法!");
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
		printf("删除的元素非法!");
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

//>>>>>>>>>>>>>>>>>>>>>>>>有关幂集的运算>>>>>>>>>>>>>>>>>>>>>>>>>> 

void PowerSet(int i,int n,Sqlist listA,Sqlist &listB){
	//求含n个元素的所有集合 ,对于第i个元素的要与不要形成的二叉树
	//i代表的是当前元素的索引 ,n是集合中元素的个数
	if(i == n){
		//到了最后一个元素的时候
		PrintList(listB); 
	} 
	else{
		//这个元素的要与不要
		//要了
		ListInsert_Sq(listB,listB.length,listA.elem[i]); 
		PowerSet(i+1,n,listA,listB);
		//不要 
		//还原回原来的地方 //这里还原的是要把当前进入list的数组删除掉
		int temp;
		ListDelete_Sq(listB,listB.length,temp);
		PowerSet(i+1,n,listA,listB); 
	}
} 

int main(int argc, char** argv) {
	Sqlist listA;
	InitList_Sq(listA);
	int n,m;
	printf("请输入集合A的元素个数:");
	scanf("%d",&n);
	printf("\n请输入集合A的元素:如(1 2 3)\n"); 
	for(int i = 0;i < n;i++){
		scanf("%d",&m);
		ListInsert_Sq(listA,listA.length,m);
	}
	Sqlist listB;
	InitList_Sq(listB);
	printf("\n幂集集合的结果为:\n\n");
	PowerSet(0,n,listA,listB);
	
	return 0;
}


