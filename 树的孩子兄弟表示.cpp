#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
#define OVERFLOW -2

typedef int Status;
typedef char ElemType; //结点的值设置为字符

typedef struct CSNode
{
	ElemType data;
	struct CSNode *firstChild;  //第一个孩子
	struct CSNode *nextsbling;   //该孩子的第一个兄弟
}CSNode, *CSTree;
 
 
/*------------程序中用到的队列------------------------------*/
 
typedef CSTree QElemType;//队中的元素
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;
 
typedef struct  
{
	QueuePtr front;  //队头指针
	QueuePtr rear;  //队尾指针
}LinkQueue;
 
Status InitQueue(LinkQueue &Q)//构造一个空队列
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));//队头结点
	if(!Q.front)
		exit(OVERFLOW);
	Q.front ->next = NULL;
	return OK;
}
 
Status QueueEmpty(const LinkQueue &Q)//若队列为空，则返回TRUE，否则返回FALSE
{
	if(Q.rear == Q.front)
		return TRUE;
	return FALSE;
}
 
Status EnQueue(LinkQueue &Q, QElemType e) //插入元素e为Q的新队尾元素
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}
 
Status DeQueue(LinkQueue &Q,QElemType &e) //若队列不空，则删除Q的队头元素，用e返回其值，并返回OK;
{
	if(Q.front == Q.rear)
	{
		return ERROR; //队空
	}
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return OK;
}
 
/*--------------------------------------------------------------*/
 
 
/*-----------------树的实现代码---------------------------------*/

Status CreateTree(CSTree &T){  
	//创建一棵树
	LinkQueue Q;
	InitQueue(Q);//构造一个空队列
	
	char buffChild[10];  //用于存放孩子们的缓存
	memset(buffChild,0,10); //初始化缓存数组，置为NULL
	
	printf("请输入树的根结点（字符,以#代表空）:\n");
	fflush(stdin);
	
	scanf("%c",&buffChild[0]);
	if(buffChild[0] != '#')
	{
		T = (CSTree)malloc(sizeof(CSNode));//为根结点开辟一个空间
		if(!T)
			exit(OVERFLOW);  //开辟失败，终止程序
		
		T->data = buffChild[0];
		T->nextsbling = NULL;  //根结点无兄弟
		
		EnQueue(Q,T);  //根结点入队
		while(!QueueEmpty(Q))
		{
			QElemType e;
			DeQueue(Q,e); //结点出队
			printf("请按长幼顺序输入结点%c的孩子(字符,以#结束):\n",e->data);
			fflush(stdin);  //清空输入流缓冲区的数据
			gets(buffChild);
			
			if(buffChild[0] != '#'){
				//有孩子
				CSTree q;
				q = (CSTree)malloc(sizeof(CSNode));  //开辟孩子结点空间
				if(!q)
					exit(OVERFLOW);
				
				q->data = buffChild[0];
				e->firstChild = q;  //指向第一个孩子
				
				EnQueue(Q,q);  //第一个孩子入队
				CSTree p = q;  //指向刚入队的孩子
				for(int i = 1; i < strlen(buffChild)-1; ++i) //孩子存在兄弟
				{
					q = (CSTree)malloc(sizeof(CSNode));  //开辟孩子结点空间
					if(!q)
						exit(OVERFLOW);
						
					q->data = buffChild[i];
					p->nextsbling = q;
					EnQueue(Q,q);  
					p = q;  //指向刚入队的孩子
				}
				p->nextsbling = NULL;
			}
			else//无孩子
				e->firstChild = NULL;
		}	
	}
	else
		T = NULL;//空树
	return OK;
 
 
}
 
Status DestroyTree(CSTree &T){
	//树T存在，销毁树T
	if(T)//树不空
	{
		if(T->firstChild)//左子树存在，即销毁以长子为结点的子树
			DestroyTree(T->firstChild);
		if(T->nextsbling)//右子树存在，即销毁以兄弟为结点的子树
			DestroyTree(T->nextsbling);
		free(T); //释放根结点
		T = NULL;
		return OK;
	}
	else{
		return ERROR;
	}
	
}
 
int TreeDepth(const CSTree &T){
	//树T存在，返回树的深度
	if(!T)//树空
		return 0;
	if(!T->firstChild)//无长子
		return 1;
	CSTree p;
	int depth,max = 0;
	for(p=T->firstChild; p; )
	{
		depth = TreeDepth(p);
		if(depth > max)
			max = depth;
		p= p->nextsbling;
	}
	return max+1;//当前层的下一层
}
 
