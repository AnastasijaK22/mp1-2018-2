#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <io.h>

struct datafail //структура для хранения имени и размера файла
{
	unsigned long size;
	char name[32];
};
//функция сравнения двух элементов  
int compare(struct datafail a, struct datafail b, int k) 
{
	if (k == 1)
		if (a.size > b.size)
			return 1;
		else
			return 0;
	if (k == 2)
		if (a.size < b.size)
			return 1;
		else
			return 0;
}
//функция сортировки пузырьком
void buble_sort(struct datafail a[], long size, int k)
{
	long i,j;
	struct datafail c;
	for (i = 0; i < size; i++)
		for (j = (size-1); j > i; j--)
			if (compare(a[j],a[j-1],k) == 1)
			{
				c = a[j];
				a[j] = a[j - 1];
				a[j - 1] = c;
			}
}
//функция сортировки выбором
void select_sort(struct datafail a[], long size, int k)
{
	long i, j;
	struct datafail c;
	long m;//min или max
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
//функция сортировки вставками
void insert_sort(struct datafail a[], long size, int k)
{
	long i, j;
	struct datafail c;
	for (i = 0; i < size; i++)
	{
		c = a[i];
		for (j = i - 1; j >= 0 && (compare(c, a[j], k) == 1); j--)
			a[j + 1] = a[j];
		a[j + 1] = c;
	}
}
//функция организующая слияние, двух упорядоченных последовательностей
void merge(struct datafail a[], long l, long mid, long r, int k)
{
	long pos1 = l;
	long pos2 = mid + 1;
	long pos3 = 0;
	struct datafail *buf = new struct datafail[r - l + 1];
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
//функция сортировки слиянием
void merge_sort(struct datafail a[], long l, long r, int k)
{
	long mid;
	if (l < r)
	{
		mid = (l + r) / 2;
		merge_sort(a, l, mid, k);
		merge_sort(a, mid + 1, r, k);
		merge(a, l, mid, r, k);
	}
}
//функция сортировки Хоара
void quick_sort(struct datafail *a, long size, int k)
{
	long i = 0, j = size - 1;
	struct datafail buf, mid;
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
//функция считающее приращение для сортировки Шелла
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
//функция сортировки Шелла
void shell_sort(struct datafail a[], long size, int k)
{
	long inc, i, j, seq[40];
	int s;
	s = increment(seq, size);
	while (s >= 0) {
		inc = seq[s--];
		for (i = inc; i < size; i++) {
			struct datafail buf = a[i];
			for (j = i - inc; (j >= 0) && (compare(buf,a[j],k) == 1); j -= inc)
				a[j + inc] = a[j];
			a[j + inc] = buf;
		}
	}
}
int main()
{
	setlocale(LC_ALL, "Rus");
	struct _finddata_t c_file;
	intptr_t hFile;
	char path[260];
	struct datafail a[10000];//массив с данными о файле
	long i;
	long N = 0;//Число файлов в каталоге
	int flag = 0, flag1 = 0;
	//order_sort - по убыванию или возрастанию сортировать, number_sort - какая сортировка
	int order_sort = 0, number_sort = 0;
	//переменные для подсчета времени
	clock_t t1, t2;
	double tt = 0;
	printf("    Файловый менеджер \"Я у мамы программист\"\n");
	printf("    Меню :\n");
	while (1 > 0)
	{
		if (flag1 == 0)
		{	printf("Введите путь до директории в таком формате с:\\..\\\n");
			gets_s(path, 260);
			strcat(path, "*");//добавляем * в конец пути
		}
		if ((hFile = _findfirst(path, &c_file)) == -1L)
			printf("Нет файлов в этой директории!\n");
		else
		{
			//считываем данные о файлах из директории
			N = 0;
			printf("FILE               SIZE\n", ' ');
			printf("----               ----\n", ' ');
			do {
				strncpy(a[N].name, c_file.name, 32);
				a[N].size = c_file.size;
				printf("%-12.12s %10u\n", a[N].name, a[N].size);
				N++;
			} 
			while (_findnext(hFile, &c_file) == 0);
			_findclose(hFile);
			printf("Число файлов: %d\n\n", N);
			//пользователь выбирает сортировку
			printf("Выбирите сортировку:\n");
			printf("    1 - Пузырек\n");
			printf("    2 - Выбором\n");
			printf("    3 - Вставками\n");
			printf("    4 - Слиянием\n");
			printf("    5 - Хоара, более известная как быстрая сортировка\n");
			printf("    6 - Шелла\n");
			flag = 0;
			//проверка правильности ввода
			do
			{
				if (flag == 1)
					printf("Вы неправильно ввели номер, повторите попытку\n");
				else
					flag = 1;
				scanf_s("%d", &number_sort);
			} 
			while (number_sort < 1 || number_sort > 6);
			printf("Как хотите отсортировать?\n1 - по убыванию, 2 -по возрастанию\n");
			flag = 0;
			//проверка правильности ввода
			do
			{
				if (flag == 1)
					printf("Вы неправильно ввели номер, повторите попытку\n");
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
			//подсчет времени
			tt = double(t2 - t1) / CLOCKS_PER_SEC;
			//вывод результата
			printf("FILE               SIZE\n", ' ');
			printf("----               ----\n", ' ');
			for (i = 0; i < N; i++)
				printf("%-12.12s %10u\n", a[i].name, a[i].size);
			printf("\nВремя работы сортировки :%f\n\n", tt);
			printf("Хотите продолжить работу?\n     Введите 0, если хотите закончить работу\n     Любое другое, чтобы продолжить\n");
			scanf_s("%d", &flag);
			getchar();
			if (flag == 0)
				break;
			printf("Хотите отсортировать файлы из этого директория с помощью другой сортировки?\n 0 - нет, 1 - да\n");
			flag = 0;
			do
			{
				if (flag == 1)
					printf("Вы неправильно ввели номер, повторите попытку\n");
				else
					flag = 1;
				scanf_s("%d", &flag1);
			} 
			while (flag1 < 0 || flag1 > 1);
			getchar();
		}
	} 
	scanf_s("%d", &N);
}