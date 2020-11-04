#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"
#include "Lists.h"


Graph* create_graph(int vertexes) {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->numVertex = vertexes;
	graph->headsVertex = (Node**)malloc(sizeof(Node*) * vertexes);
	for (int i = 0; i < vertexes; i++) {
		graph->headsVertex[i] = NULL;
	}
	return graph;
}

Node* create_node(int vertex) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->vertex = vertex;
	node->next = NULL;
	return node;
}

int randFunc() {
	if (rand() % 101 <= 45)
		return 1;
	else
		return 0;
}

void random_graph(Graph* graph) {
	Node* newNode;
	for (int i = 0; i < graph->numVertex; i++) {
		for (int j = i + 1; j < graph->numVertex; j++) {
			if (randFunc() == 1) {
				newNode = create_node(j);
				if (graph->headsVertex[i] == NULL) {
					graph->headsVertex[i] = newNode;
				}
				else {
					Node* tmp = graph->headsVertex[i];
					while (tmp->next != NULL) {
						tmp = tmp->next;
					}
					tmp->next = newNode;
				}
				newNode = create_node(i);
				if (graph->headsVertex[j] == NULL) {
					graph->headsVertex[j] = newNode;
				}
				else {
					Node* tmp = graph->headsVertex[j];
					while (tmp->next != NULL) {
						tmp = tmp->next;
					}
					tmp->next = newNode;
				}
			}
		}
	}
}

void print_graph(Graph* graph) {
	Node* tmp;
	for (int i = 0; i < graph->numVertex; i++) {
		printf("%d", i + 1);
		tmp = graph->headsVertex[i];
		while (tmp != NULL) {
			printf("->%d", tmp->vertex + 1);
			tmp = tmp->next;
		}
		printf("\n");
	}
}




int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	int numVertexes;
	printf("Введите количество вершин: ");
	scanf("%d", &numVertexes);
	Graph* graphG1 = create_graph(numVertexes);
	random_graph(graphG1);
	print_graph(graphG1);
	system("PAUSE");
}