
#include "Graphs.h"



void StructGraph::add_to_structure(int id_1, int id_2, int weight)
{
	Graph_structure* current = nullptr;
	if (this->graph[id_1]) {
		current = graph[id_1];
		if (id_2 < current->edge_to) {
			Graph_structure* to_add = new Graph_structure(id_2, weight, current);
			graph[id_1] = to_add;
			return;
		}
		while (current->next) {
			if (current->next->edge_to < id_2) {
				current->next = new Graph_structure(id_2, weight, current->next);
				return;
			}
			current = current->next;
		}
		current->next = new Graph_structure(id_2, weight);
	}
	else {
		this->graph[id_1] = new Graph_structure(id_2, weight, nullptr);
	}
}

void StructGraph::set_size(std::size_t value)
{
	this->size = value;
}

std::size_t StructGraph::get_size()
{
	return this->size;
}



void StructGraph::bfs_structure_recursive(int current, std::string& to_show, bool weight_mode, bool *visited) {
	if (visited[current]) return;
	visited[current] = true;
	to_show += std::to_string(current);
	to_show += ' ';
	Graph_structure* current_edge = this->graph[current];
	if (weight_mode == false) {
		while (current_edge) {
			bfs_structure_recursive(current_edge->edge_to, to_show, weight_mode, visited);
			current_edge = current_edge->next;
		}
	}
	else {
		Graph_structure* sorted_by_weight = sort_by_weight(current_edge);
		current_edge = sorted_by_weight;
		while (current_edge) {
			bfs_structure_recursive(current_edge->edge_to, to_show, weight_mode, visited);
			current_edge = current_edge->next;
		}
		this->clear_structure(&sorted_by_weight);
	}
}

void StructGraph::clear() {
	for (int i = 0; i < this->size; i++) {
		this->clear_structure(&this->graph[i]);
	}
}
void StructGraph::clear_structure(Graph_structure** to_clear)
{
	Graph_structure* current = (*to_clear);
	Graph_structure* to_delete;
	while (current) {
		to_delete = current;
		current = current->next;
		delete to_delete;
	}
	(*to_clear) = nullptr;
}
Graph_structure* StructGraph::sort_by_weight(Graph_structure* beginning) {
	Graph_structure* weights = nullptr;
	Graph_structure* current_edge = beginning;
	while (current_edge) { // sort by weights
		Graph_structure* to_add = new Graph_structure(current_edge->edge_to, current_edge->weight);
		if (weights == nullptr) {
			weights = to_add;
		}
		else {
			if (to_add->weight < weights->weight) {
				to_add->next = weights;
				weights = to_add;
			}
			else
			{
				while (weights->next and weights->next->weight <= to_add->weight) {
					weights = weights->next;
				}
				Graph_structure* temp = weights->next;
				weights->next = to_add;
				to_add->next = temp;
			}
		}
		current_edge = current_edge->next;
	}
	return weights;
}
Graph_structure* StructGraph::gen_queue(Graph_structure* beginning, bool* visited)
{
	Graph_structure* to_return = nullptr;
	Graph_structure* current_edge = beginning;
	while (current_edge) {
		if (visited[current_edge->edge_to] == 0) {
			if (to_return == nullptr) {
				to_return = new Graph_structure(current_edge->edge_to, current_edge->weight);
			}
			else {
				Graph_structure* current = to_return;
				while (current->next)
				{
					current = current->next;
				}
				current->next = new Graph_structure(current_edge->edge_to, current_edge->weight);
			}
		}
		current_edge = current_edge->next;
	}
	return to_return;
}
void StructGraph::pop_from_queue(Graph_structure** from)
{
	Graph_structure* to_pop = (*from);
	(*from) = (*from)->next;
	delete to_pop;
}


void StructGraph::dfs_structure_recursive(int current, std::string& to_show, bool weight_mode, bool* visited) {
	Graph_structure* current_edge = this->graph[current];
	if (visited[current] == false)
	{
		to_show += std::to_string(current);
		to_show += ' ';
		visited[current] = true;
	}
	Graph_structure* queue = gen_queue(current_edge, visited);
	if (weight_mode) {
		queue = sort_by_weight(queue);
	}
	Graph_structure* element = queue;
	while (element) {
		visited[element->edge_to] = true;
		to_show += std::to_string(element->edge_to);
		to_show += ' ';
		element = element->next;
	}
	while (queue) {
		dfs_structure_recursive(queue->edge_to, to_show, weight_mode, visited);
		pop_from_queue(&queue);
	}
	

}