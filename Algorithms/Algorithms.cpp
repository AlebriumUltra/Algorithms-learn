#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"

typedef struct Graph {
	int** matrix;
	int* vertexes;
	int matrix_order;
};

typedef struct Node {
	int vertex;
	Node* next;
};

typedef struct Lists {
	int num_vertexes;
	Node** head;
};

int** MatrixMalloc(int matrix_order) {
	int** Matrix = (int**)malloc(sizeof(int) * matrix_order);
	for (int i = 0; i < matrix_order; i++) {
		Matrix[i] = (int*)malloc(sizeof(int) * matrix_order);
	}
	return Matrix;
}

int* VertexesMalloc(int matrix_order) {
	int* Vertexes = (int*)malloc(sizeof(int) * matrix_order);
	for (int i = 0; i < matrix_order; i++) {
		Vertexes[i] = i + 1;
	}
	return Vertexes;
}

Graph* GraphCreate(int matrix_order) {
	Graph* pGraph = (Graph*)malloc(sizeof(Graph));
	pGraph->matrix = MatrixMalloc(matrix_order);
	pGraph->vertexes = VertexesMalloc(matrix_order);
	pGraph->matrix_order = matrix_order;
	return pGraph;
}

int* ArrayCreate(int num_vertexes) {
	int* Array = (int*)malloc(sizeof(int) * num_vertexes);
	return Array;
}

void DistanceArrayRefresh(int* distance_array, int num_vertexes) {
	for (int i = 0; i < num_vertexes; i++) {
		distance_array[i] = -1;
	}
}

void VisitedArrayRefresh(int* visited_array, int num_vertexes) {
	for (int i = 0; i < num_vertexes; i++) {
		visited_array[i] = 0;
	}
}

void GraphFree(Graph* GraphG) {
	int MatrixOrder = GraphG->matrix_order;
	for (int i = 0; i < MatrixOrder; i++) {
		free(GraphG->matrix[i]);
	}
	free(GraphG->matrix);
	free(GraphG->vertexes);
	free(GraphG);
}

int GetAdj() {
	if (rand() % 101 <= 30) {
		return 1;
	}
	else {
		return 0;
	}
}

void GraphUndirectUnweight(Graph* GraphG) {
	int matrix_order = GraphG->matrix_order;
	for (int i = 0; i < matrix_order; i++) {
		for (int j = i; j < matrix_order; j++) {
			if (i == j) {
				GraphG->matrix[i][j] = 0;
			}
			else {
				GraphG->matrix[i][j] = GraphG->matrix[j][i] = GetAdj();
			}
		}
	}
}

void GraphUndirectWeight(Graph* GraphG) {
	int matrix_order = GraphG->matrix_order;
	for (int i = 0; i < matrix_order; i++) {
		for (int j = i; j < matrix_order; j++) {
			if (i == j)
				GraphG->matrix[i][j] = 0;
			else if (GetAdj())
				GraphG->matrix[i][j] = GraphG->matrix[j][i] = rand() % 10;
			else
				GraphG->matrix[i][j] = GraphG->matrix[j][i] = 0;
		}
	}
}

void GraphDirectWeight(Graph* GraphG) {
	int matrix_order = GraphG->matrix_order;
	for (int i = 0; i < matrix_order; i++) {
		for (int j = i; j < matrix_order; j++) {
			if (i == j)
				GraphG->matrix[i][j] = 0;
			else if (GetAdj()) {
				GraphG->matrix[i][j] = rand() % 10;
				GraphG->matrix[j][i] = 0;
			}
			else
				GraphG->matrix[i][j] = GraphG->matrix[j][i] = 0;
		}
	}
}

void GraphDirectUnweight(Graph* GraphG) {
	int matrix_order = GraphG->matrix_order;
	for (int i = 0; i < matrix_order; i++) {
		for (int j = i; j < matrix_order; j++) {
			if (i == j)
				GraphG->matrix[i][j] = 0;
			else if (GetAdj()) {
				GraphG->matrix[i][j] = 1;
				GraphG->matrix[j][i] = 0;
			}
			else
				GraphG->matrix[i][j] = GraphG->matrix[j][i] = 0;
		}
	}
}

