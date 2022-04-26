#pragma once
#include "Header.h"
#include "Graph_structure.h"


struct BitVector {
	unsigned bits;
	BitVector() { bits = 0; }

	bool get(std::size_t index) {
		return (bits >> index) & 01;
	}
	unsigned get_bits() {
		return this->bits;
	}
	void set(std::size_t index, bool value) {
		if (value == true) {
			bits |= (1 << index);
		}
		else {
			bits &= ~(1 << index);
		}
	}
	void print() {
		std::string str;
		unsigned current = bits;
		for (std::size_t i = 0; i < 32; i++) {
			std::cout << (current & 1) << " ";
			current >>= 1;
		}
		std::cout << std::endl;
	}
	void set_bits(unsigned value) {
		this->bits = value;
	}
};

class BitGraph {
private:
	std::size_t size;
	BitVector edges[NODE_LIMIT];
	int weights[NODE_LIMIT][NODE_LIMIT];
	void set_weight(int id_1, int id_2, int weight) {
		this->weights[id_1][id_2] = weight;
	}
	BitVector gen_queue(int row, BitVector* visited);
	void sort_by_weight(int row, int* arr);
	int sort_by_weight_unit(int row, BitVector* current_vector);
	void sort_by_weight(BitVector current, int row, int* arr);
public:
	BitGraph(std::size_t size = 32) {
		this->size = size;
	}
	~BitGraph() {

	}
	void print();
	void clear() {
		for (int i = 0; i < NODE_LIMIT; i++) {
			this->edges[i].set_bits(0);
		}
	}
	void dfs_vector_recursive(int current, std::string& to_show, bool weight_mode, BitVector *visited);
	void bfs_vector_recursive(int current, std::string& to_show, bool weight_mode, BitVector* visited);
	void add_element(int id_1, int id_2, int weight) {
		this->edges[id_1].set(id_2, true);
		this->set_weight(id_1, id_2, weight);
	}
	void set_size(std::size_t value) {
		this->size = value;
	}
	std::size_t get_size() {
		return this->size;
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
