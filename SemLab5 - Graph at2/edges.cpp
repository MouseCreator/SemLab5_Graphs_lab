#include "Program.h"

void Program::add_edge(Node* beginning) {
	List_edges* to_add = new List_edges;
	to_add->edge = new Edge();
	to_add->edge->set_beginning(beginning, &this->font, this->current_weight, this->oriented_graph, &this->arrow_texture);
	to_add->next = this->all_edges;
	this->all_edges = to_add;
}

void Program::pop_edge(Edge* edge)
{
	List_edges* current = all_edges;
	if (this->all_edges->edge == edge) {
		this->all_edges = all_edges->next;
		delete current;
	}
	else {
		while (current) {
			if (current->next->edge == edge) {
				List_edges* to_delete = current->next;
				current->next = to_delete->next;
				delete to_delete;
				return;
			}
			current = current->next;
		}
	}
}

void Program::clear_list()
{
	List_edges* current = all_edges;
	List_edges* to_delete = current;
	while (current) {
		to_delete = current;
		current = current->next;
		delete to_delete;
	}
}

void Program::establish_edge()
{
	this->all_edges->node1 = this->all_edges->edge->get_beginning();
	this->all_edges->node2 = this->all_edges->edge->get_ending();
}

