#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

//#define	PERSONS_MAX_SIZE	  200
#define	NAME_MAX_SIZE	  1024
#define	PHONE_MAX_SIZE	  100
/*ͨ���ṹ���ʾһ����ʵ������Ĳ�������Ϊ������*/
typedef   struct PersonInfo
{
	char	   name[NAME_MAX_SIZE];
	char    phone[PHONE_MAX_SIZE];
}PersonInfo;

typedef   struct Addrbook
{
	PersonInfo* 	persons ;
	int	size;			//��ǰ��������ЧԪ�صĸ���
	int  capacity;	//��ǰ������������
}Addrbook;

/*��ʼ��*/
void  Init(Addrbook*	addr_book)
{
	//�ܹ��޸Ľṹ�������
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
//�����ϵ��
void  Add(Addrbook*	addr_book)
{
	assert(addr_book != NULL);
	printf("======������ϵ��!======  \n");
	if (addr_book->size  >=	addr_book->capacity)
	{
		 //����
		addr_book->capacity += 10;
		addr_book->persons = (PersonInfo*)realloc(addr_book->persons,addr_book->capacity);
	}
	PersonInfo*	p = &addr_book->persons[addr_book->size];
	printf("��������ϵ�˵������� \n");
	char	name[NAME_MAX_SIZE] = {0};
	scanf("%s",p->name);
	printf("��������ϵ�˵ĵ绰��  \n");
	scanf("%s", p->phone);
	++addr_book ->size;
}
//ɾ����ϵ��
void  Remove(Addrbook*	addr_book)
{
	assert(addr_book != NULL);
	printf("======ɾ��ͨѶ¼�е�Ԫ�أ�====== \n");
	if (addr_book->size == 0)
	{
		printf("��ǰͨѶ¼Ϊ�գ��޷�ɾ����\n");
		return;
	}
	printf("������Ҫɾ��Ԫ�ص���ţ�\n");
	int  index = 0;
	scanf("%d", &index);
	if (index < 0 || index >= addr_book->size)
	{
		printf("��������������[0-%d]  \n", addr_book->size - 1);
		return;
	}
	//����ɾ��

	if (index==addr_book->size-1)
	{
		//1.ɾ�����һ��Ԫ��
		--addr_book->size;
	}
	else
	{
		//2.ɾ���м�Ԫ�أ��Ȱ����һ��Ԫ��д��Ҫɾ����λ���ϣ���ɾ�����һ��Ԫ��
		PersonInfo*  mid = &addr_book->persons[index];
		PersonInfo*  last = &addr_book->persons[addr_book->size-1];
		strcpy(mid->name,	last->name);
		strcpy(mid->phone, last->phone);
		--addr_book->size;
	}
	printf("ɾ���ɹ�����ǰ��ʣ  %d	����¼��\n",addr_book->size);
}
//������ϵ��
void  PrintAll(Addrbook*	addr_book)
{
	assert(addr_book != NULL);
	printf("=====================\n");
	for (int i = 0; i < addr_book->size; ++i)
	{
		PersonInfo*  p = &addr_book->persons[i];
		printf("[%d]  %s:	%s\n",	i,	p->name,		p->phone);
	}
	printf("��ǰ���� %d	����¼��\n",	addr_book->size);
	printf("=====================\n");
}
//������ϵ��
void  Update(Addrbook*	addr_book)
{
	assert(addr_book != NULL);
	printf("======������ϵ�˵ĵ绰!======  \n");
	if (addr_book	->	size	==	0)
	{
		printf("��ǰͨѶ¼Ϊ�գ��޷��޸ģ�\n");
		return;
	}
	printf("��������Ҫ�޸ĵ���ϵ�˼�¼����ţ�  \n");
	int  index = 0;
	scanf("%d",&index);
	if (index < 0		||	index	>=addr_book->size)
	{
		printf("��������������[0-%d]  \n",addr_book->size-1);
		return;
	}
	PersonInfo*   p = &addr_book->persons[index];
	printf("��ǰ����Ϊ��%s \n�������޸�֮���������*��ʾ���ֶβ��޸ģ���",	p->name);
	char  name[NAME_MAX_SIZE] = {0};
	scanf("%s",name);
	if (strcmp(name,"*")!=0)
	{
		strcpy(p->name,name);
	}
	printf("��ǰ�绰Ϊ��%s \n�������޸�֮��ĵ绰��*��ʾ���ֶβ��޸ģ���",	p->phone);
	char  phone[PHONE_MAX_SIZE] = { 0 };
	scanf("%s", phone);
	if (strcmp(phone, "*") != 0)
	{
		strcpy(p->phone, phone);
	}
	printf("�޸����\n");
}

int  Menu()
{
	printf("=====================\n");
	printf("��ӭʹ��ͨѶ¼����\n");
	printf("1.��ʾ������ϵ����Ϣ   \n");
	printf("2.������ϵ����Ϣ    \n");
	printf("3.�޸���ϵ����Ϣ   \n");
	printf("4.ɾ����ϵ����Ϣ   \n");
	printf("0.�˳�ʹ��ͨѶ¼����   \n");
	printf("=====================\n");
	printf("����������ѡ��");
	int choice = 0;
	scanf("%d",&choice);
	return  choice;
}

Addrbook	addr_book;

//����ָ��
typedef	void(*Func)(Addrbook*);

int  main()
{
	//��ʼ��
	Init(&addr_book);
	//����ָ������
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
			printf("���������������������룡\n");
			continue;
		}
		if (choice == 0)
		{
			printf("goodbye!	\n");
			break;
		}
		//����
		system("cls");
		//����ת�Ʊ�����ĺ���
		func_table[choice](&addr_book);
	}
	return 0;
}