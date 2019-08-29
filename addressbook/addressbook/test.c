#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

//#define	PERSONS_MAX_SIZE	  200
#define	NAME_MAX_SIZE	  1024
#define	PHONE_MAX_SIZE	  100
/*通过结构体表示一个现实中事物的操作，称为“抽象”*/
typedef   struct PersonInfo
{
	char	   name[NAME_MAX_SIZE];
	char    phone[PHONE_MAX_SIZE];
}PersonInfo;

typedef   struct Addrbook
{
	PersonInfo* 	persons ;
	int	size;			//当前数组中有效元素的个数
	int  capacity;	//当前数组的最大容量
}Addrbook;

/*初始化*/
void  Init(Addrbook*	addr_book)
{
	//能够修改结构体的内容
	assert(addr_book	   !=	NULL);
	addr_book->size = 0;
	addr_book->capacity = 10;
	addr_book->persons = (PersonInfo*)malloc(sizeof(PersonInfo)  *   addr_book->capacity);

	for (int i = 0; i < addr_book->capacity; ++i)
	{
		memset(addr_book->persons[i].name, 0, NAME_MAX_SIZE);
		memset(addr_book->persons[i].phone, 0, PHONE_MAX_SIZE);
	}
}
//添加联系人
void  Add(Addrbook*	addr_book)
{
	assert(addr_book != NULL);
	printf("======新增联系人!======  \n");
	if (addr_book->size  >=	addr_book->capacity)
	{
		 //扩容
		addr_book->capacity += 10;
		addr_book->persons = (PersonInfo*)realloc(addr_book->persons,addr_book->capacity);
	}
	PersonInfo*	p = &addr_book->persons[addr_book->size];
	printf("请输入联系人的姓名： \n");
	char	name[NAME_MAX_SIZE] = {0};
	scanf("%s",p->name);
	printf("请输入联系人的电话：  \n");
	scanf("%s", p->phone);
	++addr_book ->size;
}
//删除联系人
void  Remove(Addrbook*	addr_book)
{
	assert(addr_book != NULL);
	printf("======删除通讯录中的元素！====== \n");
	if (addr_book->size == 0)
	{
		printf("当前通讯录为空，无法删除！\n");
		return;
	}
	printf("请输入要删除元素的序号：\n");
	int  index = 0;
	scanf("%d", &index);
	if (index < 0 || index >= addr_book->size)
	{
		printf("您输入的序号有误！[0-%d]  \n", addr_book->size - 1);
		return;
	}
	//具体删除

	if (index==addr_book->size-1)
	{
		//1.删除最后一个元素
		--addr_book->size;
	}
	else
	{
		//2.删除中间元素，先把最后一个元素写到要删除的位置上，再删除最后一个元素
		PersonInfo*  mid = &addr_book->persons[index];
		PersonInfo*  last = &addr_book->persons[addr_book->size-1];
		strcpy(mid->name,	last->name);
		strcpy(mid->phone, last->phone);
		--addr_book->size;
	}
	printf("删除成功！当前还剩  %d	条记录！\n",addr_book->size);
}
//查找联系人
void  PrintAll(Addrbook*	addr_book)
{
	assert(addr_book != NULL);
	printf("=====================\n");
	for (int i = 0; i < addr_book->size; ++i)
	{
		PersonInfo*  p = &addr_book->persons[i];
		printf("[%d]  %s:	%s\n",	i,	p->name,		p->phone);
	}
	printf("当前共有 %d	条记录！\n",	addr_book->size);
	printf("=====================\n");
}
//更新联系人
void  Update(Addrbook*	addr_book)
{
	assert(addr_book != NULL);
	printf("======更新联系人的电话!======  \n");
	if (addr_book	->	size	==	0)
	{
		printf("当前通讯录为空，无法修改！\n");
		return;
	}
	printf("请输入您要修改的联系人记录的序号：  \n");
	int  index = 0;
	scanf("%d",&index);
	if (index < 0		||	index	>=addr_book->size)
	{
		printf("您输入的序号有误！[0-%d]  \n",addr_book->size-1);
		return;
	}
	PersonInfo*   p = &addr_book->persons[index];
	printf("当前姓名为：%s \n请输入修改之后的姓名（*表示该字段不修改）：",	p->name);
	char  name[NAME_MAX_SIZE] = {0};
	scanf("%s",name);
	if (strcmp(name,"*")!=0)
	{
		strcpy(p->name,name);
	}
	printf("当前电话为：%s \n请输入修改之后的电话（*表示该字段不修改）：",	p->phone);
	char  phone[PHONE_MAX_SIZE] = { 0 };
	scanf("%s", phone);
	if (strcmp(phone, "*") != 0)
	{
		strcpy(p->phone, phone);
	}
	printf("修改完成\n");
}

int  Menu()
{
	printf("=====================\n");
	printf("欢迎使用通讯录程序！\n");
	printf("1.显示所有联系人信息   \n");
	printf("2.新增联系人信息    \n");
	printf("3.修改联系人信息   \n");
	printf("4.删除联系人信息   \n");
	printf("0.退出使用通讯录程序！   \n");
	printf("=====================\n");
	printf("请输入您的选择：");
	int choice = 0;
	scanf("%d",&choice);
	return  choice;
}

Addrbook	addr_book;

//函数指针
typedef	void(*Func)(Addrbook*);

int  main()
{
	//初始化
	Init(&addr_book);
	//函数指针数组
	Func		func_table[] = {
		NULL,
		PrintAll,
		Add,
		Update,
		Remove
	};
	while (1)
	 {
		int  choice = Menu();
		if (choice	<	0 || choice	>	4)
		{
			printf("您的输入有误，请重新输入！\n");
			continue;
		}
		if (choice == 0)
		{
			printf("goodbye!	\n");
			break;
		}
		//清屏
		system("cls");
		//调用转移表里面的函数
		func_table[choice](&addr_book);
	}
	return 0;
}