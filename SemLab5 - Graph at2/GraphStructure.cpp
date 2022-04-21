#include "Program.h"
#include "Header.h"

void Program::bfs_structure() {
	std::string to_show = "BFS: ";
	bool visited[NODE_LIMIT] = { 0 };
	int starter = 0;
	if (this->selected) {
		starter = this->selected->get_id();
	}
	bfs_structure_recursive(starter, to_show, this->weight_mode, visited);
	this->tab.update_output_text(to_show);
}

void Program::bfs_structure_recursive(int current, std::string& to_show, bool weight_mode, bool *visited) {
	if (visited[current]) return;
	visited[current] = true;
	to_show += std::to_string(current);
	to_show += ' ';
	Graph_structure* current_edge = this->structed_graph.graph[current];
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
Graph_structure* Program::sort_by_weight(Graph_structure* beginning) {
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
				while (weights->next and weights->next->weight > to_add->weight) {
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
Graph_structure* Program::gen_queue(Graph_structure* beginning, bool* visited)
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
void Program::pop_from_queue(Graph_structure** from)
{
	Graph_structure* to_pop = (*from);
	(*from) = (*from)->next;
	delete to_pop;
}
void Program::dfs_structure() {
	std::string to_show = "DFS: ";
	int starter = 0;
	bool visited[NODE_LIMIT] = { 0 };
	if (this->selected) {
		starter = this->selected->get_id();
	}
	dfs_structure_recursive(starter, to_show, this->weight_mode, visited);
	this->tab.update_output_text(to_show);
}

void Program::dfs_structure_recursive(int current, std::string& to_show, bool weight_mode, bool* visited) {
	Graph_structure* current_edge = this->structed_graph.graph[current];
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