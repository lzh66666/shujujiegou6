#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0

#define MAX_TREE_SIZE 100

typedef int Status;
typedef char TElemType;

typedef struct Snode  //���ṹ
{
    TElemType data;
    int parent;
}PTNode;

typedef struct  //���ṹ 
{
    PTNode nodes[MAX_TREE_SIZE];
    int r,n;                 //����λ�úͽ����� 
}PTree;

typedef PTree MFSet;

//���Һ���,ȷ��S��x�����Ӽ�Si 
int find_mfset(MFSet S,int i){
	//�Ҽ���S��i�����Ӽ��ĸ�.
	int j;
	if(i<0 || i>S.n)
		return -1;//i������S����һ�Ӽ� 
	for(j = i;S.nodes[j].parent>=0;j=S.nodes[j].parent); 
	return j;
}

//��������Һ���
int fix_mfset(MFSet &S,int i){
	//ȷ��i�����Ӽ�,������i����·�������н�㶼��ɸ��ĺ��ӽ��.
	int j,t;
	if(i<0 || i>S.n)
		return -1; //i����S����һ�Ӽ��ĳ�Ա
	for(j = i;S.nodes[j].parent>=0;j=S.nodes[j].parent); 
	for(int k = i;k != j;k=t){
		t = S.nodes[k].parent;
		S.nodes[k].parent = j;
	}
	return j; 
}

//�鲢����,��Si��Sj�е�һ��������һ����
Status merge_mfset(MFSet &S,int i,int j){
	//S.nodes[i]��S.nodes[j] �ֱ�ΪS�Ļ����ཻ�������Ӽ�Si��Sj�ĸ����
	//�󲢼�SiUSj.
	if(i<0 ||i>S.n || j<0 || j>S.n)
		return ERROR;
	S.nodes[i].parent = j;
	return OK; 
}

//������鲢����
Status mix_mfset(MFSet &S,int i,int j){
	//S.nodes[i]��S.nodes[j] �ֱ�ΪS�Ļ����ཻ�������Ӽ�Si��Sj�ĸ����
	//�󲢼�SiUSj.
	if(i<0 ||i>S.n || j<0 || j>S.n)
		return ERROR;
	if(S.nodes[i].parent>S.nodes[j].parent){
		//Si������Ա����Sj��
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
	
    printf("�Զ�������\n");
    S.r = 0;
    S.n = 0;  //��ʼ��Ϊ�㣬����������
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
    	printf("�ڼ���S��6�����Ӽ��ĸ�Ϊ��%d\n",j);
    else
    	printf("��(6)���Ϊ��\n"); 
    printf("\n\n��S0��S6�ϲ���:\n");
    mix_mfset(S,0,6);
    Print_mfset(S);
    
    j = fix_mfset(S,7);
    printf("�ڼ���S��7 �����Ӽ��ĸ�Ϊ��%d\n",j);
    return 0;
} 


