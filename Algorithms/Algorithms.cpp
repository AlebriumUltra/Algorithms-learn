#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"


double shellsort(int* items, int count)
{
	clock_t start, end;
	int i, j, gap, k;
	int x, a[5];
	a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;
	start = clock();
	for (k = 0; k < 5; k++) {
		gap = a[k];
		for (i = gap; i < count; ++i) {
			x = items[i];
			for (j = i - gap; (x < items[j]) & (j >= 0); j = j - gap)
				items[j + gap] = items[j];
			items[j + gap] = x;
		}
	}
	end = clock();
	return (double)(end - start) / CLK_TCK;
}

double qs(int* items, int left, int right) {
	clock_t start, end;
	int i, j;
	int x, y;
	i = left; j = right;
	x = items[(left + right) / 2 + 100];
	start = clock();
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
	end = clock();
	return (double)(end - start) / CLK_TCK;
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

int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

int main() {
	srand(time(NULL));
	FILE* Output;
	clock_t start, end;
	char FileName[50];
	printf("Enter FileName: ");
	scanf("%s", FileName);
	int Sizes[] = { 10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000 };
	double Times[4];
	int* Array = NULL;
	int LengthSizes = sizeof(Sizes) / sizeof(int);
	Output = fopen(FileName, "w");
	fprintf(Output, "Shellsort:\n\tRandomized\tSorted\tReversed\tSaw\n");
	for (int i = 0; i < LengthSizes; i++) {
		Array = (int*)realloc(Array, Sizes[i] * sizeof(int));
		fprintf(Output, "%d\t", Sizes[i]);
		Randomized(Array, Sizes[i]);
		Times[0] = shellsort(Array, Sizes[i]);
		Times[1] = shellsort(Array, Sizes[i]);
		Reversed(Array, Sizes[i]);
		Times[2] = shellsort(Array, Sizes[i]);
		Saw(Array, Sizes[i]);
		Times[3] = shellsort(Array, Sizes[i]);
		fprintf(Output, "%lf\t\t%lf\t%lf\t%lf\n", Times[0], Times[1], Times[2], Times[3]);
	}
	fprintf(Output, "\nHandQuicksort:\n\tRandomized\tSorted\tReversed\tSaw\n");
	for (int i = 0; i < LengthSizes; i++) {
		Array = (int*)realloc(Array, Sizes[i] * sizeof(int));
		fprintf(Output, "%d\t", Sizes[i]);
		Randomized(Array, Sizes[i]);
		Times[0] = qs(Array, 0, Sizes[i] - 1);
		Times[1] = qs(Array, 0, Sizes[i] - 1);
		Reversed(Array, Sizes[i]);
		Times[2] = qs(Array, 0, Sizes[i] - 1);
		Saw(Array, Sizes[i]);
		Times[3] = qs(Array, 0, Sizes[i] - 1);
		fprintf(Output, "%lf\t\t%lf\t%lf\t%lf\n", Times[0], Times[1], Times[2], Times[3]);
	}
	fprintf(Output, "\nLibraryQuicksort:\n\tRandomized\tSorted\tReversed\tSaw\n");
	for (int i = 0; i < LengthSizes; i++) {
		Array = (int*)realloc(Array, Sizes[i] * sizeof(int));
		fprintf(Output, "%d\t", Sizes[i]);
		Randomized(Array, Sizes[i]);
		start = clock();
		qsort(Array, Sizes[i], sizeof(int), compare);
		end = clock();
		Times[0] = (double)(end - start) / CLK_TCK;
		start = clock();
		qsort(Array, Sizes[i], sizeof(int), compare);
		end = clock();
		Times[1] = (double)(end - start) / CLK_TCK;
		Reversed(Array, Sizes[i]);
		start = clock();
		qsort(Array, Sizes[i], sizeof(int), compare);
		end = clock();
		Times[2] = (double)(end - start) / CLK_TCK;
		Saw(Array, Sizes[i]);
		start = clock();
		qsort(Array, Sizes[i], sizeof(int), compare);
		end = clock();
		Times[3] = (double)(end - start) / CLK_TCK;
		fprintf(Output, "%lf\t\t%lf\t%lf\t%lf\n", Times[0], Times[1], Times[2], Times[3]);
	}
	free(Array);
	system("PAUSE");
}