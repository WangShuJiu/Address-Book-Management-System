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
};//����һ���ṹ�壬��¼������ְҵ���绰����ַ�����䣻�������ַ�������ʽ����


struct addritem addrinfo[100];
void input();//����������¼����ϵ�˵���Ϣ
void search();//������ϵ��
void update();//�޸���ϵ�˵���Ϣ
void del();//ɾ����ϵ�˵���Ϣ
void display();//չʾ��ϵ�˵���Ϣ
void sort();//����



void Homepage()
{
	printf("				**********************CONTACT************************\n");
	printf("				**                                                 **\n");
	printf("				**                1.������ϵ����Ϣ                 **\n");
	printf("				**                                                 **\n");
	printf("				**                2.������ϵ����Ϣ                 **\n");
	printf("				**                                                 **\n");
	printf("				**                3.�޸���ϵ����Ϣ                 **\n");
	printf("				**                                                 **\n");
	printf("				**                4.ɾ��Ŀ����ϵ��                 **\n");
	printf("				**                                                 **\n");
	printf("				**                5.����������ϵ��                 **\n");
	printf("				**                                                 **\n");
	printf("				**                6.չʾ������ϵ��                 **\n");
	printf("				**                                                 **\n");
	printf("				**                0.����                           **\n");
	printf("				**                                                 **\n");
	printf("				*****************************************************\n");
}




int main()
{
	int n;
	Homepage();
	printf("\t������������Ҫ�Ĺ�����ţ�");
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
		printf("\t������������Ҫ�Ĺ�����ţ�");
		scanf_s("%d", &n);
	}
	return 0;//switch����ѡ�����������ţ�������ú�������
}


void input()
{
	int i, count = 0;//count���ڼ�¼��ϵ�˵ĸ���
	char ch[2];//��¼Y/N
	FILE* fp;
	errno_t err = fopen_s(&fp, "data.txt", "a+");//��δ���Ĺ�������׷��ģʽ����Ϊ "data.txt" ���ļ�������ļ��������򴴽�����Ȼ���ļ�ָ�뱣���� fp �����С�����ļ���ʧ�ܣ���Ὣ������洢�� err �����У����� fp ����Ϊ NULL��
	if (err != 0)
	{
		printf("\t���ļ�ʧ��!\n");
		return;
	}

	while (!feof(fp))//��¼����
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	}
	fclose(fp);

	if (count == 0)
		printf("\tû����ϵ��¼!\n");
	else
	{
		display();
	}
	errno_t err1 = fopen_s(&fp, "data.txt", "wb");
	if (err1 != 0)
	{
		printf("\t���ܴ򿪣�");
		return;
	}

	for (i = 0; i < count; i++)
		fwrite(&addrinfo[i], LEN, 1, fp);

	printf("\t�Ƿ��������ϵ�ˣ���Y/N��:");
	scanf_s("%s", &ch, sizeof(ch));


	while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
	{
		printf("��    ����");
		scanf_s("%s", addrinfo[count].name, _countof(addrinfo[count].name));
		for (i = 0; i < count; i++)
			if (strcmp(addrinfo[i].name, addrinfo[count].name) == 0)
			{
				printf("\t��������Ѿ����ڣ��������������\n\n");
				fclose(fp);
				return;
			}

		printf("ְ    ҵ��");//ְҵ 
		scanf_s("%s", addrinfo[count].occu, _countof(addrinfo[count].occu));


		printf("�绰���룺");
		scanf_s("%s", addrinfo[count].tel, _countof(addrinfo[count].tel));


		printf("��    �䣺");
		scanf_s("%s", addrinfo[count].email, _countof(addrinfo[count].email));

		printf("��ͥסַ��");
		scanf_s("%s", addrinfo[count].address, _countof(addrinfo[count].address));

		//��¼�����ϵ����Ϣд������ļ��� 
		if (fwrite(&addrinfo[count], LEN, 1, fp) != 1)
		{
			printf("\t�½���ϵ��ʧ�ܣ�\n");
		}
		else
		{
			printf("\t%s¼��ɹ���\n", addrinfo[count].name);
			count++;
		}
		printf("\t�Ƿ�����½���ϵ�ˣ�(Y/N):");
		scanf_s("%s", &ch, sizeof(ch));
	}
	fclose(fp);
	printf("\tִ�гɹ���\n");
	system("pause");
}




