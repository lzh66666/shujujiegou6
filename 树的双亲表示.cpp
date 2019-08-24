#include<stdio.h>
#include<stdlib.h>

#define MAX_TREE_SIZE 100

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

void InitPNode(PTree &tree)
{
    int i,j;
    char ch;
    printf("请输入结点个数:\n");
    scanf("%d",&(tree.n));

	//根结点的序号设为-1 
    printf("请输入结点的序及值其双亲序号:如(A,-1)\n");
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
    printf("请输入要查询的结点的序号(如:0)\n");
    scanf("%d",&i);
    j=tree.nodes[i].parent;
    printf(" %c 的父亲结点为：%c ,结点序号为 %d\n",tree.nodes[i].data,tree.nodes[j].data,j);
}

int main() 
{
    PTree tree;
    InitPNode(tree);
    while(1) //测试 
    FindParent(tree); 
    return 0;
} 


