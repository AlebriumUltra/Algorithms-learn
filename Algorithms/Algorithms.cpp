#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"

int** MallocMatrix(int Order) {
	int** Matrix = (int**)malloc(sizeof(int) * Order);
	for (int i = 0; i < Order; i++) {
		Matrix[i] = (int*)malloc(sizeof(int) * Order);
	}
	return Matrix;
}


int RandReturns(){
	int RandomNumber = rand() % 101;
	if (RandomNumber <= 45) {
		return 1;
	}
	else {
		return 0;
	}
}


void RandomComGraphs(int** Matrix, int Order) {
	for(int i = 0; i < Order; i++) {
		for (int j = 0; j < Order; j++) {
			if (i == j) {
				Matrix[i][j] = 0;
			}
			if (i > j) {
				Matrix[i][j] = Matrix[j][i] = RandReturns();
			}
		}
	}
}

void PrintMatrix(int** Matrix, int Order) {
	for (int i = 0; i < Order; i++) {
		for (int j = 0; j < Order; j++) {
			printf("%d ", Matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void VertexIdentification(int** Matrix, int Order) {
	int Vertex, Vertex2;
	printf("Введите вершину 1: ");
	scanf("%d", &Vertex);
	printf("Введите вершину 2: ");
	scanf("%d", &Vertex2);
	Vertex--;
	Vertex2--;
	if (Vertex > Vertex2) {
		int temp = Vertex2;
		Vertex2 = Vertex;
		Vertex = temp;
	}
	for (int i = 0; i < Order; i++) {
		Matrix[Vertex][i] = Matrix[Vertex2][i] || Matrix[Vertex][i];
		Matrix[i][Vertex] = Matrix[i][Vertex2] || Matrix[i][Vertex];
	}
	int** EditMatrix = (int**)malloc(sizeof(int) * (Order - 1));
	for (int i = 0; i < Order - 1; i++) {
		EditMatrix[i] = (int*)malloc(sizeof(int) * (Order - 1));
	}
	if (Vertex2 == (Order - 1)) {
		for (int i = 0; i < Order - 1; i++) {
			for (int j = 0; j < Order - 1; j++) {
				EditMatrix[i][j] = Matrix[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < Order - 1; i++) {
			for (int j = 0; j < Order - 1; j++) {
				if (j >= Vertex2 && i < Vertex2) {
					EditMatrix[i][j] = Matrix[i][j + 1];
				}
				else if (j >= Vertex2 && i >= Vertex2) {
					EditMatrix[i][j] = Matrix[i+1][j+1];
				}
				else if (j < Vertex2 && i >= Vertex2) {
					EditMatrix[i][j] = Matrix[i + 1][j];
				}
				else {
					EditMatrix[i][j] = Matrix[i][j];
				}
			}
		}
	}
	PrintMatrix(EditMatrix, Order - 1);
}



int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int** AdjacenciesM1 = NULL;
	int** AdjacenciesM2 = NULL;
	int Order;
	printf("Введите порядок матрицы(>3): ");
	scanf("%d", &Order);
	AdjacenciesM1 = MallocMatrix(Order);
	AdjacenciesM2 = MallocMatrix(Order);
	RandomComGraphs(AdjacenciesM1, Order);
	RandomComGraphs(AdjacenciesM2, Order);
	PrintMatrix(AdjacenciesM1, Order);
	VertexIdentification(AdjacenciesM1, Order);
	system("PAUSE");
}