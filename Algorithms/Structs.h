#pragma once

typedef struct Graph {
	int** matrix_adj;
	int** matrix_num;
	int order;
	bool bipartition;
};