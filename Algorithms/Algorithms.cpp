﻿#define _CRT_SECURE_NO_WARNINGS
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

int _Rand() {
	if (rand() % 101 <= 30) {
		return 1;
	}
	else {
		return 0;
	}
}

void GraphRandom(Graph* GraphG) {
	int matrix_order = GraphG->matrix_order;
	for (int i = 0; i < matrix_order; i++) {
		for (int j = i; j < matrix_order; j++) {
			if (i == j) {
				GraphG->matrix[i][j] = 0;
			}
			else {
				GraphG->matrix[i][j] = GraphG->matrix[j][i] = _Rand();
			}
		}
	}
}

void ArrayClear(int* visitedArray, int size) {
	for (int i = 0; i < size; i++) {
		visitedArray[i] = 0;
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

void ArrayPrint(int* Array, int num_vertexes) {
	printf("\n");
	for (int i = 0; i < num_vertexes; i++) {
		printf("%d ", Array[i]);
	}
}

void BFSD(Graph* graph ,int* dist, int start_vertex) {
	std::queue<int>Q;
	int num_vertexes = graph->matrix_order;
	Q.push(start_vertex);
	dist[start_vertex] = 0;
	int current_vertex;
	while (!Q.empty()) {
		current_vertex = Q.front();
		Q.pop();
		printf("%d", current_vertex + 1);
		for (int i = 0; i < num_vertexes; i++) {
			if (graph->matrix[current_vertex][i] && dist[i] == -1) {
				Q.push(i);
				dist[i] = dist[current_vertex] + 1;
			}
		}
	}
}

void BFSDLists(Lists* list, int* dist, int start_vertex) {
	std::queue<int>Q;
	int num_vertexes = list->num_vertexes;
	Q.push(start_vertex);
	dist[start_vertex] = 0;
	int current_vertex;
	while (!Q.empty()) {
		current_vertex = Q.front();
		Q.pop();
		printf("%d", current_vertex + 1);
		Node* currentNode = list->head[current_vertex];
		while(currentNode) {
			if (dist[currentNode->vertex] == -1) {
				Q.push(currentNode->vertex);
				dist[currentNode->vertex] = dist[current_vertex] + 1;
			}
			currentNode = currentNode->next;
		}
	}
}

void DFSD(Graph* graph, int* dist, int start_vertex) {
	std::stack<int>S;
	int num_vertexes = graph->matrix_order;
	S.push(start_vertex);
	dist[start_vertex] = 0;
	int current_vertex;
	while (!S.empty()) {
		current_vertex = S.top();
		S.pop();
		printf("%d", current_vertex + 1);
		for (int i = num_vertexes - 1; i >= 0; i--) {
			if (graph->matrix[current_vertex][i] && dist[i] == -1) {
					S.push(i);
					dist[i] = dist[current_vertex] + 1;
			}
		}
	}
}

void DFSDLists(Lists* list, int* dist, int start_vertex) {
	std::stack<int>S;
	int num_vertexes = list->num_vertexes;
	S.push(start_vertex);
	dist[start_vertex] = 0;
	int current_vertex;
	while (!S.empty()) {
		current_vertex = S.top();
		S.pop();
		dist[current_vertex] = 0;
		printf("%d", current_vertex + 1);
		Node* currentNode = list->head[current_vertex];
		while(currentNode) {
			if (dist[currentNode->vertex] == -1) {
					S.push(currentNode->vertex);
					dist[currentNode->vertex] = dist[current_vertex] + 1;
			}
			currentNode = currentNode->next;
		}
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	int matrix_order;
	printf("Enter matrix order: ");
	scanf("%d", &matrix_order);
	Graph* graph = GraphCreate(matrix_order);
	GraphRandom(graph);
	MatrixPrint(graph);
	Lists* list = ListsCreate(matrix_order);
	TransMatrixInList(graph, list);
	ListsPrint(list);
	int* distance_array = ArrayCreate(matrix_order);
	DistanceArrayRefresh(distance_array, matrix_order);
	printf("\nРезультат обхода графа в ширину на матрице:\n");
	BFSD(graph, distance_array, 0);
	printf("\nМассив расстояний:");
	ArrayPrint(distance_array, matrix_order);
	DistanceArrayRefresh(distance_array, matrix_order);
	printf("\n\nРезультат обхода графа в ширину на списках:\n");
	BFSDLists(list, distance_array, 0);
	printf("\nМассив расстояний:");
	ArrayPrint(distance_array, matrix_order);
	DistanceArrayRefresh(distance_array, matrix_order);
	printf("\n\nРезультат обхода графа в глубину на матрице:\n");
	DFSD(graph, distance_array, 0);
	printf("\nМассив расстояний:");
	ArrayPrint(distance_array, matrix_order);
	DistanceArrayRefresh(distance_array, matrix_order);
	printf("\n\nРезультат обхода графа в глубину на списках:\n");
	DFSDLists(list, distance_array, 0);
	printf("\nМассив расстояний:");
	ArrayPrint(distance_array, matrix_order);
	printf("\n\n");
	system("PAUSE");
}