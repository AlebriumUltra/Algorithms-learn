#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"
#include "Structs.h"

int** MallocMatrix(int MatrixOrder) {
	int** Matrix = (int**)malloc(sizeof(int) * MatrixOrder);
	for (int i = 0; i < MatrixOrder; i++) {
		Matrix[i] = (int*)malloc(sizeof(int) * MatrixOrder);
	}
	return Matrix;
}

int* MallocVertexes(int MatrixOrder) {
	int* Vertexes = (int*)malloc(sizeof(int) * MatrixOrder);
	for (int i = 0; i < MatrixOrder; i++) {
		Vertexes[i] = i + 1;
	}
	return Vertexes;
}

Graph* graph_create(int MatrixOrder) {
	Graph* pGraph = (Graph*)malloc(sizeof(Graph));
	pGraph->Matrix = MallocMatrix(MatrixOrder);
	pGraph->Vertexes = MallocVertexes(MatrixOrder);
	pGraph->MatrixOrder = MatrixOrder;
	pGraph->is_filled = true;
	return pGraph;
}


void graph_free(Graph* GraphG) {
	int MatrixOrder = GraphG->MatrixOrder;
	for (int i = 0; i < MatrixOrder; i++) {
		free(GraphG->Matrix[i]);
	}
	free(GraphG->Matrix);
	free(GraphG->Vertexes);
	free(GraphG);
}


void matrix_copydec(Graph* GraphG, Graph* CompGraph, int vertex) {
	int MatrixOrder = GraphG->MatrixOrder;
	if (vertex == MatrixOrder - 1) {
		for (int i = 0; i < MatrixOrder - 1; i++) {
			for (int j = 0; j < MatrixOrder - 1; j++) {
				CompGraph->Matrix[i][j] = GraphG->Matrix[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < MatrixOrder - 1; i++) {
			for (int j = 0; j < MatrixOrder - 1; j++) {
				if (j >= vertex && i < vertex) {
					CompGraph->Matrix[i][j] = GraphG->Matrix[i][j + 1];
				}
				else if (j >= vertex && i >= vertex) {
					CompGraph->Matrix[i][j] = GraphG->Matrix[i + 1][j + 1];
				}
				else if (j < vertex && i >= vertex) {
					CompGraph->Matrix[i][j] = GraphG->Matrix[i + 1][j];
				}
				else {
					CompGraph->Matrix[i][j] = GraphG->Matrix[i][j];
				}
			}
		}
		for (int i = vertex; i < MatrixOrder - 1; i++) {
			CompGraph->Vertexes[i] = i + 2;
		}
	}
}


void matrix_edgeName(Graph* GraphG, Graph* NumEdgeGraph) {
	int MatrixOrder = GraphG->MatrixOrder;
	int NumberEdge = 1;
	for (int i = 0; i < MatrixOrder; i++) {
		for (int j = 0; j < MatrixOrder; j++) {
			if ((i < j) && GraphG->Matrix[i][j] == 1) {
				NumEdgeGraph->Matrix[i][j] = NumEdgeGraph->Matrix[j][i] = NumberEdge;
				NumberEdge++;
			}
			if (i >= j && GraphG->Matrix[i][j] == 0) {
				NumEdgeGraph->Matrix[i][j] = NumEdgeGraph->Matrix[j][i] = 0;
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


void random_Graph(Graph* GraphG) {
	int MatrixOrder = GraphG->MatrixOrder;
	for(int i = 0; i < MatrixOrder; i++) {
		for (int j = 0; j < MatrixOrder; j++) {
			if (i == j) {
				GraphG->Matrix[i][j] = 0;
			}
			if (i < j) {
				GraphG->Matrix[i][j] = GraphG->Matrix[j][i] = randFunc();
			}
		}
	}
}


void matrix_print(Graph* GraphG) {
	printf("\n");
	int MatrixOrder = GraphG->MatrixOrder;
	printf("\t");
	for (int i = 0; i < MatrixOrder; i++) {
		printf(" %d\t", GraphG->Vertexes[i]);
	}
	printf("\n");
	for (int i = 0; i < MatrixOrder; i++) {
		printf("%d --->\t", GraphG->Vertexes[i]);
		for (int j = 0; j < MatrixOrder; j++) {
			printf("|%d|\t", GraphG->Matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void vertexIndentification(Graph* GraphG) {
	int u, v;
	int MatrixOrder = GraphG->MatrixOrder;
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

	for (int i = 0; i < MatrixOrder; i++) {
		GraphG->Matrix[u][i] = GraphG->Matrix[v][i] || GraphG->Matrix[u][i];
		GraphG->Matrix[i][u] = GraphG->Matrix[i][v] || GraphG->Matrix[i][u];
	}

	Graph* IndentGraph = graph_create(MatrixOrder - 1);

	matrix_copydec(GraphG, IndentGraph, v);
	matrix_print(IndentGraph);
	graph_free(IndentGraph);
}


void edgeContract(Graph* GraphG) {
	int MatrixOrder = GraphG->MatrixOrder;
	Graph* NumEdgeGraph = graph_create(MatrixOrder);
	int u, v;
	int NumberEdge;
	bool is_found = false;
	matrix_edgeName(GraphG, NumEdgeGraph);
	matrix_print(NumEdgeGraph);

	printf("Введите номер ребра: ");
	scanf("%d", &NumberEdge);
	for (int i = 0; i < MatrixOrder && is_found == false; i++) {
		for (int j = 0; j < MatrixOrder; j++) {
			if (NumEdgeGraph->Matrix[i][j] == NumberEdge) {
				u = i;
				v = j;
				GraphG->Matrix[i][j] = GraphG->Matrix[j][i] = 0;
				is_found = true;
				break;
			}
		}
	}
	
	graph_free(NumEdgeGraph);

	for (int i = 0; i < MatrixOrder; i++) {
		GraphG->Matrix[u][i] = GraphG->Matrix[v][i] || GraphG->Matrix[u][i];
		GraphG->Matrix[i][u] = GraphG->Matrix[i][v] || GraphG->Matrix[i][u];
	}

	Graph* IndentGraph = graph_create(MatrixOrder - 1);
	matrix_copydec(GraphG, IndentGraph, v);
	matrix_print(IndentGraph);
	graph_free(IndentGraph);
}


void vertexSplit(Graph* GraphG) {
	int MatrixOrder = GraphG->MatrixOrder;
	int u;
	printf("Введите вершину для расщепления: ");
	scanf("%d", &u);
	u--;

	Graph* IndentGraph = graph_create(MatrixOrder + 1);
	for (int i = 0; i < MatrixOrder; i++) {
		for (int j = 0; j < MatrixOrder; j++) {
			IndentGraph->Matrix[i][j] = GraphG->Matrix[i][j];
		}
	}
	for (int i = 0; i < MatrixOrder; i++) {
		IndentGraph->Matrix[MatrixOrder][i] = GraphG->Matrix[u][i];
		IndentGraph->Matrix[i][MatrixOrder] = GraphG->Matrix[i][u];
	}
	IndentGraph->Matrix[MatrixOrder][MatrixOrder] = 0;
	matrix_print(IndentGraph);
	graph_free(IndentGraph);
}


int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int MatrixOrder;
	printf("Введите размерность матрицы: ");
	scanf("%d", &MatrixOrder);
	Graph* GraphG1 = graph_create(MatrixOrder);
	random_Graph(GraphG1);
	matrix_print(GraphG1);
	vertexSplit(GraphG1);
	system("PAUSE");
}