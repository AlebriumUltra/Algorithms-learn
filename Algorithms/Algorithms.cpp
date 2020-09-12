#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"


void SearchMaxMin(int* Numbers, int Size) {
	int Max, Min;
	Max = Numbers[0]; // Присваиваем первый элемент массива
	Min = Numbers[0];
	for (int i = 0; i < Size - 1; i++) {
		if (Max < Numbers[i + 1]) { // Сравниваем элементы и присваиваем наибольшее из 2-ух
			Max = Numbers[i + 1];
		}
		if (Min > Numbers[i + 1]) { // Сравниваем элементы и присваиваем наименьшее из 2-ух
			Min = Numbers[i + 1];
		}
	}
	printf("\n  Min: %d\n  Max: %d", Min, Max);
	printf("\n  Difference: %d", abs(Max - Min));
}

void RandomArray(int* Numbers, int Size) {
	printf(" Array: ");
	for (int i = 0; i < Size; i++) {
		Numbers[i] = rand() % 201 - 100; // Заполнение массива случайными цифрами в диапазоне от -100 до 100
		printf("%d ", Numbers[i]);
	}
}

void RandomMatrix(int** Matrix, int Rows, int Cols) {
	printf(" Matrix: \n\n");
	for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Cols; j++) {
			Matrix[i][j] = rand() % 201 - 100; // Заполнение массива случайными цифрами в диапазоне от -100 до 100
			printf(" %d\t", Matrix[i][j]);
		}
		printf("\n");
	}
}

int main() {
	// Задание 1,2,3
	srand(time(NULL));
	int* Numbers;
	int Size;
	printf(" Enter size array: "); // Пользовательский ввод размера массива
	scanf("%d", &Size);
	Numbers = (int*)malloc(sizeof(int) * Size); // Выделение памяти
	RandomArray(Numbers, Size); // Функция по инициализации массива случайными числами
	printf("\n");
	SearchMaxMin(Numbers, Size); // Поиск максимального и минимального элементов и вывод разницы
	free(Numbers);
	printf("\n");

	// Задание 4
	int Rows, Cols;
	printf("Enter amount rows: ");
	scanf("%d", &Rows);
	printf("Enter amount cols: ");
	scanf("%d", &Cols);
	int** Matrix = (int**)malloc(sizeof(int) * Rows);
	for (int i = 0; i < Rows; i++) {
		Matrix[i] = (int*)malloc(sizeof(int) * Cols);
	}
	int SumCols = 0;
	printf("\n\n");
	RandomMatrix(Matrix, Rows, Cols); // Инициализвация массива случайными числами
	printf("\n\n");
	for (int j = 0; j < Cols; j++) { // Т.к считается сумма столбца, меняем циклы местами
		for (int i = 0; i < Rows; i++) {
			SumCols += Matrix[i][j];
		}
		printf("Col (%d): %d\n", j + 1, SumCols);
		SumCols = 0; // Обнуляем для считывания следующих столбцов
	}
	for (int i = 0; i < Rows; i++) {
		free(Matrix[i]);
	}
	free(Matrix);
	_getch();
}