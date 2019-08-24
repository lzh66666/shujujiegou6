#include<stdio.h>
#include<stdlib.h>

#define MAX_TREE_SIZE 100

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

void InitPNode(PTree &tree)
{
    int i,j;
    char ch;
    printf("�����������:\n");
    scanf("%d",&(tree.n));

	//�����������Ϊ-1 
    printf("�����������ֵ��˫�����:��(A,-1)\n");
    for(i=0; i<tree.n; i++)
    {
     fflush(stdin);
     scanf("%c,%d",&ch,&j);
     tree.nodes[i].data = ch;
     tree.nodes[i].parent = j;
    }
    tree.nodes[0].parent = -1;
}

void FindParent(PTree &tree) 
{
    int i,j;
    printf("������Ҫ��ѯ�Ľ������(��:0)\n");
    scanf("%d",&i);
    j=tree.nodes[i].parent;
    printf(" %c �ĸ��׽��Ϊ��%c ,������Ϊ %d\n",tree.nodes[i].data,tree.nodes[j].data,j);
}

int main() 
{
    PTree tree;
    InitPNode(tree);
    while(1) //���� 
    FindParent(tree); 
    return 0;
} 


