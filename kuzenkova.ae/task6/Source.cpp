#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <locale.h>

void input1()
{
	printf("Введите номер функции:\n 1 - exp(x)\n");
	printf(" 2 - sin(x)\n");
	printf(" 3 - cos(x)\n");
}

void input2()
{
	printf("Введите число слагаемых от 1 до 1000\n");
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

double my_exp(double x, int& N, double eps)
{
	int i;
	double result = 1;
	double buf = 1;
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

double my_cos(double x, int& N, double eps)
{
	int i;
	int j = 2;
	double result = 1;
	double buf = 1;
	//x = x - 2*M_PI*floor((x / (2*M_PI)));
	printf("%fl ", x);
	for (i = 2; i <= N; i++)
	{
		//buf = (-1)*(buf * x * x) / (j * (j - 1));
		//buf = (-1)*((x * x )/(j * (j - 1)))*(buf);
		buf = (-1)*((x / j)*(x / (j - 1)))*(buf);
		j += 2;
		result = result + buf;
		if (fabs(cos(x) - result) < eps)
			break;
	}
	N = i - 1;
	return result;
}

double my_sin(double x, int& N, double eps)
{
	int i;
	int j = 3;
	//x = x - 2 * M_PI*floor((x / (2 * M_PI)));
	double result = x;
	double buf = x;
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

int main()
{
	setlocale(LC_ALL, "Rus");
	double x;
	int N;
	double eps = 0.000001;
	int n_func;
	void (*p1)();
	void (*p2)();
	p1 = input1;
	p2 = input2;
	n_func = input_check(1, 2, p1);
	printf("Введите значение x\n");
	scanf_s("%lf",&x);
	N = input_check(1, 1000, p2);
	printf("%lf ", my_cos(x,N,eps));
	printf("%d \n", N);
	printf("%lf ", cos(x));
	scanf_s("%d", &N);
}