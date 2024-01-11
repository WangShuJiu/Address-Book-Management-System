#include"stdio.h"
#include"stdlib.h"
#include"conio.h"
#include"dos.h"
#include"string.h"
#define LEN sizeof(struct addritem)
#define FORMAT "%-10s%-10s%-15s%-22s%-15s%"
#define DATA addrinfo[i].name, addrinfo[i].occu, addrinfo[i].tel, addrinfo[i].email, addrinfo[i].address

struct addritem
{
	char name[10];
	char occu[10];
	char tel[15];
	char address[30];
	char email[100];
};//定义一个结构体，记录姓名、职业、电话、地址、邮箱；都是以字符串的形式储存


struct addritem addrinfo[100];
void input();//声明函数，录入联系人的信息
void search();//查找联系人
void update();//修改联系人的信息
void del();//删除联系人的信息
void display();//展示联系人的信息
void sort();//排序



void Homepage()
{
	printf("				**********************CONTACT************************\n");
	printf("				**                                                 **\n");
	printf("				**                1.输入联系人信息                 **\n");
	printf("				**                                                 **\n");
	printf("				**                2.搜索联系人信息                 **\n");
	printf("				**                                                 **\n");
	printf("				**                3.修改联系人信息                 **\n");
	printf("				**                                                 **\n");
	printf("				**                4.删除目标联系人                 **\n");
	printf("				**                                                 **\n");
	printf("				**                5.整理排序联系人                 **\n");
	printf("				**                                                 **\n");
	printf("				**                6.展示所有联系人                 **\n");
	printf("				**                                                 **\n");
	printf("				**                0.返回                           **\n");
	printf("				**                                                 **\n");
	printf("				*****************************************************\n");
}




int main()
{
	int n;
	Homepage();
	printf("\t请输入你所需要的功能序号：");
	scanf_s("%d", &n);
	printf("\n");
	while (n) {
		switch (n)
		{
		case 1:input(); break;
		case 2:search(); break;
		case 3:update(); break;
		case 4:del(); break;
		case 5:sort(); break;
		case 6:display(); break;
		default:break;
		}
		Homepage();
		printf("\t请输入你所需要的功能序号：");
		scanf_s("%d", &n);
	}
	return 0;//switch函数选择你输出的序号，并进入该函数运行
}


void input()
{
	int i, count = 0;//count用于记录联系人的个数
	char ch[2];//记录Y/N
	FILE* fp;
	errno_t err = fopen_s(&fp, "data.txt", "a+");//这段代码的功能是以追加模式打开名为 "data.txt" 的文件，如果文件不存在则创建它，然后将文件指针保存在 fp 变量中。如果文件打开失败，则会将错误码存储在 err 变量中，并将 fp 设置为 NULL。
	if (err != 0)
	{
		printf("\t打开文件失败!\n");
		return;
	}

	while (!feof(fp))//记录条数
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	}
	fclose(fp);

	if (count == 0)
		printf("\t没有联系记录!\n");
	else
	{
		display();
	}
	errno_t err1 = fopen_s(&fp, "data.txt", "wb");
	if (err1 != 0)
	{
		printf("\t不能打开！");
		return;
	}

	for (i = 0; i < count; i++)
		fwrite(&addrinfo[i], LEN, 1, fp);

	printf("\t是否新添加联系人？（Y/N）:");
	scanf_s("%s", &ch, sizeof(ch));


	while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
	{
		printf("姓    名：");
		scanf_s("%s", addrinfo[count].name, _countof(addrinfo[count].name));
		for (i = 0; i < count; i++)
			if (strcmp(addrinfo[i].name, addrinfo[count].name) == 0)
			{
				printf("\t这个姓名已经存在，按任意键继续；\n\n");
				fclose(fp);
				return;
			}

		printf("职    业：");//职业 
		scanf_s("%s", addrinfo[count].occu, _countof(addrinfo[count].occu));


		printf("电话号码：");
		scanf_s("%s", addrinfo[count].tel, _countof(addrinfo[count].tel));


		printf("邮    箱：");
		scanf_s("%s", addrinfo[count].email, _countof(addrinfo[count].email));

		printf("家庭住址：");
		scanf_s("%s", addrinfo[count].address, _countof(addrinfo[count].address));

		//新录入的联系人信息写入磁盘文件中 
		if (fwrite(&addrinfo[count], LEN, 1, fp) != 1)
		{
			printf("\t新建联系人失败！\n");
		}
		else
		{
			printf("\t%s录入成功！\n", addrinfo[count].name);
			count++;
		}
		printf("\t是否继续新建联系人？(Y/N):");
		scanf_s("%s", &ch, sizeof(ch));
	}
	fclose(fp);
	printf("\t执行成功！\n");
	system("pause");
}




