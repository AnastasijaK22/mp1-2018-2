#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

int compare(int a, int b, int k)
{
	if (k == 1)
		if (a > b)
			return 1;
		else
			return 0;
	if (k == 2)
		if (a < b)
			return 1;
		else
			return 0;
}
void buble_sort(int a[], int size, int k)
{
	int i,j;
	int c;
	for (i = 0; i < size; i++)
		for (j = (size-1); j > i; j--)
			if (compare(a[j],a[j-1],k) == 1)
			{
				c = a[j];
				a[j] = a[j - 1];
				a[j - 1] = c;
			}
}
void select_sort(int a[], int size, int k)
{
	int i, j;
	int c;
	int m;//min ��� max
	for (i = 0; i < size; i++)
	{
		m = i;
		c = a[i];
		for (j = (i + 1); j < size; j++)
		{
			if (compare(a[j], c, k) == 1)
			{
				c = a[j];
				m = j;
			}
		}	
		a[m] = a[i];
		a[i] = c;
	}
}
void insert_sort(int a[], int size, int k)
{
	int i, j;
	int c;
	for (i = 0; i < size; i++)
	{
		c = a[i];
		for (j = i - 1; j >= 0 && (compare(c, a[j], k) == 1); j--)
			a[j + 1] = a[j];
		a[j + 1] = c;
	}
}
void merge(int a[], int l, int mid, int r, int k)
{
	int pos1 = l;
	int pos2 = mid + 1;
	int pos3 = 0;
	int *buf = new int[r - l + 1];
	while (pos1 <= mid && pos2 <= r)
	{
		if (compare(a[pos1], a[pos2], k) == 1)
			buf[pos3++] = a[pos1++];
		else
			buf[pos3++] = a[pos2++];
	}
	while (pos2 <= r)
		buf[pos3++] = a[pos2++];
	while (pos1 <= mid)
		buf[pos3++] = a[pos1++];
	for (pos3 = 0; pos3 < r - l + 1; pos3++)
		a[l + pos3] = buf[pos3];
}
void merge_sort(int a[], int l, int r, int k)
{
	int mid;
	if (l < r)
	{
		mid = (l + r) / 2;
		merge_sort(a, l, mid, k);
		merge_sort(a, mid + 1, r, k);
		merge(a, l, mid, r, k);
	}
}
void quick_sort(int *a, int size, int k)
{
	int i = 0, j = size - 1;
	int buf, mid;
	mid = a[ size>>1 ];
	do
	{
		while (compare(a[i],mid,k) == 1 )
			i++;
		while (compare(mid, a[j],k) == 1)
			j--;
		if (i <= j) 
		{
			buf = a[i]; 
			a[i] = a[j]; 
			a[j] = buf;
			i++; 
			j--;
		}
	} 
	while (i <= j);
	if (j > 0) 
		quick_sort(a, j+1,k);
	if (size > i) 
		quick_sort(a + i, size - i,k);
}
int increment(long inc[], long size) {
	int p1, p2, p3, s;

	p1 = p2 = p3 = 1;
	s = -1;
	do {
		if (++s % 2) {
			inc[s] = 8 * p1 - 6 * p2 + 1;
		}
		else {
			inc[s] = 9 * p1 - 9 * p3 + 1;
			p2 *= 2;
			p3 *= 2;
		}
		p1 *= 2;
	} while (3 * inc[s] < size);

	return s > 0 ? --s : 0;
}
void shell_sort(int a[], int size, int k)
{
	long inc, i, j, seq[40];
	int s;
	s = increment(seq, size);
	while (s >= 0) {
		inc = seq[s--];
		for (i = inc; i < size; i++) {
			int buf = a[i];
			for (j = i - inc; (j >= 0) && (compare(buf,a[j],k) == 1); j -= inc)
				a[j + inc] = a[j];
			a[j + inc] = buf;
		}
	}
}
int main()
{
	setlocale(LC_ALL, "Rus");
	//��� k ������ 1 �� ��������, ��� k ������ 2 �� �����������
	int a[10] = { 9, 4, 5, 6, 1, 7, 2, 3, 8, 0 };
	int i;
	int N = 10;
	int flag = 0;
	int order_sort = 0, number_sort = 0;
	clock_t t1, t2;
	double tt = 0;
	printf("    �������� �������� \"� � ���� �����������\"\n");
	printf("    ���� :\n");
	while (1 > 0)
	{
		printf("������� ���� �� ��������\n");
		//�������� � �������
		//����� ������ � ��������� ��������
		printf("�������� ����������:\n");
		printf("    1 - �������\n");
		printf("    2 - �������\n");
		printf("    3 - ���������\n");
		printf("    4 - ��������\n");
		printf("    5 - �����, ����� ��������� ��� ������� ����������\n");
		printf("    6 - �����\n");
		flag = 0;
		do
		{
			if (flag == 1)
				printf("�� ����������� ����� �����, ��������� �������\n");
			else
				flag = 1;
			scanf_s("%d", &number_sort);
		} 
		while (number_sort < 1 || number_sort > 6);
		printf("��� ������ �������������?\n1 - �� ��������, 2 -�� �����������\n");
		flag = 0;
		do
		{
			if (flag == 1)
				printf("�� ����������� ����� �����, ��������� �������\n");
			else
				flag = 1;
			scanf_s("%d", &order_sort);
		} 
		while (order_sort < 1 || order_sort > 2);
		switch (number_sort)
		{
		case 1: t1 = clock();  
				buble_sort(a, N, order_sort); 
				t2 = clock(); 
				break;
		case 2: t1 = clock();  
				select_sort(a, N, order_sort); 
				t2 = clock();
				break;
		case 3: t1 = clock();  
				insert_sort(a, N, order_sort); 
				t2 = clock();
				break;
		case 4: t1 = clock();  
				merge_sort(a, 0, N - 1, order_sort); 
				t2 = clock();
				break;
		case 5: t1 = clock();
				quick_sort(a, N, order_sort);
				t2 = clock();
				break;
		case 6: t1 = clock();
				shell_sort(a, N, order_sort); 
				t2 = clock();
				break;
		}
		//����� ����������
		tt = double(t2 - t1) / CLOCKS_PER_SEC;
		printf("\n����� ������ ���������� :%f\n\n", tt);
		for (i = 0; i < N; i++)
			printf("%d\n", a[i]);
		printf("������ ���������� ������?\n     ������� 0, ���� ������ ��������� ������\n    ����� ������, ����� ����������\n");
		scanf_s("%d", &flag);
		if (flag == 0)
			break;
	} 
	scanf_s("%d", &N);
}