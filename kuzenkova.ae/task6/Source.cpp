#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <locale.h>

void input1()
{
	printf("Выберите режим:\n 1 - обычный \n 2 - эксперимент\n");
}

void input2()
{
	printf("Введите номер функции:\n 1 - exp(x)\n");
	printf(" 2 - sin(x)\n");
	printf(" 3 - cos(x)\n");
	printf(" 4 - sh(x)\n");
}

void input3()
{
	printf("Введите число слагаемых от 1 до 1000\n");
}

void input4()
{
	printf("Введите число экспериментов от 1 до 25\n");
}

int input_check(int left, int right, void (*p)( ) )
{
	int n;
	do
	{
		p();
		scanf_s("%d", &n);
		if (n < left || n > right)
			printf("Неверно введен номер!\n");
	}
	while (n < left || n > right);
	return n;
}

long double my_exp(long double x, int& N, long double eps)
{
	int i;
	long double result = 1;
	long double buf = 1;
	for (i = 2; i <= N; i++)
	{
		buf = (buf * x) / (i-1);
		result = result + buf;
		if (fabs(exp(x) - result) < eps) 
			break;
	}
	N = i - 1;
	return result;
}

long double my_cos(long double x, int& N, long double eps)
{
	int i;
	int j = 2;
	long double result = 1;
	long double buf = 1;
	//x = x - 2*M_PI*floor((x / (2*M_PI)));
	//printf("%fl ", x);
	for (i = 2; i <= N; i++)
	{
		//buf = (-1)*(buf * x * x) / (j * (j - 1));
		//buf = (-1)*((x * x )/(j * (j - 1)))*(buf);
		buf = (-1)*(buf * x * x) / (j * (j - 1));
		//printf("%.16fl \n", buf);
		j += 2;
		result = result + buf;
		if (fabs(cos(x) - result) < eps) 
			break;
	}
	N = i - 1;
	return result;
}

long double my_sin(long double x, int& N, long double eps)
{
	int i;
	int j = 3;
	//x = x - 2 * M_PI*floor((x / (2 * M_PI)));
	long double result = x;
	long double buf = x;
	for (i = 2; i <= N; i++)
	{
		buf = (-1)*((x * x )/(j * (j - 1)))*(buf);
		j += 2;
		result = result + buf;
		if (fabs(sin(x) - result) < eps) 
			break;
	}
	N = i - 1;
	return result;
}

long double my_sh(long double x, int& N, long double eps)
{
	int i;
	int j = 3;
	long double result = x;
	long double buf = x;
	for (i = 2; i <= N; i++)
	{
		buf = ((x * x) / (j * (j - 1)))*(buf);
		j += 2;
		result = result + buf;
		if (fabs(sin(x) - result) < eps)
			break;
	}
	N = i - 1;
	return result;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	long double x;
	int N;
	int mode;
	long double eps = 0.000001;
	long double result = 0, reference = 0;;
	int n_func;
	int i;
	void (*p)();
	long double (*pf[4])(long double, int&, long double);
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
	{
		p = input2;
		n_func = input_check(1, 4, p);
		printf("Введите значение x\n");
		scanf_s("%lf", &x);
		do
		{
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
	{
		p = input2;
		n_func = input_check(1, 4, p);
		printf("Введите значение x\n");
		scanf_s("%lf", &x);
		eps = -1;
		p = input4;
		N = input_check(1, 25, p);
		reference = pfreference[n_func - 1](x);
		printf("N      Эталон         Оценка       Разница\n");
		printf("-      ------         ------       -------\n");
		for (i = 1; i <= N; i++)
		{
			result = pf[n_func - 1](x, i, eps);
			printf("%.2d %lf %lf %lf\n", i, reference, result, fabs(reference - result));
		}
	}
	scanf_s("%d", &N);
}