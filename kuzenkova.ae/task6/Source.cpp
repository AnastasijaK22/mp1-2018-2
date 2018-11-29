#include <stdio.h>
#include <math.h>
#include <locale.h>

void input1()
{
	printf("Введите номер функции:\n 1 - exp(x)\n");
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
	n_func = input_check(1, 1, p1);
	printf("Введите значение x\n");
	scanf_s("%lf",&x);
	N = input_check(1, 1000, p2);
	printf("%lf ", my_exp(x,N,eps));
	printf("%d ", N);
	scanf_s("%d", &N);
}