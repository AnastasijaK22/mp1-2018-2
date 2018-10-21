#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

int randomchik(int x, int y)
{
	return x + rand() % (y - x + 1);
}

int length(int x)
{
	int k=0;
	while (x > 0)
	{
		x = x / 10;
		k++;
	}
	return k;
}

int main() 
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	FILE *f;
	char name[10][100] = { 0 };//������ ��� �������� ������������
	char x[100];//��������������� �������� ������
	int discounts[10] = { 0 }, price[10] = { 0 }, barcode[10][5] = { 0 };//������ ��� ������, ��� ���� �� �����, ��� ����� �����
	int quantity[10] = { 0 };//������ ��� ���������� ������������ �������
	int products[100] = { 0 };//�������� ����� �������� ���� �������������
	int i,j = 0,z = 0;//������� ��� �������� � �������� ��� ������, z ��������������� ���������� �������� ������������� 
	int flag;//
	int total=0;//�������� �����
	int com;//��������� �������
	float discount = 0;//������
	int stockn = 0, n = 0;//stockn - ���������� ������� �� �������, n - ���������� ������� ������������
	fopen_s (&f,"stock.txt", "r");//��������� ����
	while (fgetc(f)!=EOF) //��������� ���������� ������ �� ����� stock.txt ���� �� �� ����������
	{
		fgets(x,100,f);
		for (i = 0; i < 4; i++)
		{
			barcode[stockn][i] =(int)x[i]-48;
		}
		i = 6;
		while (x[i] != '*')
		{
			name[stockn][i-6] = x[i];
			name[stockn][i-5] = '\0';
			i++;
		}
		for (j = (i + 2); j < (strlen(x)-1); j++)
		{
			z = (int)x[j]-48;
			price[stockn] = price[stockn] * 10 + z;
		}
		stockn++;
	}
	fclose(f);
	printf("������ ����� �����\n");
	for (i = 0; i < stockn; i++)//��������� ������, � ����������� ����� ��� � ����� ��� ��������
	{
		printf("%d%d%d%d \n", barcode[i][0], barcode[i][1], barcode[i][2], barcode[i][3]);
		for (j = 0; j < 4 ; j++)
			barcode[i][4] = barcode[i][4] * 10 + barcode[i][j];
		discounts[i] = randomchik(1, 50);
	}
	do //��������� ���������� ��������� �������������
	{
		flag = 0;
		do 
		{
			if (flag == 1)
				printf("������� ������ ��������\n");
			printf("������� ��������. ���� � ��� ��� ������� -1\n");
			scanf_s("%d",&z);
			flag = 1;
		} 
		while (z<-1 || z>9999);
		if (z == -1)
			break;
		for (i = 0; i < stockn; i++)
		{
			if (z == barcode[i][4])
			{
				quantity[i]++;
				if (quantity[i] == 1)
				{
					products[n] = i;
					n++;
				}
				break;
			}
		}
		if (i == stockn)
			printf("������ ����� ���� ���\n");
		else//����� ������������������������ ������
		{
			printf("��� �������:\n");
			for (j = 0; j < strlen(name[i]); j++)
				printf("%c", name[i][j]);
			printf(": ���� - %d ���.", price[i]);
			printf(", ������ - %d%%\n\n", discounts[i]);
		}
	}
	while (1 > 0);
	if (n > 0) {//�������� ����
		for (i = 0; i < 40; i++)
			printf("*");
		printf("\n");
		for (i = 0; i < 40; i++)
			printf("*");
		printf("\n\n");
		for (i = 0; i < n; i++)
		{
			puts(name[products[i]]);
			printf("%d x %d", quantity[products[i]], price[products[i]]);
			com = quantity[products[i]] * price[products[i]];
			for (j = (3 + length(quantity[products[i]]) + length(price[products[i]])); j <= (38 - length(com)); j++)
				printf(" ");
			printf("=%d\n", com);
			discount = (com*discounts[products[i]]) / 100. + discount;
			total = com + total;
		}
		printf("\n�������:");
		for (j = 8; j <= (38 - length(total)); j++)
			printf(" ");
		printf("=%d\n", total);
		printf("������:");
		for (j = 7; j <= (38 - length((int)discount)); j++)
			printf(" ");
		printf("=%d\n", (int)discount);
		total = total - (int)discount;
		printf("����:");
		for (j = 5; j <= (38 - length(total)); j++)
			printf(" ");
		printf("=%d\n", total);
	}
	scanf_s("%d\n", &n);
}