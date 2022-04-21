#pragma once
#include "Header.h"
#include "BitVector.cpp"
#include "Graph_structure.h"
struct BitGraph {
	std::size_t size;
	BitVector edges[NODE_LIMIT];

	BitGraph(std::size_t size = 32) {
		this->size = size;
	}
};

struct StructGraph {
	Graph_structure* graph[NODE_LIMIT];
};

struct Nodes_queue {
	Graph_structure* node;
	Nodes_queue* next;
	Nodes_queue(Graph_structure* node, Nodes_queue* next = nullptr) {
		this->next = next;
		this->node = node;
	}
};