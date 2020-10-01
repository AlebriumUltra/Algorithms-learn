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

void CopiedArray(int* Array1, int* Array2, int count) {
	for (int i = 0; i < count; i++) {
		Array1[i] = Array2[i];
	}
}
int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

int main() {
	srand(time(NULL));
	FILE* Output;
	char FileName[50];
	printf("Enter FileName: ");
	scanf("%s", FileName);
	int Sizes[] = { 50000, 100000, 150000, 200000, 250000 };
	double start, end;
	double TimesShell[4];
	double TimesQS[4];
	double TimesLQS[4];
	int LengthSizes = sizeof(Sizes) / sizeof(int);
	int* RandomArray = NULL;
	int* TempArray = NULL;
	Output = fopen(FileName, "w");
	for (int i = 0; i < LengthSizes; i++) {
		RandomArray = (int*)realloc(RandomArray, sizeof(int) * Sizes[i]);
		TempArray = (int*)realloc(TempArray, sizeof(int) * Sizes[i]);
		Randomized(RandomArray, Sizes[i]);
		CopiedArray(TempArray, RandomArray, Sizes[i]);

		TimesShell[0] = shellsort(TempArray, Sizes[i]);
		Sorted(TempArray, Sizes[i]);
		TimesShell[1] = shellsort(TempArray, Sizes[i]);
		Reversed(TempArray, Sizes[i]);
		TimesShell[2] = shellsort(TempArray, Sizes[i]);
		Saw(TempArray, Sizes[i]);
		TimesShell[3] = shellsort(TempArray, Sizes[i]);


		CopiedArray(TempArray, RandomArray, Sizes[i]);
		TimesQS[0] = qs(TempArray, 0, Sizes[i] - 1);
		Sorted(TempArray, Sizes[i]);
		TimesQS[1] = qs(TempArray, 0, Sizes[i] - 1);
		Reversed(TempArray, Sizes[i]);
		TimesQS[2] = qs(TempArray, 0, Sizes[i] - 1);
		Saw(TempArray, Sizes[i]);
		TimesQS[3] = qs(TempArray, 0, Sizes[i] - 1);


		CopiedArray(TempArray, RandomArray, Sizes[i]);
		start = clock();
		qsort(TempArray, Sizes[i], sizeof(int), compare);
		end = clock();
		TimesLQS[0] = (end - start) / CLK_TCK;
		Sorted(TempArray, Sizes[i]);
		start = clock();
		qsort(TempArray, Sizes[i], sizeof(int), compare);
		end = clock();
		TimesLQS[1] = (end - start) / CLK_TCK;
		Reversed(TempArray, Sizes[i]);
		start = clock();
		qsort(TempArray, Sizes[i], sizeof(int), compare);
		end = clock();
		TimesLQS[2] = (end - start) / CLK_TCK;
		Saw(TempArray, Sizes[i]);
		start = clock();
		qsort(TempArray, Sizes[i], sizeof(int), compare);
		end = clock();
		TimesLQS[3] = (end - start) / CLK_TCK;

		fprintf(Output, "SizeArray:\t%d\n\n", Sizes[i]);
		fprintf(Output, "ShellSort:\nRandomTime:\t%lf\nSortedTime:\t%lf\nReversedTime:\t%lf\nSawTime:\t%lf\n\n", TimesShell[0], TimesShell[1], TimesShell[2], TimesShell[3]);
		fprintf(Output, "QS:\nRandomTime:\t%lf\nSortedTime:\t%lf\nReversedTime:\t%lf\nSawTime:\t%lf\n\n", TimesQS[0], TimesQS[1], TimesQS[2], TimesQS[3]);
		fprintf(Output, "LQS:\nRandomTime:\t%lf\nSortedTime:\t%lf\nReversedTime:\t%lf\nSawTime:\t%lf\n========================|\n\n", TimesLQS[0], TimesLQS[1], TimesLQS[2], TimesLQS[3]);
	}
	fclose(Output);
	free(RandomArray);
	free(TempArray);
	system("PAUSE");
}