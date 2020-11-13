#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"

typedef struct Graph {
	int** Matrix;
	int* Vertexes;
	int MatrixOrder;
};

typedef struct Node {
	int vertex;
	Node* next;
};

typedef struct Lists {
	int numVertexes;
	Node** head;
};


Node* NodeCreate(int vertex);
void AddLastQ(int vertex);
void PopNodeQ();
Node* head = NULL;
Node* tail = NULL;

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

int* create_visitedArray(int MatrixOrder) {
	int* Array = (int*)malloc(sizeof(int) * MatrixOrder);
	for (int i = 0; i < MatrixOrder; i++) {
		Array[i] = 0;
	}
	return Array;
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

int randFunc() {
	if (rand() % 101 <= 30) {
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

void clear_visited(int* visitedArray, int size) {
	for (int i = 0; i < size; i++) {
		visitedArray[i] = 0;
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

Node* NodeCreate(int vertex) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->vertex = vertex;
	newNode->next = NULL;
	return newNode;
}

Lists* ListsCreate(int numVertexes) {
	Lists* list = (Lists*)malloc(sizeof(struct Lists));
	list->numVertexes = numVertexes;
	list->head = (Node * *)malloc(sizeof(struct Node*) * numVertexes);
	for (int i = 0; i < numVertexes; i++) {
		list->head[i] = NULL;
	}
	return list;
}


void AddLastQ(int vertex) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->vertex = vertex;
	newNode->next = NULL;
	if (head == NULL) {
		head = newNode;
		tail = newNode;
		return;
	}
	tail->next = newNode;
	tail = newNode;
}

void AddLast(Node** head, Node* newNode) {
	Node* current = *head;
	if (*head == NULL) {
		newNode->next = *head;
		*head = newNode;
		return;
	}
	while (current->next) {
		current = current->next;
	}
	newNode->next = current->next;
	current->next = newNode;
}

void PrintList(Lists* list) {
	printf("\n");
	printf("\nСписок смежности");
	printf("\n");
	Node* current;
	for (int i = 0; i < list->numVertexes; i++) {
		printf("%d", i + 1);
		current = list->head[i];
		while (current != NULL) {
			printf("->%d", current->vertex + 1);
			current = current->next;
		}
		printf("\n");
	}
}

void TransMatrixInList(Graph* graph, Lists* list) {
	int MatrixOrder = graph->MatrixOrder;
	for (int i = 0; i < MatrixOrder; i++) {
		for (int j = 0; j < MatrixOrder; j++) {
			if (graph->Matrix[i][j] == 1) {
				Node* newNode = NodeCreate(j);
				AddLast(&list->head[i], newNode);
			}
		}
	}
}

void PopNodeQ() {
	Node* headOld = head;
	head = head->next;
	free(headOld);
}



double BFSwithoutQ(Graph* graph, int vertex, int* visitedArray) {
	clock_t start, end;
	start = clock();
	AddLastQ(vertex);
	visitedArray[vertex] = 1;
	while (head != NULL) {
		vertex = head->vertex;
		PopNodeQ();
		for (int i = 0; i < graph->MatrixOrder; i++) {
			if (graph->Matrix[vertex][i] == 1 && visitedArray[i] == 0) {
				AddLastQ(i);
				visitedArray[i] = 1;
			}
		}
	}
	end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC;
}

double BFS(Graph* graph, int vertex, int* visitedArray) {
	clock_t start, end;
	std::queue <int> Q;
	start = clock();
	Q.push(vertex);
	visitedArray[vertex] = 1;
	while (!Q.empty()) {
		vertex = Q.front();
		Q.pop();
		for (int i = 0; i < graph->MatrixOrder; i++) {
			if (graph->Matrix[vertex][i] == 1 && visitedArray[i] == 0) {
				Q.push(i);
				visitedArray[i] = 1;
			}
		}
	}
	end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC;
}

void BFSinLists(Lists* list, int vertex, int* visitedArray) {
	std::queue <int> Q;
	Q.push(vertex);
	visitedArray[vertex] = 1;
	while (!Q.empty()) {
		vertex = Q.front();
		printf("%d", vertex + 1);
		Q.pop();
		Node* current = list->head[vertex];
		while (current) {
			if (visitedArray[current->vertex] == 0) {
				Q.push(current->vertex);
				visitedArray[current->vertex] = 1;
			}
			current = current->next;
		}
	}
}

void ListsDelete(Lists* list) {
	for (int i = 0; i < list->numVertexes; i++) {
		while (list->head[i] != NULL) {
			Node* prevNode = list->head[i];
			list->head[i] = list->head[i]->next;
			free(prevNode);
		}
	}
	free(list->head);
	free(list);
}

int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	int MatrixOrder;
	double TimeQue = 0, TimeList = 0;
	printf("Enter matrix order: ");
	scanf("%d", &MatrixOrder);
	Graph* graph = graph_create(MatrixOrder);
	int* visitedArray = create_visitedArray(MatrixOrder);
	graph_random(graph);
	matrix_print(graph);
	printf("\nРезультат работы на матрице смежности: \n");
	TimeQue = BFS(graph, 0, visitedArray);
	clear_visited(visitedArray, MatrixOrder);
	printf("\nРезультат работы на матрице смежности с использованием списка как очереди: \n");
	TimeList = BFSwithoutQ(graph, 0, visitedArray);
	printf("\n\n");
	printf("Время с очередью: %lf", TimeQue);
	printf("\n\n");
	printf("Время со списком: %lf\n", TimeList);
	Lists* list = ListsCreate(MatrixOrder);
	TransMatrixInList(graph, list);
	PrintList(list);
	printf("\nРезультат работы на списках смежности: \n");
	clear_visited(visitedArray, MatrixOrder);
	BFSinLists(list, 0, visitedArray);
	printf("\n");
	graph_free(graph);
	ListsDelete(list);
	system("Pause");
}
