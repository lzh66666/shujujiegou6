#include <stdlib.h>
#include <stdio.h>

#define ERROR 0
#define OK 1
#define OVERFLOW -2

#define SIZE 8	//棋盘大小

typedef int Status; 

typedef struct {
	int r[SIZE+1];
	int num; 
}Queen,*QueenP;//棋盘数据结构:r[i]代表第i行,其值表示该行第几列有棋子

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

//四皇后棋盘:在nXn棋盘第i行上放置棋子,算法从i=1开始,到i=n结束
void Trial(QueenP Q,int n,int i){
	if(i>n)
		Print(Q);
	else{
		int j;
		for(j = 1;j <= n;j++){
			Q->num = i;
			Q->r[i] = j;	//在棋盘第i行第j列位置放置棋子
			if(Judge(Q))	//如果当前放置符合要求,则继续往下一行放置
				Trial(Q,n,i+1); 
		}
	}
} 

//打印棋盘
void Print(QueenP Q){
	int i;
	printf("\n");
	for(i = 1;i <= Q->num;i++)
		printf(" %d ",Q->r[i]);
	printf("\n");
}

//判断当前棋盘是否有符合约束条件
Status Judge(QueenP Q){
	int i;
	if(Q->num<2)	//如果只有一个棋子,则肯定是符合的 
		return OK;
	for(i = 1;i<Q->num;i++){
		int j;
		for(j = i+1;j <= Q->num;j++){
			if(Q->r[i] == Q->r[j])	//如果两个棋子同一列,则不符合
				return ERROR; 
		}
		if(Q->r[i] == Q->r[i+1]-1 || Q->r[i] == Q->r[i+1]+1)	//如果棋子和下一个棋子在对角线上,则不符合 
			return ERROR; 
	}
	return OK;
} 
