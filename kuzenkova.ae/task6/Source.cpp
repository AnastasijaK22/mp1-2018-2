#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <locale.h>

void input1() //функция, выводящая режимы работы
{
	printf("Выберите режим:\n 1 - обычный \n 2 - эксперимент\n");
}
//функция, выводящая номера функций
void input2() 
{
	printf("Введите номер функции:\n 1 - exp(x)\n");
	printf(" 2 - sin(x)\n");
	printf(" 3 - cos(x)\n");
	printf(" 4 - sh(x)\n");
}
//функция, выводящая интервал числа слагаемых
void input3() 
{
	printf("Введите число слагаемых от 1 до 1000\n");
}
//функция, выводящая интервал числа экспериментов
void input4() 
{
	printf("Введите число экспериментов от 1 до 25\n");
}
//функция, контролирующая ввод значений
int input_check(int left, int right, void (*p)( ) )
{
	int n;
	do
	{
		p(); //вызов функции вывода
		scanf_s("%d", &n); //ввод значения
		if (n < left || n > right) // проверка введенного
			printf("Неверно введен номер!\n"); 
	}
	while (n < left || n > right);
	return n;
}
//функция подсчета экспоненты
long double my_exp(long double x, int& N, long double eps)
{
	int i;
	long double result = 1;
	long double buf = 1;
	long double reference = exp(x);
	for (i = 2; (i <= N) && (fabs(reference - result) >= eps); i++)
	{
		buf = (buf * x) / (i-1);
		result = result + buf;
	}
	N = i - 1;
	return result;
}
//функция подсчета косинуса
long double my_cos(long double x, int& N, long double eps)
{
	int i;
	long double result = 1;
	long double buf = 1;
	long double reference = cos(x);
	//x = fmod(x, 2 * M_PI);
	for (i = 2; (i <= N) && (fabs(reference - result) >= eps); i++)
	{
		buf *= (-1) * ((x * x ) / ((2 * i - 2) * (2 * i - 3)));
		result = result + buf;
	}
	N = i - 1;
	return result;
}
//функция подсчета синуса
long double my_sin(long double x, int& N, long double eps)
{
	int i;
	//x = fmod(x, 2 * M_PI);
	long double result = x;
	long double buf = x;
	long double reference = sin(x);
	for (i = 2; (i <= N) && (fabs(reference - result) >= eps); i++)
	{
		buf *= (-1) * ((x * x ) / ((2 * i - 2) * (2 * i - 1)));
		result = result + buf;
	}
	N = i - 1;
	return result;
}
//функция подсчета гиперболического синуса
long double my_sh(long double x, int& N, long double eps)
{
	int i;
	long double result = x;
	long double buf = x;
	long double reference = sinh(x);
	for (i = 2; (i <= N) && (fabs(reference - result) >= eps); i++)
	{
		buf *= ((x * x) / ((2 * i - 2) * (2 * i - 1)));
		result = result + buf;
	}
	N = i - 1;
	return result;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	long double x;
	int N; //число слагаемых 
	int mode; //режим
	long double eps = 0.000001; //точность
	long double result = 0, reference = 0; //результат и эталон
	int n_func; //номер функции 
	int i;
	void (*p)(); //указатель на функцию (для вывода)
	//массив указателей для моих функций
	long double (*pf[4])(long double, int&, long double);
	//массив указателей для  встроенных функций
	double (*pfreference[4])(double);
	pf[0] = my_exp; 
	pf[1] = my_sin;
	pf[2] = my_cos;
	pf[3] = my_sh;
	pfreference[0] = exp;
	pfreference[1] = sin;
	pfreference[2] = cos;
	pfreference[3] = sinh;
	p = input1;
	mode = input_check(1, 2, p);
	if (mode == 1)
	{//первый режим
		p = input2;
		n_func = input_check(1, 4, p);
		printf("Введите значение x\n");
		scanf_s("%lf", &x);
		do
		{//проверка введенной точности
			printf("Введите точность вычислений >=0.000001\n");
			scanf_s("%lf", &eps);
			if (eps < 0.000001)
				printf("Неверно введена точность!");
		} 
		while (eps < 0.000001);
		p = input3;
		N = input_check(1, 1000, p);
		result = pf[n_func - 1](x, N, eps);
		reference = pfreference[n_func - 1](x);
		printf("Эталонное значение:               %lf\n", reference);
		printf("Оценка значения функции:          %lf\n", result);
		printf("Разница между оценкой и эталоном: %lf\n", fabs(reference - result));
		printf("Количество вычисленных слагаемых: %d \n", N);
	}
	else
	{// второй режим
		p = input2;
		n_func = input_check(1, 4, p);
		printf("Введите значение x\n");
		scanf_s("%lf", &x);
		eps = -1;
		p = input4;
		N = input_check(1, 25, p);
		reference = pfreference[n_func - 1](x);
		printf("N           Эталон           Оценка         Разница\n");
		printf("-           ------           ------         -------\n");
		for (i = 1; i <= N; i++)
		{
			result = pf[n_func - 1](x, i, eps);
			printf("%.2d %16.5lf %16.5lf %16.5lf\n", i, reference, result, fabs(reference - result));
		}
	}
	scanf_s("%d", &N);
}