void MatrixPrint(Graph* GraphG) {
	printf("\n");
	int matrix_order = GraphG->matrix_order;
	printf("\t");
	for (int i = 0; i < matrix_order; i++) {
		printf(" %d\t", GraphG->vertexes[i]);
	}
	printf("\n");
	for (int i = 0; i < matrix_order; i++) {
		printf("%d --->\t", GraphG->vertexes[i]);
		for (int j = 0; j < matrix_order; j++) {
			printf("|%d|\t", GraphG->matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void ArrayPrint(int* array, int size) {
	printf("\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
}

Node* NodeCreate(int vertex) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->vertex = vertex;
	newNode->next = NULL;
	return newNode;
}

Lists* ListsCreate(int num_vertexes) {
	Lists* list = (Lists*)malloc(sizeof(struct Lists));
	list->num_vertexes = num_vertexes;
	list->head = (Node * *)malloc(sizeof(struct Node*) * num_vertexes);
	for (int i = 0; i < num_vertexes; i++) {
		list->head[i] = NULL;
	}
	return list;
}

void ListsDelete(Lists* list) {
	for (int i = 0; i < list->num_vertexes; i++) {
		while (list->head[i] != NULL) {
			Node* prevNode = list->head[i];
			list->head[i] = list->head[i]->next;
			free(prevNode);
		}
	}
	free(list->head);
	free(list);
}


void AddFirst(Lists* list, Node* newNode, int vertex) {
	newNode->next = list->head[vertex];
	list->head[vertex] = newNode;
}

void AddAfter(Node* prevNode, Node* newNode) {
	newNode->next = prevNode->next;
	prevNode->next = newNode;
}


void AddLast(Lists* list, Node* newNode, int vertex) {
	Node* current = list->head[vertex];
	if (current == NULL) {
		AddFirst(list, newNode, vertex);
		return;
	}
	while (current->next) {
		current = current->next;
	}
	AddAfter(current, newNode);
}

void TransMatrixInList(Graph* graph, Lists* list) {
	int matrix_order = graph->matrix_order;
	for (int i = 0; i < matrix_order; i++) {
		for (int j = 0; j < matrix_order; j++) {
			if (graph->matrix[i][j] == 1) {
				Node* newNode = NodeCreate(j);
				AddLast(list, newNode, i);
			}
		}
	}
}

void ListsPrint(Lists* list) {
	printf("\n");
	printf("\nСписок смежности");
	printf("\n");
	Node* current;
	for (int i = 0; i < list->num_vertexes; i++) {
		printf("%d", i + 1);
		current = list->head[i];
		while (current != NULL) {
			printf("->%d", current->vertex + 1);
			current = current->next;
		}
		printf("\n");
	}
}

void BFSD(Graph* graph, int* dist, int start_vertex) {
	std::queue<int>Q;
	int num_vertexes = graph->matrix_order;
	dist[start_vertex] = 0;
	Q.push(start_vertex);
	int current_vertex;
	while (!Q.empty()) {
		current_vertex = Q.front();
		Q.pop();
		printf("%2d", current_vertex + 1);
		for (int i = 0; i < num_vertexes; i++) {
			if (graph->matrix[current_vertex][i] && dist[i] == -1) {
				Q.push(i);
				dist[i] = dist[current_vertex] + graph->matrix[current_vertex][i];
			}
		}
	} 
}


int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	const char PROGRAMinfo[] = "--info";
	const char UNDIRECTgraph[] = "-ud";
	const char DIRECTgraph[] = "-d"; // Это лучше как-то объединить
	const char UNWEIGHTgraph[] = "-uw";
	const char WEIGHTgraph[] = "-w";
	const char COUNTarg = 3;

	if (argc > 1 && argc != COUNTarg) {
		if (strcmp(argv[1], PROGRAMinfo) == 0) {
			printf("\n");
			printf("Программа для вычисления расстояний в графе\n");
			printf("Доступные аргументы: \n");
			printf("Неориентированный граф:  ");
			puts(UNDIRECTgraph);
			printf("Ориентированный граф: ");
			puts(DIRECTgraph);
			printf("Невзвешенный граф: ");
			puts(UNWEIGHTgraph);
			printf("Взвешенный граф: ");
			puts(WEIGHTgraph);
			printf("\n");
			printf("Пример введения параметров для неориентированного взвешенного графа\n");
			printf("*.exe -UD -W");
			printf("\n");
			return 0;
		}
	}

	if (argc == COUNTarg) {

		if (strcmp(argv[1], UNDIRECTgraph) == 0 && strcmp(argv[2], UNWEIGHTgraph) == 0 || strcmp(argv[2], UNDIRECTgraph) == 0 && strcmp(argv[1], UNWEIGHTgraph) == 0) {
			printf("\n");
			printf("Свойства графа: неориентированный, невзвешенный\n");
			int graph_order;
			printf("Введите порядок графа(количество вершин): ");
			scanf("%d", &graph_order);
			Graph* graph = GraphCreate(graph_order);
			GraphUndirectUnweight(graph);
			printf("Представление графа в виде матрицы смежности");
			MatrixPrint(graph);
			int* distance_array = ArrayCreate(graph_order);
			int start_vertex;
			DistanceArrayRefresh(distance_array, graph_order);
			printf("\n");
			printf("Введите вершину для обхода и поиска расстояний: ");
			scanf("%d", &start_vertex);
			start_vertex--;
			printf("Осуществление обхода...");
			printf("\n");
			BFSD(graph, distance_array, start_vertex);
			printf("\n");
			printf("Расстояния от вершины %d до остальных\n", start_vertex + 1);
			ArrayPrint(distance_array, graph_order);
			printf("\n");
			return 0;
		}
		if (strcmp(argv[1], DIRECTgraph) == 0 && strcmp(argv[2], UNWEIGHTgraph) == 0 || strcmp(argv[2], DIRECTgraph) == 0 && strcmp(argv[1], UNWEIGHTgraph) == 0) {
			printf("\n");
			printf("Свойства графа: ориентированный, невзвешенный\n");
			int graph_order;
			printf("Введите порядок графа(количество вершин): ");
			scanf("%d", &graph_order);
			Graph* graph = GraphCreate(graph_order);
			GraphDirectUnweight(graph);
			printf("Представление графа в виде матрицы смежности");
			MatrixPrint(graph);
			int* distance_array = ArrayCreate(graph_order);
			int start_vertex;
			DistanceArrayRefresh(distance_array, graph_order);
			printf("\n");
			printf("Введите вершину для обхода и поиска расстояний: ");
			scanf("%d", &start_vertex);
			start_vertex--;
			printf("Осуществление обхода...");
			printf("\n");
			BFSD(graph, distance_array, start_vertex);
			printf("\n");
			printf("Расстояния от вершины %d до остальных\n", start_vertex + 1);
			ArrayPrint(distance_array, graph_order);
			printf("\n");
			return 0;
		}
		if (strcmp(argv[1], UNDIRECTgraph) == 0 && strcmp(argv[2], WEIGHTgraph) == 0 || strcmp(argv[2], UNDIRECTgraph) == 0 && strcmp(argv[1], WEIGHTgraph) == 0)  {
			printf("\n");
			printf("Свойства графа: неориентированный, взвешенный\n");
			int graph_order;
			printf("Введите порядок графа(количество вершин): ");
			scanf("%d", &graph_order);
			Graph* graph = GraphCreate(graph_order);
			GraphUndirectWeight(graph);
			printf("Представление графа в виде матрицы смежности");
			MatrixPrint(graph);
			int* distance_array = ArrayCreate(graph_order);
			int start_vertex;
			DistanceArrayRefresh(distance_array, graph_order);
			printf("\n");
			printf("Введите вершину для обхода и поиска расстояний: ");
			scanf("%d", &start_vertex);
			start_vertex--;
			printf("Осуществление обхода...");
			printf("\n");
			BFSD(graph, distance_array, start_vertex);
			printf("\n");
			printf("Расстояния от вершины %d до остальных\n", start_vertex + 1);
			ArrayPrint(distance_array, graph_order);
			printf("\n");
			return 0;
		}
		if (strcmp(argv[1], DIRECTgraph) == 0 && strcmp(argv[2], WEIGHTgraph) == 0 || strcmp(argv[2], DIRECTgraph) == 0 && strcmp(argv[1], WEIGHTgraph) == 0) {
			printf("\n");
			printf("Свойства графа: ориентированный, взвешенный\n");
			int graph_order;
			printf("Введите порядок графа(количество вершин): ");
			scanf("%d", &graph_order);
			Graph* graph = GraphCreate(graph_order);
			GraphUndirectWeight(graph);
			printf("Представление графа в виде матрицы смежности");
			MatrixPrint(graph);
			int* distance_array = ArrayCreate(graph_order);
			int start_vertex;
			DistanceArrayRefresh(distance_array, graph_order);
			printf("\n");
			printf("Введите вершину для обхода и поиска расстояний: ");
			scanf("%d", &start_vertex);
			start_vertex--;
			printf("Осуществление обхода...");
			printf("\n");
			BFSD(graph, distance_array, start_vertex);
			printf("\n");
			printf("Расстояния от вершины %d до остальных\n", start_vertex + 1);
			ArrayPrint(distance_array, graph_order);
			printf("\n");
			return 0;
		}
		else {
			printf("Введённые аргументы неверны!\n");
			return 1;
		}
	}
	else {
	printf("Введено неправильное количество аргументов! Для просмотра доступных аргументов введите *.exe --info");
	return 1;
	}
}