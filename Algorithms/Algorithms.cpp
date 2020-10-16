#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"
#include "Structs.h"

int** matrix_malloc(int MatrixOrder) {
	int** Matrix = (int**)malloc(sizeof(int) * MatrixOrder);
	for (int i = 0; i < MatrixOrder; i++) {
		Matrix[i] = (int*)malloc(sizeof(int) * MatrixOrder);
	}
	return Matrix;
}

int* vertexes_malloc(int MatrixOrder) {
	int* Vertexes = (int*)malloc(sizeof(int) * MatrixOrder);
	for (int i = 0; i < MatrixOrder; i++) {
		Vertexes[i] = i + 1;
	}
	return Vertexes;
}

Graph* graph_create(int MatrixOrder) {
	Graph* pGraph = (Graph*)malloc(sizeof(Graph));
	pGraph->Matrix = matrix_malloc(MatrixOrder);
	pGraph->Vertexes = vertexes_malloc(MatrixOrder);
	pGraph->MatrixOrder = MatrixOrder;
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

void copy_graph(Graph* GraphG, Graph* GraphTemp) {
	for (int i = 0; i < GraphG->MatrixOrder; i++) {
		for (int j = i; j < GraphG->MatrixOrder; j++) {
			if (i == j) {
				GraphTemp->Matrix[i][j] = 0;
			}
			else {
				GraphTemp->Matrix[i][j] = GraphTemp->Matrix[j][i] = GraphG->Matrix[i][j];
			}
		}
	}
	for (int i = 0; i < GraphG->MatrixOrder; i++) {
		GraphTemp->Vertexes[i] = i + 1;
	} 
}

int randFunc() {
	if (rand() % 101 <= 50) {
		return 1;
	}
	else {
		return 0;
	}
}

void graph_random(Graph* GraphG) {
	int MatrixOrder = GraphG->MatrixOrder;
	for (int i = 0; i < MatrixOrder; i++) {
		for (int j = i; j < MatrixOrder; j++) {
			if (i == j) {
				GraphG->Matrix[i][j] = 0;
			}
			else {
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
			if (i == j && GraphG->Matrix[i][j] != 0) {
				NumEdgeGraph->Matrix[i][j] = NumberEdge;
				NumberEdge++;
			}
		}
	}
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
	free(IndentGraph);
}


void edgeContract(Graph* GraphG) {
	int MatrixOrder = GraphG->MatrixOrder;
	Graph* NumEdgeGraph = graph_create(MatrixOrder);
	int u, v;
	int NumberEdge;
	bool is_found = false;
	printf("Матрица с номерами рёбер:\n ");
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
	free(IndentGraph);
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
	free(IndentGraph);
}

void graphUnion(Graph* GraphG1, Graph* GraphG2) {
	printf("Объединение графов");
	int MatrixOrderG1 = GraphG1->MatrixOrder;
	int MatrixOrderG2 = GraphG2->MatrixOrder;
	Graph* GraphG3Union = graph_create(MatrixOrderG1);
	for (int i = 0; i < MatrixOrderG1; i++) {
		for (int j = 0; j < MatrixOrderG1; j++) {
			GraphG3Union->Matrix[i][j] = GraphG1->Matrix[i][j] || GraphG2->Matrix[i][j];
 		}
	}
	matrix_print(GraphG3Union);
}

void graphCross(Graph* GraphG1, Graph* GraphG2) {
	printf("Пересечение графов");
	int MatrixOrderG1 = GraphG1->MatrixOrder;
	int MatrixOrderG2 = GraphG2->MatrixOrder;
	Graph* GraphG3Cross = graph_create(MatrixOrderG1);
	for (int i = 0; i < MatrixOrderG1; i++) {
		for (int j = 0; j < MatrixOrderG1; j++) {
			GraphG3Cross->Matrix[i][j] = GraphG1->Matrix[i][j] && GraphG2->Matrix[i][j];
		}
	}
	matrix_print(GraphG3Cross);
}

void graphSum(Graph* GraphG1, Graph* GraphG2) {
	printf("Кольцевая сумма графов");
	int MatrixOrderG1 = GraphG1->MatrixOrder;
	int MatrixOrderG2 = GraphG2->MatrixOrder;
	int MatrixOrderG3 = GraphG1->MatrixOrder;
	int* RightRaw = (int*)malloc(sizeof(int) * MatrixOrderG1);
	bool is_same;
	for (int i = 0, int k = 0; i < MatrixOrderG1; i++) {
		is_same = true;
		for (int j = 0; j < MatrixOrderG1; j++) {
			if (GraphG1->Matrix[i][j] != GraphG2->Matrix[i][j]) {
				is_same = false;
			}
		}
		if (is_same) {
			MatrixOrderG3--;
			RightRaw[k] = i;
			k++;
		}
	}
	RightRaw = (int*)realloc(RightRaw, sizeof(int) * MatrixOrderG3);
	Graph* GraphG3Sum = graph_create(MatrixOrderG3);
	for (int i = 0; i < MatrixOrderG3; i++) {
		GraphG3Sum->Vertexes[i] = RightRaw[i] + 1;
	}
	matrix_print(GraphG3Sum);
}

int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int MatrixOrder;
	printf("Введите размерность матрицы: ");
	scanf("%d", &MatrixOrder);
	Graph* GraphG1 = graph_create(MatrixOrder);
	Graph* GraphG1temp = graph_create(MatrixOrder);
	Graph* GraphG2 = graph_create(MatrixOrder);
	Graph* GraphG2temp = graph_create(MatrixOrder);
	graph_random(GraphG1);
	graph_random(GraphG2);
	matrix_print(GraphG1);
	copy_graph(GraphG1, GraphG1temp);
	vertexIndentification(GraphG1temp);
	copy_graph(GraphG1, GraphG1temp);
	edgeContract(GraphG1temp);
	copy_graph(GraphG1, GraphG1temp);
	vertexSplit(GraphG1temp);
	copy_graph(GraphG1, GraphG1temp);
	copy_graph(GraphG2, GraphG2temp);
	matrix_print(GraphG1);
	matrix_print(GraphG2);
	graphUnion(GraphG1temp, GraphG2temp);
	copy_graph(GraphG1, GraphG1temp);
	copy_graph(GraphG2, GraphG2temp);
	graphCross(GraphG1temp, GraphG2temp);
	system("PAUSE");
}