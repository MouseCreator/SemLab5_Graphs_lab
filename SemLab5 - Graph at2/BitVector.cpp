#include "Header.h"
#include "Graphs.h"

void BitGraph::dfs_vector_recursive(int current, std::string& to_show, bool weight_mode, BitVector* visited)
{
	if ((*visited).get(current)) return;
	BitVector current_vector = this->edges[current];
	(*visited).set(current, true);
	to_show += std::to_string(current);
	to_show += ' ';
	if (weight_mode == false) {
		for (int i = 0; i < this->size; i++) {
			if (current_vector.get(i)) {
				dfs_vector_recursive(i, to_show, weight_mode, visited);
			}
		}
	}
	else {
		int sorted[NODE_LIMIT] = { -1 };
		sort_by_weight(current, sorted);
		int i = 0;
		while (sorted[i] != -1) {
			dfs_vector_recursive(sorted[i], to_show, weight_mode, visited);
			i++;
		}
	}
}
void BitGraph::bfs_vector_recursive(int current, std::string& to_show, bool weight_mode, BitVector* visited)
{
	BitVector current_vector = this->edges[current];
	if (visited->get(current) == false) {
		to_show += std::to_string(current);
		to_show += ' ';
		visited->set(current, true);
	}
	BitVector queue = gen_queue(current, visited);
	if (weight_mode == false) {
		for (int i = 0; i < this->size; i++) {
			if (queue.get(i))
			{
				to_show += std::to_string(i);
				to_show += ' ';
				visited->set(i, true);
			}
		}
		for (int i = 0; i < this->size; i++) {
			if (queue.get(i))
			{
				bfs_vector_recursive(i, to_show, weight_mode, visited);
			}
		}
	}
	else {
		int sorted[NODE_LIMIT] = { -1 };
		sort_by_weight(queue, current, sorted);
		int i = 0;
		while (sorted[i] != -1) {
			to_show += std::to_string(sorted[i]);
			to_show += ' ';
			visited->set(sorted[i], true);
			i++;
		}
		i = 0;
		while (sorted[i] != -1) {
			bfs_vector_recursive(sorted[i], to_show, weight_mode, visited);
			i++;
		}
	}
}

BitVector BitGraph::gen_queue(int row, BitVector *visited)
{
	unsigned temp = (this->edges[row].get_bits() & ~visited->get_bits());
	BitVector to_return;
	to_return.set_bits(temp);
	return to_return;
}

void BitGraph::sort_by_weight(int row, int* arr) {
	BitVector temp = this->edges[row];
	int counter = 0;
	int last_value = 0;
	while (true) {
		last_value = this->sort_by_weight_unit(row, &temp);
		if (last_value != -1) {
			arr[counter] = last_value;
			counter++;
		}
		else {
			arr[counter] = -1; //marks the end of the array
			return;
		}
	}
}
void BitGraph::sort_by_weight(BitVector current, int row, int* arr) {
	BitVector temp = current;
	int counter = 0;
	int last_value = 0;
	while (true) {
		last_value = this->sort_by_weight_unit(row, &temp);
		if (last_value != -1) {
			arr[counter] = last_value;
			counter++;
		}
		else {
			arr[counter] = -1; //marks the end of the array
			return;
		}
	}
}

void BitGraph::print() { //dev
	for (int i = 0; i < this->size; i++) {
		this->edges[i].print();
	}
	std::cout << std::endl;
}
int BitGraph::sort_by_weight_unit(int row, BitVector* current_vector)
{
	int min_weight = -1;
	int to_return = -1;
	for (int i = 0; i < this->size; i++) {
		if (current_vector->get(i)) {
			if (min_weight < this->weights[row][i]);
			{
				to_return = i;
				min_weight = this->weights[row][i];
			}
		}
	}
	if (to_return != -1) {
		current_vector->set(to_return, false);
	}
	return to_return;
}
