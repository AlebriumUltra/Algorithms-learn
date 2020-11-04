#pragma once
typedef struct Node {
	int vertex;
	Node* next;
};

typedef struct Graph {
	int numVertex;
	Node** headsVertex;
};