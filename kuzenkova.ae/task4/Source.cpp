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
	char name[10][100] = { 0 };//массив для хранения наименований
	char x[100];//вспомогательный знаковый массив
	int discounts[10] = { 0 }, price[10] = { 0 }, barcode[10][5] = { 0 };//массив для скидок, для цены за штуку, для штрих кодов
	int quantity[10] = { 0 };//массив для количества определенных товаров
	int products[100] = { 0 };//хранится какие продукты были отсканированы
	int i,j = 0,z = 0;//индексы для массивов и счетчики для циклов, z вспомогательная переменная вводимая пользователем 
	int flag;//
	int total=0;//итоговая сумма
	int com;//стоимость товаров
	float discount = 0;//скидка
	int stockn = 0, n = 0;//stockn - количество товаров на скаладе, n - количество товаров пользователя
	fopen_s (&f,"stock.txt", "r");//открываем файл
	while (fgetc(f)!=EOF) //выполняем считывание данных из файла stock.txt пока он не закончится
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
	printf("Список штрих кодов\n");
	for (i = 0; i < stockn; i++)//назначаем скидку, и преобразуем штрих код в число для простоты
	{
		printf("%d%d%d%d \n", barcode[i][0], barcode[i][1], barcode[i][2], barcode[i][3]);
		for (j = 0; j < 4 ; j++)
			barcode[i][4] = barcode[i][4] * 10 + barcode[i][j];
		discounts[i] = randomchik(1, 50);
	}
	do //обработка информации введенной пользователем
	{
		flag = 0;
		do 
		{
			if (flag == 1)
				printf("Неверно введен штрихкод\n");
			printf("Введите штрихкод. Если у вас все введите -1\n");
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
			printf("Такого штрих кода нет\n");
		else//вывод описанияотсканированного товара
		{
			printf("Ваш продукт:\n");
			for (j = 0; j < strlen(name[i]); j++)
				printf("%c", name[i][j]);
			printf(": цена - %d руб.", price[i]);
			printf(", скидка - %d%%\n\n", discounts[i]);
		}
	}
	while (1 > 0);
	if (n > 0) {//создание чека
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
		printf("\nПодитог:");
		for (j = 8; j <= (38 - length(total)); j++)
			printf(" ");
		printf("=%d\n", total);
		printf("Скидка:");
		for (j = 7; j <= (38 - length((int)discount)); j++)
			printf(" ");
		printf("=%d\n", (int)discount);
		total = total - (int)discount;
		printf("Итог:");
		for (j = 5; j <= (38 - length(total)); j++)
			printf(" ");
		printf("=%d\n", total);
	}
	scanf_s("%d\n", &n);
}