void search()
{
	FILE* fp;
	int i, count = 0, nm,li=0,count1=0;
	char ch[2], name[15],email[100];
	errno_t err = fopen_s(&fp, "data.txt", "a+");//这段代码的功能是以追加模式打开名为 "data.txt" 的文件，如果文件不存在则创建它，然后将文件指针保存在 fp 变量中。如果文件打开失败，则会将错误码存储在 err 变量中，并将 fp 设置为 NULL。
	if (err != 0)
	{
		printf("\t不能打开！\n");
		return;
	}
	while (!feof(fp))
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	}
	fclose(fp);
	if (count == 0)
	{
		printf("\t没有记录！\n");
		return;
	}
	printf("\t请输入的需要的查询方式：①姓名查询。②地址查询。③邮箱查询");
	scanf_s("%d", &nm);
	if (nm == 1)
	{
		printf("\t请输入姓名：");
		scanf_s("%s", &name, 15);
		for (i = 0; i < count; i++)
		{
			if (strcmp(name, addrinfo[i].name) == 0)
			{
				printf("\n\n");
				printf("姓名     职业       手机号码         邮箱                家庭住址\t\n");
				printf(FORMAT, DATA);
				printf("\n");
				count1++;
				break;
			}
			
		}
		if (count1 == 0) printf("\n没有该联系人！");
	}

	if (nm == 2)
	{
		printf("\t请输入家庭住址：");
		scanf_s("%s", &name, 15);
		for (i = 0; i < count; i++)
		{
			if (strcmp(name, addrinfo[i].address) == 0)
			{
				li++;
				if (li == 1)
				{
					printf("\n\n");
					printf("姓名     职业       手机号码         邮箱                家庭住址\t\n");
					printf(FORMAT, DATA);
					printf("\n");
				}
				else {
					printf(FORMAT, DATA);
					printf("\n");
				}
			}
		}
		if (li == 0) printf("\n没有该联系人！");
	}
	if (nm == 3)
	{
		printf("\t请输入邮箱：");
		scanf_s("%s", &email, 100);
		for (i = 0; i < count; i++)
		{
			if (strcmp(email, addrinfo[i].email) == 0)
			{
				li++;
				if (li == 1)
				{
					printf("\n\n");
					printf("姓名     职业       手机号码         邮箱                家庭住址\t\n");
					printf(FORMAT, DATA);
					printf("\n");
				}
				else {
					printf(FORMAT, DATA);
					printf("\n");
				}
			}
			
		}
		if (li == 0)
		{
			printf("\t没有找到给联系人！");
		}
		
	}
		
	printf("\n\n");
		system("pause");
}

	void update()
{
	FILE* fp;
	int i, j, count = 0;
	char name[15];//errno_t 是一种数据类型，通常用于表示函数返回的错误码。它是一个无符号整数类型，在标准 C 库中被定义为 typedef unsigned int errno_t;。
	errno_t err = fopen_s(&fp, "data.txt", "r+");//这段代码的功能是以读写模式打开名为 "data.txt" 的文件，如果文件不存在则失败，将错误码存储在 err 变量中，并将 fp 设置为 NULL。打开文件后，我们可以通过 fp 指针执行文件 I / O 操作，例如读取、写入文件等。由于文件以读写模式打开，我们可以在任何位置进行读写操作。如果文件不存在，则会返回一个错误码并设置 fp 为 NULL。
	if (err != 0)
	{
		printf("\t不能打开！\n");
		return;
	}
	while (!feof(fp))
		if (fread(&addrinfo[count], LEN, 1, fp))
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("\t没有记录！\n");
		fclose(fp);
		return;
	}
	display();
	printf("\t修改人的名字：");
	scanf_s("%s", &name, 15);
	for (i = 0; i < count; i++)
	{
		if (strcmp(name, addrinfo[i].name) == 0)
		{
			printf("找到联系人的信息！你可以修改！\n");
			printf("姓    名：");
			scanf_s("%s", addrinfo[i].name, _countof(addrinfo[i].name));
			printf("职    业：");//职业 
		scanf_s("%s", addrinfo[i].occu, _countof(addrinfo[i].occu));
			printf("电话号码：");
			scanf_s("%s", addrinfo[i].tel, _countof(addrinfo[i].tel));
			printf("邮    箱：");
			scanf_s("%s", addrinfo[i].email, _countof(addrinfo[i].email));
			printf("家庭住址：");
			scanf_s("%s", addrinfo[i].address, _countof(addrinfo[i].address));
			printf("修改成功！\n");

			errno_t err1 = fopen_s(&fp, "data.txt", "wb");
			if (err1 != 0)
			{
				printf("不能打开！\n");
				return;
			}

			for (j = 0; j < count; j++)
				if (fwrite(&addrinfo[j], LEN, 1, fp) != 1)
				{
					printf("\t没有成功保存\n");
				}
			fclose(fp);
			system("pause");
			return;
		}
		
	}
	printf("\t没有找到相关内容！\n");
	system("pause");
}

