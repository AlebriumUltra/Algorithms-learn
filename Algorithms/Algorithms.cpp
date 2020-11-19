#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"
#include "Lists.h"


GraphList* create_graph(int vertexes) {
	GraphList* graph = (GraphList*)malloc(sizeof(GraphList));
	graph->numVertex = vertexes;
	graph->heads = (Node**)malloc(sizeof(Node**) * vertexes);
	graph->tails = (Node**)malloc(sizeof(Node**) * vertexes);
	graph->sequence_vertexes = (int*)malloc(sizeof(int) * vertexes);
	for (int i = 0; i < vertexes; i++) {
		graph->heads[i] = NULL;
		graph->tails[i] = NULL;
		graph->sequence_vertexes[i] = i;
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

void AddFirst(GraphList* graph , int vertex, int vertexHead) {
	Node* newNode = create_node(vertex);
	newNode->next = graph->heads[vertexHead];
	graph->heads[vertexHead] = newNode;
}

void AddAfter(Node* afterNode, Node* newNode) {
	newNode->next = afterNode->next;
	afterNode->next = newNode;
}

void AddLast(GraphList* graph, int vertex, int vertexHead) {
	Node* newNode = create_node(vertex);
	Node* head = graph->heads[vertexHead];
	Node* tail = graph->tails[vertexHead];
	if (head == NULL) {
		graph->heads[vertexHead] = newNode;
		graph->tails[vertexHead] = newNode;
		return;
	}
	tail->next = newNode;
	graph->tails[vertexHead] = newNode;
}

void random_graph(GraphList* graph) {
	Node* newNode;
	for (int i = 0; i < graph->numVertex; i++) {
		for (int j = i + 1; j < graph->numVertex; j++) {
			if (randFunc() == 1) {
				AddLast(graph, j, i);
				AddLast(graph, i, j);
			}
		}
	}
}

void print_graph(GraphList* graph) {
	Node* tmp;
	for (int i = 0; i < graph->numVertex; i++) {
		printf("%d", graph->sequence_vertexes[i] + 1);
		tmp = graph->heads[i];
		while (tmp != NULL) {
			printf("->%d", tmp->vertex + 1);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

Node* find_node(GraphList* graph, int vertex, int vertexHead) {
	Node* current = graph->heads[vertexHead];
	while (current && current->vertex != vertex)
		current = current->next;
	return current;
}

void node_delete(GraphList* graph, int vertexHead, Node* DelNode) {
	Node* head = graph->heads[vertexHead];
	Node* tail = graph->tails[vertexHead];
	if (head == DelNode) {
		graph->heads[vertexHead] = DelNode->next;
		if (head == NULL) {
			graph->tails[vertexHead] = NULL;
		}
	}
	else {
		Node* current = head;
		while (current && current->next == DelNode) {
			current = current->next;
		}

		if (current == NULL) return;
		current->next = DelNode->next;
		if (tail == DelNode) {
			graph->tails[vertexHead] = current;
		}
	}
	free(DelNode);
}

void graph_delete(GraphList* graph) {
	for (int i = 0; i < graph->numVertex; i++) {
		Node* current = graph->heads[i];
		while (current) {
			Node* prevNode = current;
			current = current->next;
			free(prevNode);
		}
	}
	free(graph->heads);
	free(graph->tails);
	free(graph->sequence_vertexes);
	free(graph);
}

void vertex_identification(GraphList* graph) {
	printf("\n Vertex Identification: \n");
	printf("Enter v and u vertexes for identification: \n");
	printf("v = ");
	int v, u;
	scanf("%d", &v);
	printf("u = ");
	scanf("%d", &u);
	if (v > u) {
		int tmp = v;
		v = u;
		u = tmp;
	}
	v--;
	u--;
	GraphList* newGraph = create_graph(graph->numVertex - 1);

	for (int i = 0; i < u; i++) {
		Node* copyCurrent = graph->heads[i];
		while (copyCurrent) {
			AddLast(newGraph, copyCurrent->vertex, i);
			copyCurrent = copyCurrent->next;
		}
	}
	for (int i = u; i < newGraph->numVertex; i++) {
		Node* copyCurrent = graph->heads[i + 1];
		while (copyCurrent) {
			AddLast(newGraph, copyCurrent->vertex, i);
			copyCurrent = copyCurrent->next;
		}
	}
	for (int i = u; i < newGraph->numVertex; i++) {
		newGraph->sequence_vertexes[i] = i + 1;
	}

	Node* currentU = graph->heads[u];
	while (currentU) {
		if (find_node(graph, currentU->vertex, v) != NULL) {
			currentU = currentU->next;
		}
		else {
			AddLast(newGraph, currentU->vertex, v);
			currentU = currentU->next;
		}
	}
	printf("\n Result: \n");
	print_graph(newGraph);
	graph_delete(newGraph);
}

void edge_contract(GraphList* graph) {
	printf("\n Edge Contract: \n");
	printf("Enter v and u vertexes with connect: \n");
	printf("v = ");
	int v, u;
	scanf("%d", &v);
	printf("u = ");
	scanf("%d", &u);
	if (v > u) {
		int tmp = v;
		v = u;
		u = tmp;
	}
	v--;
	u--;
	if (find_node(graph, u, v) == NULL) {
		printf("Connect does not exist!");
		return;
	}
	GraphList* newGraph = create_graph(graph->numVertex - 1);

	for (int i = 0; i < u; i++) {
		Node* copyCurrent = graph->heads[i];
		while (copyCurrent) {
			AddLast(newGraph, copyCurrent->vertex, i);
			copyCurrent = copyCurrent->next;
		}
	}
	for (int i = u; i < newGraph->numVertex; i++) {
		Node* copyCurrent = graph->heads[i + 1];
		while (copyCurrent) {
			AddLast(newGraph, copyCurrent->vertex, i);
			copyCurrent = copyCurrent->next;
		}
	}
	for (int i = u; i < newGraph->numVertex; i++) {
		newGraph->sequence_vertexes[i] = i + 1;
	}

	Node* currentU = graph->heads[u];
	while (currentU) {
		if (find_node(graph, currentU->vertex, v) != NULL) {
			currentU = currentU->next;
		}
		else {
			AddLast(newGraph, currentU->vertex, v);
			currentU = currentU->next;
		}
	}

	Node* DeleteNode = find_node(newGraph, v, v);
	node_delete(newGraph, v, DeleteNode);
	printf("\n Result: \n");
	print_graph(newGraph);
	graph_delete(newGraph);
}

void split_vertex(GraphList* graph) {
	printf("\n Vertex Split \n");
	printf("Enter vertex for split: \nv = ");
	int v;
	scanf("%d", &v);
	v--;

	GraphList* newGraph = create_graph(graph->numVertex + 1);

	for (int i = 0; i < graph->numVertex; i++) {
		Node* copyCurrent = graph->heads[i];
		while (copyCurrent) {
			AddLast(newGraph, copyCurrent->vertex, i);
			copyCurrent = copyCurrent->next;
		}
	}

	int newVertex = graph->numVertex;

	Node* currentV = newGraph->heads[v];
	while (currentV) {
		if (rand() % 2 == 1) {
			AddLast(newGraph, currentV->vertex, newVertex);
			Node* OldNode = currentV;
			currentV = currentV->next;
			node_delete(newGraph, v, OldNode);
		}
		else {
			currentV = currentV->next;
		}
	}
	printf("\n Result: \n");
	print_graph(newGraph);
	graph_delete(newGraph);
}

void GraphUnion(GraphList* G1, GraphList* G2) {
	print_graph(G1);
	printf("\n");
	print_graph(G2);
	printf("\nGraphUnion\n");
	int num_vertexesG1 = G1->numVertex;
	int num_vertexesG2 = G2->numVertex;
	GraphList* G3_union;
	if (num_vertexesG1 < num_vertexesG2) {
		G3_union = create_graph(num_vertexesG2);
		for (int i = 0; i < num_vertexesG2; i++) {
			Node* current = G2->heads[i];
			while (current) {
				AddLast(G3_union, current->vertex, i);
				current = current->next;
			}
		}
		for (int i = 0; i < num_vertexesG1; i++) {
			Node* current = G1->heads[i];
			while (current) {
				if (find_node(G3_union, current->vertex, i)) {
					current = current->next;
				}
				else {
					AddLast(G3_union, current->vertex, i);
					current = current->next;
				}
			}
		}
	}
	else {
		G3_union = create_graph(num_vertexesG1);
		for (int i = 0; i < num_vertexesG1; i++) {
			Node* current = G1->heads[i];
			while (current) {
				AddLast(G3_union, current->vertex, i);
				current = current->next;
			}
		}
		for (int i = 0; i < num_vertexesG2; i++) {
			Node* current = G2->heads[i];
			while (current) {
				if (find_node(G3_union, current->vertex, i)) {
					current = current->next;
				}
				else {
					AddLast(G3_union, current->vertex, i);
					current = current->next;
				}
			}
		}
	}
	printf("Result union\n");
	print_graph(G3_union);
	graph_delete(G3_union);
}

void GraphCross(GraphList* G1, GraphList* G2) {
	printf("\nGraphCross\n");
	int num_vertexesG1 = G1->numVertex;
	int num_vertexesG2 = G2->numVertex;
	GraphList* G3_cross;
	if (num_vertexesG1 < num_vertexesG2) {
		G3_cross = create_graph(num_vertexesG1);
		for (int i = 0; i < num_vertexesG1; i++) {
			Node* current = G1->heads[i];
			while (current) {
				if (find_node(G2, current->vertex, i)) {
					AddLast(G3_cross, current->vertex, i);
					current = current->next;
				}
				else {
					current = current->next;
				}
			}
		}
	}
	else {
		G3_cross = create_graph(num_vertexesG2);
		for (int i = 0; i < num_vertexesG2; i++) {
			Node* current = G2->heads[i];
			while (current) {
				if (find_node(G1, current->vertex, i)) {
					AddLast(G3_cross, current->vertex, i);
					current = current->next;
				}
				else {
					current = current->next;
				}
			}
		}
	}
	printf("Result cross\n");
	print_graph(G3_cross);
	graph_delete(G3_cross);
}

void GraphSum(GraphList* G1, GraphList* G2) {
	printf("\nGraphSum\n");
	int num_vertexesG1 = G1->numVertex;
	int num_vertexesG2 = G2->numVertex;
	GraphList* G3_sum;
	if (num_vertexesG1 < num_vertexesG2) {
		G3_sum = create_graph(num_vertexesG2);
		for (int i = 0; i < num_vertexesG1; i++) {
			Node* current = G1->heads[i];
			while (current) {
				if (find_node(G2, current->vertex, i)) {
					current = current->next;
				}
				else {
					AddLast(G3_sum, current->vertex, i);
					current = current->next;
				}
			}
		}
		for (int i = 0; i < num_vertexesG1; i++) {
			Node* current = G2->heads[i];
			while (current) {
				if (find_node(G1, current->vertex, i)) {
					current = current->next;
				}
				else {
					AddLast(G3_sum, current->vertex, i);
					current = current->next;
				}
			}
		}
		for (int i = num_vertexesG1; i < num_vertexesG2; i++) {
			Node* current = G2->heads[i];
			while (current) {
				AddLast(G3_sum, current->vertex, i);
				current = current->next;
			}
		}
	}
	else {
		G3_sum = create_graph(num_vertexesG1);
		for (int i = 0; i < num_vertexesG2; i++) {
			Node* current = G2->heads[i];
			while (current) {
				if (find_node(G1, current->vertex, i)) {
					current = current->next;
				}
				else {
					AddLast(G3_sum, current->vertex, i);
					current = current->next;
				}
			}
		}
		for (int i = 0; i < num_vertexesG2; i++) {
			Node* current = G1->heads[i];
			while (current) {
				if (find_node(G2, current->vertex, i)) {
					current = current->next;
				}
				else {
					AddLast(G3_sum, current->vertex, i);
					current = current->next;
				}
			}
		}
		for (int i = num_vertexesG2; i < num_vertexesG1; i++) {
			Node* current = G1->heads[i];
			while (current) {
				AddLast(G3_sum, current->vertex, i);
				current = current->next;
			}
		}
	}
	printf("Result sum\n");
	print_graph(G3_sum);
	graph_delete(G3_sum);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	int num_vertexesG1;
	int num_vertexesG2;
	printf("Enter the number of vertexes for G1: ");
	scanf("%d", &num_vertexesG1);
	printf("Enter the number of vertexes for G2: ");
	scanf("%d", &num_vertexesG2);
	GraphList* graphG1 = create_graph(num_vertexesG1);
	random_graph(graphG1);
	print_graph(graphG1);
	printf("\n---------------------Unary operations-------------------\n");
	vertex_identification(graphG1);
	edge_contract(graphG1);
	split_vertex(graphG1);
	printf("\n---------------------Binary operations-------------------\n");
	GraphList* graphG2 = create_graph(num_vertexesG2);
	random_graph(graphG2);
	GraphUnion(graphG1, graphG2);
	GraphCross(graphG1, graphG2);
	GraphSum(graphG1, graphG2);
	system("PAUSE");
}