#pragma once
#include "Header.h"

struct Graph_structure {
	Graph_structure* next = nullptr;
	int edge_to = 0;
	int weight = 1;
	Graph_structure(int id = 0, int weight = 1, Graph_structure* next = nullptr) {
		this->edge_to = id;
		this->next = next;
		this->weight = weight;
	}
	Graph_structure() {};
};