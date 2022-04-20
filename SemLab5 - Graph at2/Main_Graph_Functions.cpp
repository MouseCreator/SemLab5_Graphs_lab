#include "Program.h"

void Program::convert_to_structure() {
	this->clear_structure(); //if there was one
	List_edges* current = this->all_edges;
	int id_1 = 0;
	int id_2 = 0;
	int weight = 0;
	while (current) {
		id_1 = current->edge->get_beginning()->get_id();
		id_2 = current->edge->get_ending()->get_id();
		weight = current->edge->get_weight();
		add_to_structure(id_1, id_2, weight);
		if (this->oriented_graph == false) {
			add_to_structure(id_2, id_1, weight);
		}
		current = current->next;
	}
}

void Program::add_to_structure(int id_1, int id_2, int weight)
{
	Graph_structure* current = nullptr;
	if (this->graph_struct[id_1]) {
		current = graph_struct[id_1];
		if (id_2 < current->edge_to) {
			Graph_structure* to_add = new Graph_structure(id_2, weight, current);
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
		this->graph_struct[id_1] = new Graph_structure(id_2, weight, nullptr);
	}
}

void Program::clear_structure() {
	Graph_structure* current = nullptr;
	Graph_structure* to_delete = current;
	for (int i = 0; i < NODE_LIMIT; i++) {
		if (current = graph_struct[i]) {
			while (current) {
				to_delete = current;
				current = current->next;
				delete to_delete;
			}
			this->graph_struct[i] = nullptr;
		}
	}
}