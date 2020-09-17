#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"

#define SIZE 2000

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	clock_t start, end; // объявляем переменные для определения времени выполнения
	int i = 0, j = 0, r;
	int** a;
	int** b;
	int** c;
	int elem_c;
	a = (int**)malloc(SIZE * sizeof(int));
	b = (int**)malloc(SIZE * sizeof(int));
	c = (int**)malloc(SIZE * sizeof(int));
	for (int i = 0; i < SIZE; i++) {
		a[i] = (int*)malloc(SIZE * sizeof(int));
		b[i] = (int*)malloc(SIZE * sizeof(int));
		c[i] = (int*)malloc(SIZE * sizeof(int));
	}
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	while (i < SIZE)
	{
		while (j < SIZE)
		{
			a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	i = 0; j = 0;
	while (i < SIZE)
	{
		while (j < SIZE)
		{
			b[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	start = clock();
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			elem_c = 0;
			for (r = 0; r < SIZE; r++)
			{
				elem_c = elem_c + a[i][r] * b[r][j];
				c[i][j] = elem_c;
			}
		}
	}
	end = clock();
	printf("Время: %lf с.", (double)(end - start) / CLK_TCK);
	_getch();
	return(0);
}