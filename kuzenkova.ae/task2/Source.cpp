#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

int randomchik(int x, int y)
{
	return x + rand() % (y - x + 1);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	int rejim; //����������, ���������� �� �����
	int number; //�����
	int k, m = 0; // k - ��� �����, ������� ������ ������������ ��� ������ 1 ��� ����� ������������ �����������, m - ����� �������
	int a = 1, b = 1000; // ������� �������
	char c[2]; //�������� ������ < > =

	do {
		printf("����� �����: 1 - ��������� ����������, 2 - ������������ ����������\n");
		scanf_s("%d", &rejim);
	} while (rejim != 1 && rejim != 2);

	if (rejim == 1)
	{
		number = randomchik(a, b);
		while (1 > 0)
		{
			printf("����� �����:\n");
			scanf_s("%d", &k);
			m++;
			if (k > number)
				printf("��������� ����� ������\n");
			if (k < number)
				printf("��������� ����� ������\n");
			if (k == number)
				break;
		}
		printf("�� �������, ����������! ��� ����� %d. �� ������� �� %d �������", number, m);

	}
	else
		if (rejim == 2)
		{
			printf("������� ���������� �����\n");
			scanf_s("%d", &number);
			gets_s(c);
			k = randomchik(a, b);
			while (1 > 0)
			{
				printf("���� ����� %d ?\n", k);
				gets_s(c);
				m++;
				if (c[0] == '>')
				{
					a = k - 1;
					k = randomchik(a, b);
				}
				if (c[0] == '<')
				{
					b = k - 1;
					k = randomchik(a, b);
				}
				if (c[0] == '=')
					break;
			}
			printf("���� ����� %d. � ������ �� %d �������. ���������� �����:) ", k, m);
		}
	scanf_s("%d", &k);

}