#include <iostream>
#include<stdlib.h>

typedef enum PointerTag{Link,Thread};

typedef struct BTnode{
    char data;
    struct BTnode* lchild;
    struct BTnode* rchild;
    PointerTag ltag,rtag;
}BTnod;

void createBTree(BTnode *&T){//���������� 
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

void inThread(BTnode *&T,BTnode *&pre){//������������������� 
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

void createInThread(BTnode *T){//������������������ 
    BTnode *pre;
    pre=NULL;
    if(T!=NULL){
        inThread(T,pre);
        pre->rchild=NULL;
        pre->rtag=Thread;//�������һ�������Ϣ 
    }
}

BTnode* firstNode(BTnode *p){//��ȡ�������еĵ�һ����� 
    while(p->ltag==Link){//�������� 
        p=p->lchild;
    }
    return p;
} 

BTnode* nextNode(BTnode *p){//�������������T���ĺ�̽�� 
    if(p->rtag==Link){//�����Һ��� 
        return firstNode(p->rchild);
    }else{
        return p->rchild;
    }
}

void inOrderThread(BTnode *T){//������������������
     BTnode *p;
    for(p=firstNode(T);p!=NULL;p=nextNode(p)){
        printf("%c ",p->data);
    }
} 

int main(int argc, char** argv) {
    BTnode *T,*p;
    createBTree(T);//���������� 
    createInThread(T);//������������������ 
    inOrderThread(T);//������������������ 
    return 0;
}

