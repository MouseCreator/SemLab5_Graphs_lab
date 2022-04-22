#include "Program.h"

void Program::convert_to_vector()
{
}

void Program::convert_to_structure() {
	List_edges* current = this->all_edges;
	int id_1 = 0;
	int id_2 = 0;
	int weight = 0;
	while (current) {
		id_1 = current->edge->get_beginning()->get_id();
		id_2 = current->edge->get_ending()->get_id();
		weight = current->edge->get_weight();
		this->structed_graph.add_to_structure(id_1, id_2, weight);
		if (this->oriented_graph == false) {
			this->structed_graph.add_to_structure(id_2, id_1, weight);
		}
		current = current->next;
	}
	this->structed_graph.set_size(this->nodes.size());
}
void Program::dfs_structure() {
	if (this->autoconvert) {
		this->convert();
	}
	std::string to_show = "DFS: ";
	int starter = 0;
	bool visited[NODE_LIMIT] = { 0 };
	if (this->selected) {
		starter = this->selected->get_id();
	}
	if (this->structed_graph.get_size() > 0)
	{
		this->structed_graph.dfs_structure_recursive(starter, to_show, this->weight_mode, visited);
	}
	this->tab.update_output_text(to_show);
}

void Program::bfs_structure() {
	if (this->autoconvert) {
		this->convert();
	}
	std::string to_show = "BFS: ";
	bool visited[NODE_LIMIT] = { 0 };
	int starter = 0;
	if (this->selected) {
		starter = this->selected->get_id();
	}
	if (this->structed_graph.get_size() > 0)
	{
		this->structed_graph.bfs_structure_recursive(starter, to_show, this->weight_mode, visited);
	}
	this->tab.update_output_text(to_show);
}

void Program::convert()
{
	if (this->to_vector) {
		convert_to_vector();
	}
	else
	{
		this->clear_structure();
		this->convert_to_structure();
	}
}

void Program::clear_structure() {
	this->structed_graph.clear();
}

