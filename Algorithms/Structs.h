#pragma once

typedef struct Graph {
	int** Matrix;
	int* Vertexes;
	int MatrixOrder;
	bool is_filled = false;
};