ElemType Root(const CSTree &T){
	//树T存在，返回树的根
	if(T)
		return T->data;
	return 0;
}
 
CSNode* FindNode(const CSTree &T,ElemType cur_e){
	//树T存在，返回值为cur_e的结点的指针
	LinkQueue Q;
	InitQueue(Q);  //构造一个空队列
	if(T)
	{
		EnQueue(Q,T);//树根入队
		while(!QueueEmpty(Q))
		{
			QElemType e;
			DeQueue(Q,e);
			if(e->data == cur_e)
				return e;
			if(e->firstChild) //当前结点有长子，则该长子入队
			{
				EnQueue(Q,e->firstChild);
			}
			if(e->nextsbling)//当前结点有兄弟,则该兄弟入队
			{
				EnQueue(Q,e->nextsbling);
			}
		}
	}
	return NULL;
}
 
Status Assign(CSTree &T, ElemType cur_e, ElemType value){
	//树T存在，cur_e是树中存在的结点，操作结果：把value的值赋给cur_e的结点
	if(!T)//树空
		return ERROR;
	CSNode *node_cur_e = FindNode(T,cur_e);//查找值为cur_e的结点，并尝试获取他的地址
	if(!node_cur_e) //获取失败，返回出错信息
		return ERROR;
	node_cur_e->data = value;
	return OK;
 
}
 
CSNode * Parent(CSTree &T,ElemType cur_e){
	//初始条件：树T存在，cur_e是T中某个结点
	//操作结果：若cur_e是T的非根结点，则返回它的双亲，否则返回空
	LinkQueue Q;
	InitQueue(Q);
	if(T)
	{
		if(T->data == cur_e)
			return NULL;//根结点无双亲,结束，返回NULL
		
		EnQueue(Q,T);//根结点入队
		while(!QueueEmpty(Q))
		{
			QElemType e;
			DeQueue(Q,e);
			QElemType p = e;//提示刚出队的元素；
			if(e->firstChild)//该结点有孩子
			{
				if(e->firstChild->data == cur_e)//或该孩子是所求的结点，则返回双亲
				{
					return p;
				}
				EnQueue(Q,e->firstChild);
				QElemType brotherPtr = e->firstChild->nextsbling;//指向孩子的兄弟结点
				while(brotherPtr) //该孩子有兄弟
				{
					if(brotherPtr->data == cur_e)//兄弟是所求的结点，则返回双亲
					{
						return p;
					}
					EnQueue(Q,brotherPtr);//兄弟入队
					brotherPtr = brotherPtr->nextsbling;
				}
			}
		}
	}
	return NULL;
}
 
ElemType LeftChild(CSTree &T, ElemType cur_e)
{
	//初始条件：树T存在，cur_e是T中某个结点
	//操作结果：若cur_e是T的非叶子结点，则返回它的最左孩子，否则返回空
	CSNode *node;
	node = FindNode(T,cur_e);
	if(node)
	{
		if(node->firstChild)//非叶子结点
		{
			return node->firstChild->data; //返回结点的值
		}
	}
	return 0;
}
 
ElemType RightSibling(CSTree &T, ElemType cur_e)
{
	//初始条件：树T存在，cur_e是T中的某个结点。
	//操作结果：若cur_e有右兄弟，则返回它的右兄弟，否则返回空
	CSNode *node;
	node = FindNode(T,cur_e);
	if(node)
	{
		if(node->nextsbling)//有右兄弟
		{
			return node->nextsbling->data;//返回右兄弟的值
		}
		
	}
	return 0;
}
 
Status LevelOrderTraverse(const CSTree &T)
{
	//层序遍历树
	LinkQueue Q;
	InitQueue(Q);
	if(T)
	{
		printf("%c",T->data);//访问结点
		EnQueue(Q,T);//根结点排队
		while(!QueueEmpty(Q))
		{
			QElemType e,p;
			DeQueue(Q,e);
			p = e->firstChild;
			while(p)
			{
				printf("%c",p->data);
				EnQueue(Q,p);
				p = p->nextsbling;
			}
		}
		return OK;
	}
	return ERROR;//空树
}
/*-------------------------------------------------------*/

