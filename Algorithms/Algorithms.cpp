#define _CRT_SECURE_NO_WARNINGS
#include "Algorithms.h"
#include "Structs.h"


int** matrix_malloc(int order) {
	int** matrix = (int**)malloc(sizeof(int**) * order);
	for (int i = 0; i < order; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * order);
	}
	return matrix;
}

Graph* graph_create(int order) {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->matrix_adj = matrix_malloc(order);
	graph->matrix_num = matrix_malloc(order);
	graph->order = order;
	return graph;
}

int get_adj() {
	if (rand() % 101 <= 30) {
		return 1;
	}
	else {
		return 0;
	}
}

void matrix_numerate(Graph* graph) {
	int count = 1;
	for (int i = 0; i < graph->order; i++) {
		for (int j = i; j < graph->order; j++) {
			if (graph->matrix_adj[i][j] != 0) {
				graph->matrix_num[i][j] = graph->matrix_num[j][i] = count++;
			}
			else {
				graph->matrix_num[i][j] = graph->matrix_num[j][i] = 0;
			}
		}
	}
}

void matrix_fill(Graph* graph) {
	for (int i = 0; i < graph->order; i++) {
		for (int j = 0; j < graph->order; j++) {
			if (i == j) {
				graph->matrix_adj[i][j] = 0;
			}
			else {
				graph->matrix_adj[i][j] = graph->matrix_adj[j][i] = get_adj();

			}
		}
	}
	matrix_numerate(graph);
}


void graph_print(Graph* graph) {
	for (int i = 0; i < graph->order; i++) {
		for (int j = 0; j < graph->order; j++) {
			printf("%d  ", graph->matrix_adj[i][j]);
		}
		printf("\n");
	}
}

bool bipartition_dfs(Graph* graph, int v, int* color, int current_color) {
	color[v] = current_color;
	for (int u = 0; u < graph->order; u++) {
		if (graph->matrix_adj[v][u] && color[u] == 0) {
			if (current_color == 1) {
				bipartition_dfs(graph, u, color, 2);
			}
			else
			{
				bipartition_dfs(graph, u, color, 1);
			}
		}
		else if (color[u] == current_color) {
			return false;
		}
	}
	return true;
}



bool bipartition_check(Graph* graph) {
	int* color = (int*)malloc(sizeof(int) * graph->order);
	for (int i = 0; i < graph->order; i++) {
		color[i] = 0;
	}

	for (int i = 0; i < graph->order; i++) {
		if (color[i] == 0) {
			if (bipartition_dfs(graph, i, color, 1) == false) {
				return false;
			}
		}
	}
	return true;
}


int main() {
	srand(time(NULL));
	int order;
	scanf("%d", &order);
	Graph* G = graph_create(order);
	matrix_fill(G);
	graph_print(G);
	G->bipartition = bipartition_check(G);
	if (G->bipartition == false) {
		printf("NO");
	}
	else {
		printf("YES");
	}
	system("PAUSE");
}

