#pragma once
typedef struct Node {
	int numVertex;
	Node* next;
};

typedef struct Graph {
	int countVert;
	Graph** adjNode;
};