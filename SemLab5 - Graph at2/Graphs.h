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

class StructGraph {
private:
	Graph_structure* graph[NODE_LIMIT] = { nullptr };
	std::size_t size = 0;
	Graph_structure* gen_queue(Graph_structure* beginning, bool* visited);
	void clear_structure(Graph_structure** to_clear);
	void pop_from_queue(Graph_structure** from);
	Graph_structure* sort_by_weight(Graph_structure* beginning);
public:
	void bfs_structure_recursive(int current, std::string& to_show, bool weight_mode, bool* visited);
	void clear();
	void dfs_structure_recursive(int current, std::string& to_show, bool weight_mode, bool* visited);
	void add_to_structure(int id_1, int id_2, int weight);
	void set_size(std::size_t value);
	std::size_t get_size();
	StructGraph() {

	}
	~StructGraph() {

	}
};
