#pragma once
#include "Header.h"
#include "BitVector.cpp"
#include "Graph_structure.h"
struct BitGraph {
	std::size_t size;
	BitVector edges[NODE_LIMIT];
	int weights[NODE_LIMIT][NODE_LIMIT];
	BitGraph(std::size_t size = 32) {
		this->size = size;
	}
};

class StructGraph {
private:
	Graph_structure* graph[NODE_LIMIT] = { nullptr };
	std::size_t size = 0;
	Graph_structure* gen_queue(Graph_structure* beginning, bool* visited, int started_with, bool* found_cycle);
	void clear_structure(Graph_structure** to_clear);
	void pop_from_queue(Graph_structure** from);
	Graph_structure* sort_by_weight(Graph_structure* beginning);
public:
	void bfs_structure_recursive(int current, std::string& to_show, bool weight_mode, bool* visited);
	void bfs_structure_recursive(int current, bool* visited);
	void clear();
	void dfs_structure_recursive(int current, std::string& to_show, bool weight_mode, bool* visited);
	void bfs_cycle_structure_recursive(int current, bool* visited, int parent, bool* to_change);
	void dfs_oriented_cycle(int start_with, bool* to_change);
	void dfs_oriented_cycle_recursive(int current, std::vector<int> visited, bool* to_change);
	bool component_detection(int current, bool* visited, bool oriented, std::vector<int>& heads, int has_component);
	void add_to_structure(int id_1, int id_2, int weight);
	void set_size(std::size_t value);
	std::size_t get_size();
	StructGraph() {

	}
	~StructGraph() {

	}
};
