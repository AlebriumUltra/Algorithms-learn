#pragma once
typedef struct Node {
	int vertex;
	Node* next;
};

typedef struct GraphList {
	int numVertex;
	Node** heads;
	Node** tails;
	int* sequence_vertexes;
};