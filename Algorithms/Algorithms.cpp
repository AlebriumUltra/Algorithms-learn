#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"

#define ROWS 10
#define COLS 5



void SearchMaxMin(int* Numbers, int Size) {
	int Max, Min;
	Max = Numbers[0];
	Min = Numbers[0];
	for (int i = 0; i < Size - 1; i++) {
		if (Max < Numbers[i + 1]) {
			Max = Numbers[i + 1];
		}
		if (Min > Numbers[i + 1]) {
			Min = Numbers[i + 1];
		}
	}
	printf("\n  Min: %d\n  Max: %d", Min, Max);
	printf("\n  Difference: %d", abs(Max - Min));
}

void RandomArray(int* Numbers, int Size) {
	printf(" Array: ");
	for (int i = 0; i < Size; i++) {
		Numbers[i] = rand() % 201 - 100;
		printf("%d ", Numbers[i]);
	}
}

void RandomMatrix(int Matrix[ROWS][COLS]) {
	printf(" Matrix: \n\n");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			Matrix[i][j] = rand() % 201 - 100;
			printf(" %d\t", Matrix[i][j]);
		}
		printf("\n");
	}
}

int main() {
	srand(time(NULL));
	int* Numbers;
	int Size;
	printf(" Enter size array: ");
	scanf("%d", &Size);
	Numbers = (int*)malloc(sizeof(int) * Size);
	RandomArray(Numbers, Size);
	printf("\n");
	SearchMaxMin(Numbers, Size);
	free(Numbers);
	printf("\n");


	int Matrix[ROWS][COLS];
	int SumCols = 0;
	printf("\n\n");
	RandomMatrix(Matrix);
	printf("\n\n");
	for (int j = 0; j < COLS; j++) {
		for (int i = 0; i < ROWS; i++) {
			SumCols += Matrix[i][j];
		}
		printf("Col (%d): %d\n", j+1, SumCols);
		SumCols = 0;
	}
	_getch();
}