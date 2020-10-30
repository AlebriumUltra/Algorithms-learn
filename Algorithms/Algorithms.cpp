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


void VertexIndentification(Graph* GraphG) {
	int u, v;
	int MatrixOrder = GraphG->MatrixOrder;
	printf("\nОтождествление вершины\n");
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


void EdgeContract(Graph* GraphG) {
	int MatrixOrder = GraphG->MatrixOrder;
	Graph* NumEdgeGraph = graph_create(MatrixOrder);
	int u, v;
	int NumberEdge;
	bool is_found = false;
	printf("\nСтягивание ребра\n");
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


void VertexSplit(Graph* GraphG) {
	int MatrixOrder = GraphG->MatrixOrder;
	int u;
	printf("\nРасщепление вершины\n");
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
		if (GraphG->Matrix[u][i] == 1) {
			if (rand() % 101 <= 40) {
				IndentGraph->Matrix[MatrixOrder][i] = 1;
				IndentGraph->Matrix[i][MatrixOrder] = 1;
				IndentGraph->Matrix[u][i] = 0;
				IndentGraph->Matrix[i][u] = 0;
			}
			else {
				IndentGraph->Matrix[MatrixOrder][i] = 0;
				IndentGraph->Matrix[i][MatrixOrder] = 0;
			}
		}
		else {
			IndentGraph->Matrix[MatrixOrder][i] = 0;
			IndentGraph->Matrix[i][MatrixOrder] = 0;
		}
	}
	IndentGraph->Matrix[MatrixOrder][MatrixOrder] = 0;
	matrix_print(IndentGraph);
	free(IndentGraph);
}

void GraphUnion(Graph* GraphG1, Graph* GraphG2) {
	printf("Объединение графов");
	int MatrixOrderMin = GraphG1->MatrixOrder;
	int MatrixOrderMax = GraphG2->MatrixOrder;
	bool is_equal = false;
	bool is_moreG1 = false;
	if (MatrixOrderMin == MatrixOrderMax) {
		is_equal = true;
	}
	else if (GraphG1->MatrixOrder > GraphG2->MatrixOrder) {
		MatrixOrderMin = GraphG2->MatrixOrder;
		MatrixOrderMax = GraphG1->MatrixOrder;
		is_moreG1 = true;
	}
	Graph* GraphG3Union = graph_create(MatrixOrderMax);
	if (is_equal) {
		for (int i = 0; i < GraphG1->MatrixOrder; i++) {
			for (int j = 0; j < GraphG1->MatrixOrder; j++) {
				GraphG3Union->Matrix[i][j] = GraphG1->Matrix[i][j] || GraphG2->Matrix[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < MatrixOrderMin; i++) {
			for (int j = 0; j < MatrixOrderMin; j++) {
				GraphG3Union->Matrix[i][j] = GraphG1->Matrix[i][j] || GraphG2->Matrix[i][j];
			}
		}
		if (is_moreG1) {
			for (int i = 0; i < MatrixOrderMax; i++) {
				for (int j = MatrixOrderMin; j < MatrixOrderMax; j++) {
					GraphG3Union->Matrix[i][j] = GraphG1->Matrix[i][j];
				}
			}
			for (int i = MatrixOrderMin; i < MatrixOrderMax; i++) {
				for (int j = 0; j < MatrixOrderMax; j++) {
					GraphG3Union->Matrix[i][j] = GraphG1->Matrix[i][j];
				}
			}
		}
		else {
			for (int i = 0; i < MatrixOrderMax; i++) {
				for (int j = MatrixOrderMin; j < MatrixOrderMax; j++) {
					GraphG3Union->Matrix[i][j] = GraphG2->Matrix[i][j];
				}
			}
			for (int i = MatrixOrderMin; i < MatrixOrderMax; i++) {
				for (int j = 0; j < MatrixOrderMax; j++) {
					GraphG3Union->Matrix[i][j] = GraphG2->Matrix[i][j];
				}
			}
		}
	}
	matrix_print(GraphG3Union);
	graph_free(GraphG3Union);
}

void GraphCross(Graph* GraphG1, Graph* GraphG2) {
	printf("Пересечение графов");
	int MatrixOrderMin = GraphG1->MatrixOrder;
	int MatrixOrderMax = GraphG2->MatrixOrder;

	if (GraphG1->MatrixOrder > GraphG2->MatrixOrder) {
		MatrixOrderMin = GraphG2->MatrixOrder;
		MatrixOrderMax = GraphG1->MatrixOrder;
	}

	Graph* GraphG3Cross = graph_create(MatrixOrderMin);
	{
		for (int i = 0; i < MatrixOrderMin; i++) {
			for (int j = 0; j < MatrixOrderMin; j++) {
				GraphG3Cross->Matrix[i][j] = GraphG1->Matrix[i][j] && GraphG2->Matrix[i][j];
			}
		}
	}
	matrix_print(GraphG3Cross);
	graph_free(GraphG3Cross);
}

void GraphSum(Graph* GraphG1, Graph* GraphG2) {
	printf("Кольцевая сумма");
	int MatrixOrderMin = GraphG1->MatrixOrder;
	int MatrixOrderMax = GraphG2->MatrixOrder;
	bool is_equal = false;
	bool is_moreG1 = false;
	if (MatrixOrderMin == MatrixOrderMax) {
		is_equal = true;
	}
	else if (GraphG1->MatrixOrder > GraphG2->MatrixOrder) {
		MatrixOrderMin = GraphG2->MatrixOrder;
		MatrixOrderMax = GraphG1->MatrixOrder;
		is_moreG1 = true;
	}
	Graph* GraphG3Sum = graph_create(MatrixOrderMax);
	if (is_equal) {
		for (int i = 0; i < GraphG1->MatrixOrder; i++) {
			for (int j = 0; j < GraphG1->MatrixOrder; j++) {
				if (GraphG1->Matrix[i][j] == 1 && GraphG2->Matrix[i][j] == 0 || GraphG1->Matrix[i][j] == 0 && GraphG2->Matrix[i][j] == 1)
					GraphG3Sum->Matrix[i][j] = 1;
				else
					GraphG3Sum->Matrix[i][j] = 0;
			}
		}
	}
	else {
		for (int i = 0; i < MatrixOrderMin; i++) {
			for (int j = 0; j < MatrixOrderMin; j++) {
				if (GraphG1->Matrix[i][j] == 1 && GraphG2->Matrix[i][j] == 0 || GraphG1->Matrix[i][j] == 0 && GraphG2->Matrix[i][j] == 1)
					GraphG3Sum->Matrix[i][j] = 1;
				else
					GraphG3Sum->Matrix[i][j] = 0;
			}
		}
		if (is_moreG1) {
			for (int i = 0; i < MatrixOrderMax; i++) {
				for (int j = MatrixOrderMin; j < MatrixOrderMax; j++) {
						GraphG3Sum->Matrix[i][j] = GraphG1->Matrix[i][j];
				}
			}
			for (int i = MatrixOrderMin; i < MatrixOrderMax; i++) {
				for (int j = 0; j < MatrixOrderMax; j++) {
						GraphG3Sum->Matrix[i][j] = GraphG1->Matrix[i][j];
				}
			}
		}
		else {
			for (int i = 0; i < MatrixOrderMax; i++) {
				for (int j = MatrixOrderMin; j < MatrixOrderMax; j++) {
					GraphG3Sum->Matrix[i][j] = GraphG2->Matrix[i][j];
				}
			}
			for (int i = MatrixOrderMin; i < MatrixOrderMax; i++) {
				for (int j = 0; j < MatrixOrderMax; j++) {
					GraphG3Sum->Matrix[i][j] = GraphG2->Matrix[i][j];
				}
			}
		}
	}
	matrix_print(GraphG3Sum);
	graph_free(GraphG3Sum);
}

void CartesianProduct(Graph* GraphG1, Graph* GraphG2) {
	printf("Декартово произведение\n");
	int matrixOrderG1 = GraphG1->MatrixOrder;
	int matrixOrderG2 = GraphG2->MatrixOrder;
	int vertexProduct = GraphG1->MatrixOrder * GraphG2->MatrixOrder;
	int u = 0, v = 0;
	Graph* GraphG3CartProd = graph_create(vertexProduct);
	for (int i = 0; i < vertexProduct; i++) {
		for (int j = 0; j < vertexProduct; j++) {
			GraphG3CartProd->Matrix[i][j] = 0;
		}
	}
	for (int i = 0; i < matrixOrderG1; i++) {
		for (int j = 0; j < matrixOrderG2; j++, u++) {
			v = 0;
			for (int x1 = 0; x1 < matrixOrderG1; x1++) {
				for (int x2 = 0; x2 < matrixOrderG2; x2++, v++) {
					if ((x1 == i && GraphG2->Matrix[x2][j]) || (x2 == j && GraphG1->Matrix[x1][i])) {
						GraphG3CartProd->Matrix[u][v] = 1;
					}
				}
			}
		}
	}
	for (int x1 = 0; x1 < matrixOrderG1; x1++) {
		for (int x2 = 0; x2 < matrixOrderG2; x2++) {
			printf("{%d%d}\t", x1 + 1, x2 + 1);
		}
	}
	printf("\n");
	for (int i = 0; i < vertexProduct; i++) {
		for (int j = 0; j < vertexProduct; j++) {
			printf("|%d|\t", GraphG3CartProd->Matrix[i][j]);
		}
		printf("\n");
	}
	
	graph_free(GraphG3CartProd);
}


int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int matrixOrderG1;
	int matrixOrderG2;
	printf("Введите размерность матрицы 1: ");
	scanf("%d", &matrixOrderG1);
	printf("Введите размерность матрицы 2: ");
	scanf("%d", &matrixOrderG2);
	Graph* GraphG1 = graph_create(matrixOrderG1);
	Graph* GraphG1temp = graph_create(matrixOrderG1);
	Graph* GraphG2 = graph_create(matrixOrderG2);
	graph_random(GraphG1);
	graph_random(GraphG2);
	printf("\nУнарные операции\n------------------------------------------");
	matrix_print(GraphG1);
	copy_graph(GraphG1, GraphG1temp);
	VertexIndentification(GraphG1temp);
	copy_graph(GraphG1, GraphG1temp);
	EdgeContract(GraphG1temp);
	copy_graph(GraphG1, GraphG1temp);
	VertexSplit(GraphG1temp);
	copy_graph(GraphG1, GraphG1temp);
	printf("Бинарные операции\n------------------------------------------\n");
	printf("Матрица 1");
	matrix_print(GraphG1);
	printf("Матрица 2");
	matrix_print(GraphG2);
	GraphUnion(GraphG1, GraphG2);
	GraphCross(GraphG1, GraphG2);
	GraphSum(GraphG1, GraphG2);
	CartesianProduct(GraphG1, GraphG2);
	system("PAUSE");
}