void Menu(void)
{
	printf("\t\t             ========================        \n");
	printf("\t\t            |                       |        \n");
	printf("\t\t   |--------|     各种树的操作      |-------|\n");
	printf("\t\t   |        |       孩子兄弟        |       |\n");
	printf("\t\t            |                       |        \n");
	printf("\t\t   |         ========================       |\n");
	printf("\t\t   |                                        |\n");
	printf("\t\t   |            请选择你的操作排序：        |\n");
	printf("\t\t   |            [1]树的创建                 |\n");
	printf("\t\t   |            [2]树的深度                 |\n");
	printf("\t\t   |            [3]树的层次遍历             |\n");
	printf("\t\t   |            [4]查找结点                 |\n");
	printf("\t\t   |            [5]查找结点的双亲           |\n");
	printf("\t\t   |            [6]查找结点的左孩子         |\n");
	printf("\t\t   |            [7]查找结点的右兄弟         |\n");
	printf("\t\t   |            [8]更改某个结点的值         |\n");
	printf("\t\t   |            [9]树的根结点               |\n");
	printf("\t\t   |            [10]树的销毁                |\n");
	printf("\t\t   |            [11]退出                    |\n");
	printf("\t\t   |-======================================-|\n");
	printf("\t\t   |                 欢迎修改               |\n");
	printf("\t\t   |-======================================-|\n");
	printf("请选择你要进行的操作(1/2/3/4/5/6/7/8/9/10/11):");
}
 
int main(int argc,char **argv){
	Menu();
	CSTree T,node;
	int i;
	ElemType e,d;
	
	scanf("%d",&i);
	while(i!=11){
		switch(i){
			case 1:
				if(CreateTree(T))
					printf("创建成功！\n"); 
				else
					printf("创建失败!\n");
				Menu();
				break;
			case 2:
				if(TreeDepth(T)) 
					printf("树的深度为：%d\n",TreeDepth(T));
				else
					printf("该树为空\n"); 
				Menu();
				break;
			case 3:
				printf("按层序遍历该树：");
				if(LevelOrderTraverse(T)) 
					printf("\n");
				else
					printf(">>>无法遍历,该树为空!\n"); 	
				Menu();
				break;	
			case 4:
				printf("请输入要查询的结点:");
				fflush(stdin);
				scanf("%c",&e);
				if(FindNode(T,e))
					printf("存在结点%c\n",FindNode(T,e)->data);
				else
					printf("该结点不存在!\n");
				Menu();
				break;	
			case 5:
				printf("请输入要查询的结点:");
				fflush(stdin);
				scanf("%c",&e);
				if(FindNode(T,e)){ 
					if(Parent(T,e))
						printf("结点%c的双亲是%c\n",e,Parent(T,e)->data);
					else
						printf("该结点没有双亲!\n");	
				} 
				else
					printf("该结点不存在!\n");
				Menu();
				break;	
			case 6:
				printf("请输入要查询的结点:");
				fflush(stdin);
				scanf("%c",&e);
				if(FindNode(T,e)){
					if(LeftChild(T,e)) 
						printf("%c的左孩子是%c\n",e,LeftChild(T,e));
					else
						printf("该结点没有左孩子!\n");
				}
				else
					printf("该结点不存在!\n");
				 
				Menu();
				break;	
			case 7:
				printf("请输入要查询的结点:");
				fflush(stdin);
				scanf("%c",&e);
				if(FindNode(T,e)){
					if(RightSibling(T,e)) 
						printf("%c的右兄弟是%c\n",e,RightSibling(T,e));
					else
						printf("该结点没有右兄弟!\n");
				}
				else
					printf("该结点不存在!\n");
				Menu();
				break;	
			case 8:
				printf("请输入要更改的结点:");
				fflush(stdin);
				scanf("%c",&e);
				if(FindNode(T,e)){
					printf("请输入要改成的结点:");
					fflush(stdin);
					scanf("%c",&d); 
					if(Assign(T,e,d))
						printf("更改成功\n");
					else
						printf("该树为空\n"); 
				} 
				else
					printf("此结点不存在!\n"); 
				Menu();
				break;	
			case 9:
				if(Root(T))
					printf("树的根为%c\n",Root(T));
				else
					printf("该树为空,没有根结点!\n"); 
				Menu();
				break;
			case 10:
				if(DestroyTree(T))
					printf("销毁成功!\n");
				else
					printf("该树为空!\n");
				Menu();
				break;	
			default:
				printf("输入有误,请重新输入!\n");
				Menu();
				break;		
		}
		scanf("%d",&i);
	} 	
	return 0;
}



