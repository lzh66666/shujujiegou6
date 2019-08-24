#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define UINTMAX 100

typedef int Status;

typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;

Status Select(HuffmanTree &HT,int i,int &s1,int &s2);
int Min(HuffmanTree &HT,int i);
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n);

int main(int argc, char** argv) {
	HuffmanTree HT;
	HuffmanCode HC;
	printf("请输入权值的个数:\n");
	int n;
	scanf("%d",&n);
	int *w = (int*)malloc(n*sizeof(int));
	printf("请分别输入%d个权值:\n",n);
	int i;
	for(i=0; i<n; ++i)
	{
		scanf("%d",w+i);
	}
 
	HuffmanCoding(HT, HC, w, n);
 
	printf("赫夫曼树为：\n");
	printf("NO\tweight\tparent\tlchild\trchild\n");
	for(i=1; i <= 2*n-1; ++i)
	{
		printf("%d\t%d\t%d\t%d\t%d\n", i, HT[i].weight, HT[i].parent,HT[i].lchild, HT[i].rchild);
	}
	printf("赫夫曼编码为:\n");
	for(i = 1; i <= n; ++i)
		printf("%d|  |-->%s\n", i, HC[i]);
	return 0;
}

int Min(HuffmanTree &HT,int i)
{
	//在HT[1...i]中选择parent为0且权值最小的结点
	//返回该结点的下标值
	//此函数被Select函数调用
	int j;
	unsigned int k = UINTMAX;//假设各结点的权值不会超过UINTMAX
	int flag;
	for(j = 1; j <= i; ++j)
	{
		if(HT[j].weight < k && HT[j].parent == 0)//用父结点是否为0来判断此结点是否已经被选过
		{
			k = HT[j].weight;
			flag = j;
		}
	}
	HT[flag].parent = 1;//作个标记，说明已经被选择了，因为在Select函数中要选择权值小的两个结点
	return flag;
}



Status Select(HuffmanTree &HT,int i,int &s1,int &s2)
{
	//在HT[1..i-1]选择parent为0且weight最小的两个结点
	//s1<s2 
	s1=Min(HT,i);
	s2=Min(HT,i);
}

void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n){
	//w存放n个字符的权值(均>0) ,构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC。
	int i,s1,s2,start;
	HuffmanTree p;
	if(n<=1)
		return ;
	int m=2*n-1;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));		//0号单元未用 
	for(p=HT+1,i=1;i<=n;++i,++p,++w)
	{
		(*p).weight=*w;
		(*p).parent=0;
		(*p).lchild=0;
		(*p).rchild=0; 
	} 
	for(;i<=m;++i,++p)
	{
		(*p).weight=0;
		(*p).parent=0;
		(*p).lchild=0;
		(*p).rchild=0; 
	}
	for(i=n+1;i<=m;++i)
	{ //构造赫夫曼树 
		Select(HT,i-1,s1,s2); 
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	
	//---从叶子到根逆向求每个字符的赫夫曼编码---
	char *cd;
	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));	//分配n个字符编码的头指针向量 
	cd=(char*)malloc(n*sizeof(char));			//分配求编码的工作空间 
	cd[n-1]='\0';								//编码结束符 
	for(i=1;i<=n;i++){							//逐个字符求赫夫曼编码 
		start=n-1;								//编码结束符位置
		for(int c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent) //从叶子到根逆向求编码
			if(HT[f].lchild==c) 
				cd[--start]='0';
			else
				cd[--start]='1';
		HC[i]=(char *)malloc((n-start)*sizeof(char));	//为第i个字符编码分配空间
		strcpy(HC[i],&cd[start]);
	} 
	free(cd);
}


