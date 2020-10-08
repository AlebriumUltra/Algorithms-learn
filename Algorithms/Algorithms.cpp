#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"

int** matrix_create(int Order) {
	int** Matrix = (int**)malloc(sizeof(int) * Order);
	for (int i = 0; i < Order; i++) {
		Matrix[i] = (int*)malloc(sizeof(int) * Order);
	}
	return Matrix;
}


void matrix_free(int** Matrix, int Order) {
	for (int i = 0; i < Order; i++) {
		free(Matrix[i]);
	}
	free(Matrix);
}


void matrix_copydec(int** Matrix, int** CopyMatrix, int vertex, int Order) {
	if (vertex == (Order - 1)) {
		for (int i = 0; i < Order - 1; i++) {
			for (int j = 0; j < Order - 1; j++) {
				CopyMatrix[i][j] = Matrix[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < Order - 1; i++) {
			for (int j = 0; j < Order - 1; j++) {
				if (j >= vertex && i < vertex) {
					CopyMatrix[i][j] = Matrix[i][j + 1];
				}
				else if (j >= vertex && i >= vertex) {
					CopyMatrix[i][j] = Matrix[i + 1][j + 1];
				}
				else if (j < vertex && i >= vertex) {
					CopyMatrix[i][j] = Matrix[i + 1][j];
				}
				else {
					CopyMatrix[i][j] = Matrix[i][j];
				}
			}
		}
	}
}


void matrix_edgeName(int** Matrix, int** EdgeMatrix, int Order) {
	int NumberEdge = 1;
	for (int i = 0; i < Order; i++) {
		for (int j = 0; j < Order; j++) {
			if ((i < j) && Matrix[i][j] == 1) {
				EdgeMatrix[i][j] = EdgeMatrix[j][i] = NumberEdge;
				NumberEdge++;
			}
			if (i >= j && Matrix[i][j] == 0) {
				EdgeMatrix[i][j] = EdgeMatrix[j][i] = 0;
			}
		}
	}
}


int randFunc(){
	int RandomNumber = rand() % 101;
	if (RandomNumber <= 45) {
		return 1;
	}
	else {
		return 0;
	}
}


void random_Graph(int** Matrix, int Order) {
	for(int i = 0; i < Order; i++) {
		for (int j = 0; j < Order; j++) {
			if (i == j) {
				Matrix[i][j] = 0;
			}
			if (i < j) {
				Matrix[i][j] = Matrix[j][i] = randFunc();
			}
		}
	}
}


void matrix_print(int** Matrix, int Order) {
	for (int i = 0; i < Order; i++) {
		for (int j = 0; j < Order; j++) {
			printf("%d\t", Matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void vertexIndentification(int** Matrix, int Order) {
	int u, v;
	printf("Введите вершину 1: ");
	scanf("%d", &u);
	printf("Введите вершину 2: ");
	scanf("%d", &v);
	u--;
	v--;

	if (u > v) {
		int temp = v;
		v = u;
		u = temp;
	}

	for (int i = 0; i < Order; i++) {
		Matrix[u][i] = Matrix[v][i] || Matrix[u][i];
		Matrix[i][u] = Matrix[i][v] || Matrix[i][u];
	}

	int** EditMatrix = matrix_create(Order - 1);

	matrix_copydec(Matrix, EditMatrix, v, Order);
	matrix_print(EditMatrix, Order - 1);
	matrix_free(EditMatrix, Order - 1);
}


void edgeContract(int** Matrix, int Order) {

	int** EdgeMatrix = matrix_create(Order);
	int u, v;
	int NumberEdge = 1;

	matrix_edgeName(Matrix, EdgeMatrix, Order);
	matrix_print(EdgeMatrix, Order);

	printf("Введите номер ребра: ");
	scanf("%d", &NumberEdge);
	for (int i = 0; i < Order; i++) {
		for (int j = 0; j < Order; j++) {
			if (EdgeMatrix[i][j] == NumberEdge) {
				u = i;
				v = j;
				Matrix[i][j] = Matrix[j][i] = 0;
			}
		}
	}
	
	matrix_free(EdgeMatrix, Order);

	for (int i = 0; i < Order; i++) {
		Matrix[u][i] = Matrix[v][i] || Matrix[u][i];
		Matrix[i][u] = Matrix[i][v] || Matrix[i][u];
	}

	int** EditMatrix = matrix_create(Order - 1);

	matrix_copydec(Matrix, EditMatrix, v, Order);
	matrix_print(EditMatrix, Order - 1);
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
	AdjacenciesM1 = matrix_create(Order);
	AdjacenciesM2 = matrix_create(Order);
	random_Graph(AdjacenciesM1, Order);
	random_Graph(AdjacenciesM2, Order);
	matrix_print(AdjacenciesM1, Order);
	edgeContract(AdjacenciesM1, Order);
	system("PAUSE");
}