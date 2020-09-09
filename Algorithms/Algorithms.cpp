#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"


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
	_getch();
}