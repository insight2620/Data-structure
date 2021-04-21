#define _CRT_SECURE_NO_DEPRECATE //必须放在第一行，作用是让scanf和printf直接可用
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>


//结构体定义
typedef struct BSTree
{
	long long num; //学号
	char name[20];
	char sex[5];//性别(二值)
	int age;//年龄(非负)
	char major[30];
	struct BSTree *lchild, *rchild;
}BSTree;

//函数声明
int Get_int(void);//获取整数
long long Get_int1(void);//获取longlong整数,保证学号长度

BSTree *InsertBSTree(BSTree *T);//插入操作主函数
BSTree *FindBSTreeinsert(long long num, BSTree *T, int *flag);//插入操作一级子函数

int EditBSTree(BSTree *T);//编辑操作主函数

BSTree *DeleteBSTree(BSTree *T);//删除操作主函数
BSTree *DelBSTree(long long num,BSTree *T,int *flag);//删除操作一级子函数
BSTree *Del(BSTree *T);//删除操作二级子函数

int SearchBSTree(BSTree *T);//查找操作主函数
BSTree *FindBSTreeequal(long long num, BSTree *T, int *flag);//查找操作一级子函数

int PrintBSTree(BSTree *T);//输出操作主函数
int Print(BSTree *T);//输出操作一级子函数

int main( )
{	int flag = 0, m = 0;

	//结构体初始化
	BSTree *T = 0;
	while(!(T=(BSTree *)malloc(sizeof(BSTree))))
	continue;
	T->num = 0;
	strcpy_s(T->name, "空");
	strcpy_s(T->sex, "空");
	T->age = 0;
	strcpy_s(T->major, "空");
	T->lchild = T->rchild = 0;

	//主界面
	printf(" ---------------------------------------------------------\n");
	printf(" |************** 欢迎使用学生信息管理系统 ***************|\n");
	printf(" |*******每个学生信息包括：学号,姓名,性别,年龄,专业******|\n");
	printf(" ---------------------------------------------------------\n");
	do
	{	printf("\n1,插入 | 2,编辑 | 3,删除 | 4,查找(按学号)| 5,排序输出(按学号) | 0,退出\n操作=");
		scanf("%d", &flag); //测试scanf是否直接可用
		switch(flag)
		{	 case 1: T = InsertBSTree(T); PrintBSTree(T); break;
			 case 2: EditBSTree(T); PrintBSTree(T); break;
			 case 3: T=DeleteBSTree(T); PrintBSTree(T);break;
			 case 4: SearchBSTree(T); break;
			 case 5: PrintBSTree(T);break;
			 case 0: break;
			 default : printf("\n*********对不起，选择无效！*********\n");
		}
	}while(flag);

	printf("\n谢谢使用，按任意键继续\n");
	getchar();
}

BSTree *InsertBSTree(BSTree *T)//插入操作主函数
{
	BSTree *S = 0, *t = 0;
	int flag = 0;
	while (!(t = (BSTree *)malloc(sizeof(BSTree))))
		continue;
	printf("请输入学号\n学号:");
	t->num = Get_int1();
	if (t->num < 0)
	{
		printf("\n插入失败!!!,学号不能小于0!!!");
		return 0;
	}
	printf("请输入名字\n名字:");
	gets_s(t->name);
	printf("请选择性别：1.男  2.女\n性别:");
	flag= Get_int();
	while (flag != 1 && flag != 2)
	{ printf("选择无效！请重新输入："); flag = Get_int();}
	if (flag == 1) strcpy_s(t->sex, "男");
	else if (flag == 2) strcpy_s(t->sex, "女");
	printf("请输入年龄\n年龄:");
	t->age = Get_int();
	while (t->age < 0)
	{   printf("年龄不能为负数！请重新输入:");
		t->age = Get_int();  }
	printf("请输入专业\n专业:");
	gets_s(t->major);
	t->lchild = t->rchild = 0;

	if (T->num == 0)
	{
		T = t;
		//PrintBSTree(t);
		return T;
	}
	else
	{
		S = FindBSTreeinsert(t->num, T, &flag);
		if (flag == 1)
			S->lchild = t;
		else if (flag == 3)
			S->rchild = t;
		else printf("\n插入失败！可能插入的学生信息已经存在\n");
	}
	//PrintBSTree(t);
	return T;
	}

BSTree *FindBSTreeinsert(long long number,BSTree *T,int *flag)//插入操作一级子函数
{
	if(T)
	{
	 if(number<T->num&&!T->lchild)
	 { *flag=1;
	   return T;
	 }
	else if(number<T->num&&T->lchild)
	 FindBSTreeinsert(number,T->lchild,flag);
	else if(number>T->num&&!T->rchild)
	 { *flag=3;
	   return T;
	 }
	else if(number>T->num&&T->rchild)
	 FindBSTreeinsert(number,T->rchild,flag);
	}
}

