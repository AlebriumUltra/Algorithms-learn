#pragma once

typedef struct Graph {
	int** Matrix;
	int* Vertexes;
	int MatrixOrder;
};

typedef struct Node {
	int vertex;
	Node* next;
};

typedef struct GraphList {
	int numVertexes;
	int* seqVertexes;
	Node** Heads;
};