void search()
{
	FILE* fp;
	int i, count = 0, nm,li=0,count1=0;
	char ch[2], name[15],email[100];
	errno_t err = fopen_s(&fp, "data.txt", "a+");//��δ���Ĺ�������׷��ģʽ����Ϊ "data.txt" ���ļ�������ļ��������򴴽�����Ȼ���ļ�ָ�뱣���� fp �����С�����ļ���ʧ�ܣ���Ὣ������洢�� err �����У����� fp ����Ϊ NULL��
	if (err != 0)
	{
		printf("\t���ܴ򿪣�\n");
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
		printf("\tû�м�¼��\n");
		return;
	}
	printf("\t���������Ҫ�Ĳ�ѯ��ʽ����������ѯ���ڵ�ַ��ѯ���������ѯ");
	scanf_s("%d", &nm);
	if (nm == 1)
	{
		printf("\t������������");
		scanf_s("%s", &name, 15);
		for (i = 0; i < count; i++)
		{
			if (strcmp(name, addrinfo[i].name) == 0)
			{
				printf("\n\n");
				printf("����     ְҵ       �ֻ�����         ����                ��ͥסַ\t\n");
				printf(FORMAT, DATA);
				printf("\n");
				count1++;
				break;
			}
			
		}
		if (count1 == 0) printf("\nû�и���ϵ�ˣ�");
	}

	if (nm == 2)
	{
		printf("\t�������ͥסַ��");
		scanf_s("%s", &name, 15);
		for (i = 0; i < count; i++)
		{
			if (strcmp(name, addrinfo[i].address) == 0)
			{
				li++;
				if (li == 1)
				{
					printf("\n\n");
					printf("����     ְҵ       �ֻ�����         ����                ��ͥסַ\t\n");
					printf(FORMAT, DATA);
					printf("\n");
				}
				else {
					printf(FORMAT, DATA);
					printf("\n");
				}
			}
		}
		if (li == 0) printf("\nû�и���ϵ�ˣ�");
	}
	if (nm == 3)
	{
		printf("\t���������䣺");
		scanf_s("%s", &email, 100);
		for (i = 0; i < count; i++)
		{
			if (strcmp(email, addrinfo[i].email) == 0)
			{
				li++;
				if (li == 1)
				{
					printf("\n\n");
					printf("����     ְҵ       �ֻ�����         ����                ��ͥסַ\t\n");
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
			printf("\tû���ҵ�����ϵ�ˣ�");
		}
		
	}
		
	printf("\n\n");
		system("pause");
}

	void update()
{
	FILE* fp;
	int i, j, count = 0;
	char name[15];//errno_t ��һ���������ͣ�ͨ�����ڱ�ʾ�������صĴ����롣����һ���޷����������ͣ��ڱ�׼ C ���б�����Ϊ typedef unsigned int errno_t;��
	errno_t err = fopen_s(&fp, "data.txt", "r+");//��δ���Ĺ������Զ�дģʽ����Ϊ "data.txt" ���ļ�������ļ���������ʧ�ܣ���������洢�� err �����У����� fp ����Ϊ NULL�����ļ������ǿ���ͨ�� fp ָ��ִ���ļ� I / O �����������ȡ��д���ļ��ȡ������ļ��Զ�дģʽ�򿪣����ǿ������κ�λ�ý��ж�д����������ļ������ڣ���᷵��һ�������벢���� fp Ϊ NULL��
	if (err != 0)
	{
		printf("\t���ܴ򿪣�\n");
		return;
	}
	while (!feof(fp))
		if (fread(&addrinfo[count], LEN, 1, fp))
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("\tû�м�¼��\n");
		fclose(fp);
		return;
	}
	display();
	printf("\t�޸��˵����֣�");
	scanf_s("%s", &name, 15);
	for (i = 0; i < count; i++)
	{
		if (strcmp(name, addrinfo[i].name) == 0)
		{
			printf("�ҵ���ϵ�˵���Ϣ��������޸ģ�\n");
			printf("��    ����");
			scanf_s("%s", addrinfo[i].name, _countof(addrinfo[i].name));
			printf("ְ    ҵ��");//ְҵ 
		scanf_s("%s", addrinfo[i].occu, _countof(addrinfo[i].occu));
			printf("�绰���룺");
			scanf_s("%s", addrinfo[i].tel, _countof(addrinfo[i].tel));
			printf("��    �䣺");
			scanf_s("%s", addrinfo[i].email, _countof(addrinfo[i].email));
			printf("��ͥסַ��");
			scanf_s("%s", addrinfo[i].address, _countof(addrinfo[i].address));
			printf("�޸ĳɹ���\n");

			errno_t err1 = fopen_s(&fp, "data.txt", "wb");
			if (err1 != 0)
			{
				printf("���ܴ򿪣�\n");
				return;
			}

			for (j = 0; j < count; j++)
				if (fwrite(&addrinfo[j], LEN, 1, fp) != 1)
				{
					printf("\tû�гɹ�����\n");
				}
			fclose(fp);
			system("pause");
			return;
		}
		
	}
	printf("\tû���ҵ�������ݣ�\n");
	system("pause");
}

void del()
{
	FILE* fp;
	int i, j, count = 0;
	char ch[2];
	char name[15];
	errno_t err = fopen_s(&fp, "data.txt", "a+");//��δ���Ĺ�������׷��ģʽ����Ϊ "data.txt" ���ļ�������ļ��������򴴽�����Ȼ���ļ�ָ�뱣���� `fp` �����С�����ļ���ʧ�ܣ���Ὣ������洢�� `err` �����У����� `fp` ����Ϊ `NULL`�����ļ������ǿ���ͨ�� `fp` ָ��ִ���ļ� I / O �����������ȡ��д���ļ��ȡ������ļ���׷��ģʽ�򿪣������ÿ��д��ʱ���Ὣ������ӵ��ļ�ĩβ������ļ������ڣ���ᴴ��һ���µĿ��ļ���
	if (err != 0)
	{
		printf("\t���ܴ�!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("\tû�м�¼��\n");
		return;
	}
	printf("\n");
	display();
	printf("\t���������֣�");
	scanf_s("%s", &name, 15);
	for (i = 0; i < count; i++)
	{
		if (strcmp(name, addrinfo[i].name) == 0)
		{
			printf("\t�Ѿ��ҵ�����ϵ�ˣ��Ƿ�ɾ������Y/N��:");
			scanf_s("%s", ch, sizeof(ch));
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				for (j = i; j < count; j++)
					addrinfo[j] = addrinfo[j + 1];
			count--;
			errno_t err = fopen_s(&fp, "data.txt", "wb");
			if (err != 0)
			{
				printf("\t���ܴ�!\n");
				return;
			}
			for (j = 0; j < count; j++)
				if (fwrite(&addrinfo[j], LEN, 1, fp) != 1)
				{
					printf("\tû�б��棡\n");
				}
			fclose(fp);
			printf("�ɹ�ɾ����\n");
			return;
		}
	}
	printf("\tû���ҵ���ϵ��!\n");
	system("pause");
}

void sort()
{
	FILE* fp;
	struct addritem temp;
	int i, j, count = 0;
    errno_t err = fopen_s(&fp, "data.txt", "r+");//��δ���Ĺ�������׷��ģʽ����Ϊ "data.txt" ���ļ�������ļ��������򴴽�����Ȼ���ļ�ָ�뱣���� `fp` �����С�����ļ���ʧ�ܣ���Ὣ������洢�� `err` �����У����� `fp` ����Ϊ `NULL`�����ļ������ǿ���ͨ�� `fp` ָ��ִ���ļ� I / O �����������ȡ��д���ļ��ȡ������ļ���׷��ģʽ�򿪣������ÿ��д��ʱ���Ὣ������ӵ��ļ�ĩβ������ļ������ڣ���ᴴ��һ���µĿ��ļ���
	if (err != 0)
	{
		printf("���ܴ򿪣�\n");
		return;
	}

	while (!feof(fp))//feof(fp) �� C ���Ա�׼�⺯��֮һ�����ڼ���ļ�ָ�뵱ǰλ���Ƿ��Ѿ������ļ�ĩβ��
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);

	if (count == 0)
	{
		printf("û�м�¼��\n");
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
		printf("���ܴ򿪣�\n");
		return;
	}
	for (i = 0; i < count; i++)
		if (fwrite(&addrinfo[i], LEN, 1, fp) != 1)//fwrite() �� C ���Ա�׼�⺯��֮һ���������ļ���д�����ݡ�fwrite() �����᷵���Ѿ��ɹ�д������ݿ���������˶������д�����ж����� fwrite(&addrinfo[i], LEN, 1, fp) != 1��������ķ���ֵ������ 1�����ʾд��ʧ�ܻ���δ����ȫд��Ŀ�����ݣ����Ը���ʵ��������д����������������Ϣ�����׳��쳣��
		{
			printf("\tд��ʧ�ܣ�\n");
		}
	fclose(fp);
	printf("\t�ɹ�����\n");
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
		printf("����     ְҵ       �ֻ�����         ����                ��ͥסַ\t\n");
	}
	if(count==0) printf("\tû����ϵ�ˣ�\n");
	for (i = 0; i < count; i++)
	{
		printf(FORMAT, DATA);
		printf("\n");
	}
	printf("\n\n");
	fclose(fp);
	system("pause");
}