int EditBSTree(BSTree *T)//编辑操作主函数
{
	BSTree *S = 0, *t = 0;
	int flag = 0;
	long long number = 0;
	if (!T)
	{
		printf("\n**********对不起，没有数据能够编辑，请首先输入！***********\n");
		return 0;
	}
	printf("请输入要编辑学生的学号：\n学号:");
	number = Get_int1();
	S = FindBSTreeequal(number, T, &flag);
	if (flag == 2)
	{
		printf("\n********************** 学号是%lld的学生的信息如下：*********************\n", number);
		printf("\n学号%lld 姓名%s 性别%s 年龄%d 专业%s\n", S->num, S->name, S->sex, S->age, S->major);
		printf("\n************************************************************************\n");
		printf("\n请输入名字\n名字:");
		gets_s(S->name);
		printf("请选择性别：1.男  2.女\n性别:");
		flag = Get_int();
		while (flag != 1 && flag != 2)
		{
			printf("选择无效！请重新输入："); flag = Get_int();
		}
		if (flag == 1) strcpy_s(S->sex, "男");
		else if (flag == 2) strcpy_s(S->sex, "女");
		printf("请输入年龄\n年龄:");
		S->age = Get_int();
		printf("请输入专业\n专业:");
		gets_s(S->major);
		return 1;
	}
	else
	{
		printf("***********对不起，没有学号是%lld的学生************", number);
		printf("\n你想插入他的信息吗？（1，添加，0不添加）\n选择:");
		flag = Get_int();
		if (flag)
		{
			T = InsertBSTree(T);
			return 1;
		}
		else return 0;
	}
}

BSTree *DeleteBSTree(BSTree *T) //删除操作主函数
{ 
	int flag=0;
	long long number;
	BSTree *S=0;
	printf("请输入要删除学生的学号：\n学号:");
	number=Get_int1();
	S=DelBSTree(number,T,&flag);
	if(flag==0)
	printf("\n*******删除失败，没有学号是%lld的学生的信息********\n",number);
	return S;
}

BSTree *DelBSTree(long long number, BSTree *T, int *flag)//删除操作一级子函数
{ 
	int m;
	if(!T)
	*flag=0;
	else if(number==T->num)
	{ 
		printf("********学号为%lld学生的信息如下，确认要删除吗？********\n",number);
		printf("\n学号=%lld, 姓名=%s, 性别=%s,年龄=%d, 专业=%s, \n",T->num,T->name,T->sex,T->age,T->major);
		printf("\n******************************************************\n");
		printf("\n确认要删除吗？\n 1，删除 || 0，取消删除\n选择:");
		m=Get_int();
		if(m==0)
		{ *flag=1;
		 return T;
		}
		T=Del(T);
		*flag=1;
	}
	else if(number<T->num)
	T->lchild=DelBSTree(number,T->lchild,flag);
	else T->rchild=DelBSTree(number,T->rchild,flag);
	return T;
}

BSTree *Del(BSTree *T) //删除操作二级子函数
{ 
	BSTree *S=0,*Q;
	if(T->lchild)
	{ S=T->lchild;
	 while(S->rchild)
	S=S->rchild;
	S->rchild=T->rchild;
	Q=T->lchild;
	free(T);
	return Q;
	}
	else
	{ Q=T->rchild;
	 free(T);
	return Q;
	}
}

int SearchBSTree(BSTree *T)//查找操作主函数
{ 
	long long number;
	int flag = 0;
	BSTree *S=0;
	printf("请输入要查找学生的学号\n学号=");
	number=Get_int1();
	S=FindBSTreeequal(number,T,&flag);
	if(flag==2)
	{ printf("\n***************学号是%lld的学生的信息如下：*****************\n",number);
	  printf("\n学号=%lld\t姓名=%s\t性别=%s\t年龄=%d\t专业=%s\t\n",S->num,S->name,S->sex,S->age ,S->major);
	  printf("\n**********************************************************\n");
	  return 1;
	}
	printf("\n******查找失败，没有 学号=%d 学生的信息*******\n",number);
	return 0;
}

BSTree *FindBSTreeequal(long long number, BSTree *T, int *flag)//查找操作一级子函数
{
	if (T)
	{
		if (number == T->num)
		{
			*flag = 2;
			return T;
		}
		else if (number < T->num&&T->lchild)
			FindBSTreeequal(number, T->lchild, flag);
		else if (number > T->num&&T->rchild)
			FindBSTreeequal(number, T->rchild, flag);
	}
}

int PrintBSTree(BSTree *T)//输出操作主函数
{ 
	if(!T)
	{ printf("\n***********************没有学生信息*************************\n");
	return 0;
	}
	printf("\n***************************学生信息如下：***************************\n");
	Print(T);
	printf("\n********************************************************************\n");
	return 1;
}

int Print(BSTree *T)//输出操作一级子函数
{
	if(T)
	{ Print(T->lchild);
	  printf("\n学号=%lld\t姓名=%s\t性别=%s\t年龄=%d\t专业=%s\t",T->num,T->name,T->sex,T->age ,T->major);
	  Print(T->rchild);
	  return 1;
	}
	return 0;
}

int Get_int(void)//获取整数
{ 
	int m=0;
	while(scanf_s("%d",&m)!=1)//若用户输入非整数则提醒
	{	 while(getchar()!='\n')
		 continue;
		 printf("\n请输入一个整数!\n输入:");
	}
	while(getchar()!='\n')
	continue;
	return m;
}

long long Get_int1(void)//获取longlong整数,保证学号长度
{
	long long m = 0;
	while (scanf_s("%lld", &m) != 1)//若用户输入非整数则提醒
	{
		while (getchar() != '\n')
			continue;
		printf("\n请输入一个整数!\n输入:");
	}
	while (getchar() != '\n')
		continue;
	return m;
}