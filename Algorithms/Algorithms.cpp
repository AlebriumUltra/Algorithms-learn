#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"


void shellsort(int* items, int count)
{
	int i, j, gap, k;
	int x, a[5];
	a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;
	for (k = 0; k < 5; k++) {
		gap = a[k];
		for (i = gap; i < count; ++i) {
			x = items[i];
			for (j = i - gap; (x < items[j]) & (j >= 0); j = j - gap)
				items[j + gap] = items[j];
			items[j + gap] = x;
		}
	}
}

void qs(int* items, int left, int right) {
	int i, j;
	int x, y;
	i = left; j = right;
	x = items[(left + right) / 2];
	do {
		while ((items[i] < x) && (i < right))
			i++;
		while ((x < items[j]) && (j > left))
			j--;
		if (i <= j) {
			y = items[i];
			items[i] = items[j];
			items[j] = y;
			i++; 
			j--;
		}
	} while (i <= j);
	if (left < j) 
		qs(items, left, j);
	if (i < right) 
		qs(items, i, right);
}

void Randomized(int* items, int count) {
	for (int i = 0; i < count; i++) {
		items[i] = rand() % 30001 - 15000;
	}
}

void Reversed(int* items, int count) {
	for (int i = 0; i < count; i++) {
		items[i] = count - i;
	}
}

void Sorted(int* items, int count) {
	for (int i = 0; i < count; i++) {
		items[i] = i + 1;
	}
}

void Saw(int* items, int count) {
	Sorted(items, count / 2);
	for (int i = count / 2; i < count; i++) {
		items[i] = count - i;
	}
}

void PrintArray(int* items, int count) {
	for (int i = 0; i < count; i++) {
		printf("%d ", items[i]);
	}
}

void OutputFile(int* items, int count, float time) {
	FILE* Output;
	Output = fopen("results.txt", "");
}

int main() {
	srand(time(NULL));
	int* Array = (int*)malloc(sizeof(int) * 10000);
    Randomized(Array, 10000);
    PrintArray(Array, 10000);
	_getch();
}