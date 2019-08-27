#include <stdlib.h>
#include <stdio.h>

#define ERROR 0
#define OK 1
#define OVERFLOW -2

#define SIZE 8	//���̴�С

typedef int Status; 

typedef struct {
	int r[SIZE+1];
	int num; 
}Queen,*QueenP;//�������ݽṹ:r[i]�����i��,��ֵ��ʾ���еڼ���������

void Init(QueenP &Q); 
void Trial(QueenP Q,int n,int i);
void Print(QueenP Q);
Status Judge(QueenP Q); 

int main(int argc, char** argv) {
	QueenP Q;
	Init(Q);
	Trial(Q,SIZE,1);
	return 0;
}

void Init(QueenP &Q){
	Q = (QueenP)malloc(sizeof(Queen));
	if(!Q)
		exit(OVERFLOW);
	Q->num = 0;
}

//�Ļʺ�����:��nXn���̵�i���Ϸ�������,�㷨��i=1��ʼ,��i=n����
void Trial(QueenP Q,int n,int i){
	if(i>n)
		Print(Q);
	else{
		int j;
		for(j = 1;j <= n;j++){
			Q->num = i;
			Q->r[i] = j;	//�����̵�i�е�j��λ�÷�������
			if(Judge(Q))	//�����ǰ���÷���Ҫ��,���������һ�з���
				Trial(Q,n,i+1); 
		}
	}
} 

//��ӡ����
void Print(QueenP Q){
	int i;
	printf("\n");
	for(i = 1;i <= Q->num;i++)
		printf(" %d ",Q->r[i]);
	printf("\n");
}

//�жϵ�ǰ�����Ƿ��з���Լ������
Status Judge(QueenP Q){
	int i;
	if(Q->num<2)	//���ֻ��һ������,��϶��Ƿ��ϵ� 
		return OK;
	for(i = 1;i<Q->num;i++){
		int j;
		for(j = i+1;j <= Q->num;j++){
			if(Q->r[i] == Q->r[j])	//�����������ͬһ��,�򲻷���
				return ERROR; 
		}
		if(Q->r[i] == Q->r[i+1]-1 || Q->r[i] == Q->r[i+1]+1)	//������Ӻ���һ�������ڶԽ�����,�򲻷��� 
			return ERROR; 
	}
	return OK;
} 
