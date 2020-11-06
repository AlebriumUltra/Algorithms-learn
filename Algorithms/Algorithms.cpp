#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"
#include "Structs.h"
#include <stack>


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


void DFS(int Vertex, Graph* graph, int* visitedArray) {
	printf("%d", Vertex + 1);
	visitedArray[Vertex] = 1;
	for (int vertexNext = 0; vertexNext < graph->MatrixOrder; vertexNext++) {
		if (graph->Matrix[Vertex][vertexNext] && visitedArray[vertexNext] != 1) {
			DFS(vertexNext, graph, visitedArray);
		}
	}
}

void DFSnR(int Vertex, Graph* graph, int* visitedArray) {
	std::stack<int>myStack;
	myStack.push(Vertex);
	while (!myStack.empty()) {
		Vertex = myStack.top();
		myStack.pop();
		if (visitedArray[Vertex] == 0) {
			visitedArray[Vertex] = 1;
			printf("%d", Vertex + 1);
			for (int i = graph->MatrixOrder - 1; i >= 0; i--) {
				if (graph->Matrix[Vertex][i] == 1 && visitedArray[i] == 0) {
					myStack.push(i);
				}
			}
		}
	}
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
	list->head = (Node **)malloc(sizeof(struct Node*) * numVertexes);
	for (int i = 0; i < numVertexes; i++) {
		list->head[i] = NULL;
	}
	return list;
}

void AddFirst(Node** head, Node* newNode) {
	newNode->next = *head;
	*head = newNode;
}

void AddAfter(Node* afterNode, Node* newNode) {
	newNode->next = afterNode->next;
	afterNode->next = newNode;
}

void AddBefore(Node** head, Node* beforeNode, Node* newNode) {
	Node* current = *head;
	if (*head == beforeNode) {
		AddFirst(head, newNode);
		return;
	}
	while (current && current->next != beforeNode)
		current = current->next;
	if (current)
		AddAfter(current, newNode);
}

void AddLast(Node** head, Node* newNode) {
	Node* current = *head;
	if (*head == NULL) {
		AddFirst(head, newNode);
		return;
	}
	while (current->next)
		current = current->next;
	AddAfter(current, newNode);
}


void PrintList(Lists* list) {
	printf("\n");
	printf("Список смежности");
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

void ListsDelete(Lists* list) {
	for (int i = 0; i < list->numVertexes; i++) {
		while (list->head[i] != NULL) {
			Node* prevNode = list->head[i];
			list->head[i] = list->head[i]->next;
			free(prevNode);
		}
		free(list->head[i]);
	}
	free(list->head);
	free(list);
}

void DFSinLists(Lists* list, int vertex, int* visitedArray) {
	printf("%d", vertex + 1);
	visitedArray[vertex] = 1;
	Node* current = list->head[vertex];
	while (current) {
		if (visitedArray[current->vertex] == 0) {
			DFSinLists(list, current->vertex, visitedArray);
		}
		current = current->next;
	}
}



void DFSinListsNR(Lists* list, int vertex, int* visitedArray) {
	std::stack<int>stackVertexes;
	stackVertexes.push(vertex);
	while (!stackVertexes.empty()) {
		vertex = stackVertexes.top();
		stackVertexes.pop();
		if (visitedArray[vertex] == 0) {
			visitedArray[vertex] = 1;
			printf("%d", vertex + 1);
			Node* current = list->head[vertex];
			while (current) {
				if (visitedArray[current->vertex] == 0) {
					stackVertexes.push(current->vertex);
				}
				current = current->next;
			}
		}
	}
}

void TransMatrixInListRev(Graph* graph, Lists* list) {
	int MatrixOrder = graph->MatrixOrder;
	for (int i = 0; i < MatrixOrder; i++) {
		for (int j = 0; j < MatrixOrder; j++) {
			if (graph->Matrix[i][j] == 1) {
				Node* newNode = NodeCreate(j);
				AddFirst(&list->head[i], newNode);
			}
		}
	}
}
int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	int MatrixOrder;
	printf("Enter matrix order: ");
	scanf("%d", &MatrixOrder);
	Graph* graph = graph_create(MatrixOrder);
	int* visitedArray = create_visitedArray(MatrixOrder);
	graph_random(graph);
	matrix_print(graph);
	printf("\nРекурсивный поиск в глубину\n");
	for (int vertex = 0; vertex < MatrixOrder; vertex++) {
		if (visitedArray[vertex] == 0) {
			printf("\n");
			DFS(vertex, graph, visitedArray);
		}
	}
	clear_visited(visitedArray, MatrixOrder);
	printf("\n\nНе рекурсивный поиск в глубину\n");
	for (int vertex = 0; vertex < MatrixOrder; vertex++) {
		if (visitedArray[vertex] == 0) {
			printf("\n");
			DFSnR(vertex, graph, visitedArray);
		}
	}
	clear_visited(visitedArray, MatrixOrder);
	printf("\n\nПоиск в глубину на списке смежности с рекурсией\n");
	Lists* list = ListsCreate(MatrixOrder);
	TransMatrixInList(graph, list);
	PrintList(list);
	for (int vertex = 0; vertex < MatrixOrder; vertex++) {
		if (visitedArray[vertex] == 0) {
			printf("\n");
			DFSinLists(list, vertex, visitedArray);
		}
	}
	printf("\n");
	clear_visited(visitedArray, MatrixOrder);
	Lists* listReverse = ListsCreate(MatrixOrder);
	TransMatrixInListRev(graph, listReverse);
	PrintList(listReverse);
	printf("\n\nПоиск в глубину на списке смежности без рекурсией\n");
	for (int vertex = 0; vertex < MatrixOrder; vertex++) {
		if (visitedArray[vertex] == 0) {
			printf("\n");
			DFSinListsNR(listReverse, vertex, visitedArray);
		}
	}
	printf("\n");
	graph_free(graph);
	ListsDelete(list);
	ListsDelete(listReverse);
	printf("\n");
	system("Pause");
}

