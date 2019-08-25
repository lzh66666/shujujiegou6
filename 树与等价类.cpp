#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0

#define MAX_TREE_SIZE 100

typedef int Status;
typedef char TElemType;

typedef struct Snode  //结点结构
{
    TElemType data;
    int parent;
}PTNode;

typedef struct  //树结构 
{
    PTNode nodes[MAX_TREE_SIZE];
    int r,n;                 //根的位置和结点个数 
}PTree;

typedef PTree MFSet;

//查找函数,确定S中x所属子集Si 
int find_mfset(MFSet S,int i){
	//找集合S中i所在子集的根.
	int j;
	if(i<0 || i>S.n)
		return -1;//i不属于S中任一子集 
	for(j = i;S.nodes[j].parent>=0;j=S.nodes[j].parent); 
	return j;
}

//升级版查找函数
int fix_mfset(MFSet &S,int i){
	//确定i所在子集,并将从i至根路径上所有结点都变成根的孩子结点.
	int j,t;
	if(i<0 || i>S.n)
		return -1; //i不是S中任一子集的成员
	for(j = i;S.nodes[j].parent>=0;j=S.nodes[j].parent); 
	for(int k = i;k != j;k=t){
		t = S.nodes[k].parent;
		S.nodes[k].parent = j;
	}
	return j; 
}

//归并操作,将Si和Sj中的一个并入另一个中
Status merge_mfset(MFSet &S,int i,int j){
	//S.nodes[i]和S.nodes[j] 分别为S的互不相交的两个子集Si和Sj的根结点
	//求并集SiUSj.
	if(i<0 ||i>S.n || j<0 || j>S.n)
		return ERROR;
	S.nodes[i].parent = j;
	return OK; 
}

//升级版归并操作
Status mix_mfset(MFSet &S,int i,int j){
	//S.nodes[i]和S.nodes[j] 分别为S的互不相交的两个子集Si和Sj的根结点
	//求并集SiUSj.
	if(i<0 ||i>S.n || j<0 || j>S.n)
		return ERROR;
	if(S.nodes[i].parent>S.nodes[j].parent){
		//Si所含成员数比Sj少
		S.nodes[j].parent += S.nodes[i].parent;
		S.nodes[i].parent = j; 
	}
	else{
		S.nodes[i].parent += S.nodes[j].parent;
		S.nodes[j].parent = i; 
	}
	return OK;
}

Status CreateMFSet_auto(MFSet &S)
{
    char ch1;
    char ch1_list1[6] = {'R','A','B','C','D','E'};
    char ch1_list2[4] = {'F','G','H','K'};
    int pos;
    int pos_list1[6] = {-5,0,0,0,1,1};
	int pos_list2[4] = {-3,0,0,1};
	
    printf("自动创建树\n");
    S.r = 0;
    S.n = 0;  //初始化为零，后续逐渐增加
    for(int j = 0;j < 6;j++){
        ch1 = ch1_list1[j];
        S.nodes[j].data = ch1;

        pos = pos_list1[j];
        S.nodes[j].parent = pos;
        S.n++;
    }
    for(int j = 6;j < 10;j++){
        ch1 = ch1_list2[j-6];
        S.nodes[j].data = ch1;

        pos = pos_list2[j-6];
        S.nodes[j].parent = pos;
        S.n++;
    }
    return OK;
}

void Print_mfset(MFSet S){
	for(int i=0;i<S.n;i++){
		printf("%d ",i);
    	printf("%c ",S.nodes[i].data);
    	printf("%d\n",S.nodes[i].parent);
	}
}

int main(int argc,char**argv) {
	MFSet S;
    CreateMFSet_auto(S);
    Print_mfset(S);
    
    int j = fix_mfset(S,6);
    if(j!=6)
    	printf("在集合S中6所在子集的根为：%d\n",j);
    else
    	printf("该(6)结点为根\n"); 
    printf("\n\n当S0和S6合并后:\n");
    mix_mfset(S,0,6);
    Print_mfset(S);
    
    j = fix_mfset(S,7);
    printf("在集合S中7 所在子集的根为：%d\n",j);
    return 0;
} 


