#include <iostream>
#include<stdlib.h>

typedef enum PointerTag{Link,Thread};

typedef struct BTnode{
    char data;
    struct BTnode* lchild;
    struct BTnode* rchild;
    PointerTag ltag,rtag;
}BTnod;

void createBTree(BTnode *&T){//创建二叉树 
    char ch;
    scanf("%c",&ch);
    if(ch=='#'){
        T=NULL;
    }
	else{
        T=(BTnode *)malloc(sizeof(BTnode));
        T->data=ch;
        T->ltag=Link;
        T->rtag=Link;
        createBTree(T->lchild);
        createBTree(T->rchild);
    }
}

void inThread(BTnode *&T,BTnode *&pre){//中序遍历线索化二叉树 
    if(T!=NULL){
        inThread(T->lchild,pre);
        if(T->lchild==NULL){
            T->lchild=pre;
            T->ltag=Thread;
        }
        if(pre!=NULL&&pre->rchild==NULL){
            pre->rchild=T;
            pre->rtag=Thread;
        }
        pre=T;
        inThread(T->rchild,pre);
    } 
} 

void createInThread(BTnode *T){//创建中序线索二叉树 
    BTnode *pre;
    pre=NULL;
    if(T!=NULL){
        inThread(T,pre);
        pre->rchild=NULL;
        pre->rtag=Thread;//处理最后一个结点信息 
    }
}

BTnode* firstNode(BTnode *p){//获取中序序列的第一个结点 
    while(p->ltag==Link){//若有左孩子 
        p=p->lchild;
    }
    return p;
} 

BTnode* nextNode(BTnode *p){//获得中序序列下T结点的后继结点 
    if(p->rtag==Link){//若有右孩子 
        return firstNode(p->rchild);
    }else{
        return p->rchild;
    }
}

void inOrderThread(BTnode *T){//遍历中序线索二叉树
     BTnode *p;
    for(p=firstNode(T);p!=NULL;p=nextNode(p)){
        printf("%c ",p->data);
    }
} 

int main(int argc, char** argv) {
    BTnode *T,*p;
    createBTree(T);//创建二叉树 
    createInThread(T);//创建中序线索二叉树 
    inOrderThread(T);//遍历中序线索二叉树 
    return 0;
}