void del()
{
	FILE* fp;
	int i, j, count = 0;
	char ch[2];
	char name[15];
	errno_t err = fopen_s(&fp, "data.txt", "a+");//这段代码的功能是以追加模式打开名为 "data.txt" 的文件，如果文件不存在则创建它，然后将文件指针保存在 `fp` 变量中。如果文件打开失败，则会将错误码存储在 `err` 变量中，并将 `fp` 设置为 `NULL`。打开文件后，我们可以通过 `fp` 指针执行文件 I / O 操作，例如读取、写入文件等。由于文件以追加模式打开，因此在每次写入时都会将数据添加到文件末尾。如果文件不存在，则会创建一个新的空文件。
	if (err != 0)
	{
		printf("\t不能打开!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("\t没有记录！\n");
		return;
	}
	printf("\n");
	display();
	printf("\t请输入名字：");
	scanf_s("%s", &name, 15);
	for (i = 0; i < count; i++)
	{
		if (strcmp(name, addrinfo[i].name) == 0)
		{
			printf("\t已经找到该联系人！是否删除！（Y/N）:");
			scanf_s("%s", ch, sizeof(ch));
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				for (j = i; j < count; j++)
					addrinfo[j] = addrinfo[j + 1];
			count--;
			errno_t err = fopen_s(&fp, "data.txt", "wb");
			if (err != 0)
			{
				printf("\t不能打开!\n");
				return;
			}
			for (j = 0; j < count; j++)
				if (fwrite(&addrinfo[j], LEN, 1, fp) != 1)
				{
					printf("\t没有保存！\n");
				}
			fclose(fp);
			printf("成功删除！\n");
			return;
		}
	}
	printf("\t没有找到联系人!\n");
	system("pause");
}

void sort()
{
	FILE* fp;
	struct addritem temp;
	int i, j, count = 0;
    errno_t err = fopen_s(&fp, "data.txt", "r+");//这段代码的功能是以追加模式打开名为 "data.txt" 的文件，如果文件不存在则创建它，然后将文件指针保存在 `fp` 变量中。如果文件打开失败，则会将错误码存储在 `err` 变量中，并将 `fp` 设置为 `NULL`。打开文件后，我们可以通过 `fp` 指针执行文件 I / O 操作，例如读取、写入文件等。由于文件以追加模式打开，因此在每次写入时都会将数据添加到文件末尾。如果文件不存在，则会创建一个新的空文件。
	if (err != 0)
	{
		printf("不能打开！\n");
		return;
	}

	while (!feof(fp))//feof(fp) 是 C 语言标准库函数之一，用于检查文件指针当前位置是否已经到达文件末尾。
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);

	if (count == 0)
	{
		printf("没有记录！\n");
		return;
	}

	for (i = 0; i < count; i++)
	{
		for (j = i + 1; j < count; j++)
		{
			if (strcmp(addrinfo[i].name, addrinfo[j].name) > 0)
			{
				temp = addrinfo[i];
				addrinfo[i] = addrinfo[j];
				addrinfo[j] = temp;
			}
		}
	}

	errno_t err1 = fopen_s(&fp, "data.txt", "wb");
	if (err1 != 0)
	{
		printf("不能打开！\n");
		return;
	}
	for (i = 0; i < count; i++)
		if (fwrite(&addrinfo[i], LEN, 1, fp) != 1)//fwrite() 是 C 语言标准库函数之一，用于向文件中写入数据。fwrite() 函数会返回已经成功写入的数据块数量，因此对于这行代码的判断条件 fwrite(&addrinfo[i], LEN, 1, fp) != 1，如果它的返回值不等于 1，则表示写入失败或者未能完全写入目标数据，可以根据实际需求进行处理，例如输出错误信息或者抛出异常。
		{
			printf("\t写入失败！\n");
		}
	fclose(fp);
	printf("\t成功排序！\n");
	printf("\n");
	system("pause");
}


void display()
{
	FILE* fp;
	int i = 0, j = 0, count = 0;
	errno_t err = fopen_s(&fp, "data.txt", "rb");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			if (fread(&addrinfo[count], LEN, 1, fp) == 1)
				count++;

		}
	}

	if (count != 0)
	{
		printf("姓名     职业       手机号码         邮箱                家庭住址\t\n");
	}
	if(count==0) printf("\t没有联系人！\n");
	for (i = 0; i < count; i++)
	{
		printf(FORMAT, DATA);
		printf("\n");
	}
	printf("\n\n");
	fclose(fp);
	system("pause");
}