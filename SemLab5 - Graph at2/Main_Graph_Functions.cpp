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
	for (std::size_t i = 0; i < this->structed_graph.get_size(); i++)
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

bool Program::connected_structure(bool print_result = false) {
	if (this->autoconvert) {
		this->convert();
	}
	bool visited[NODE_LIMIT] = { 0 };
	std::string to_show;
	if (this->structed_graph.get_size() > 0)
	{
		this->structed_graph.bfs_structure_recursive(0, visited);
		std::size_t size = this->structed_graph.get_size();
		for (std::size_t i = 0; i < size; i++)
		{
			if (visited[i] == 0) {
				if (print_result)
					this->tab.update_output_text("The graph is NOT connected.");
				return false;
			}
		}
		if (print_result)
			this->tab.update_output_text("The graph is connected.");
		return true;
	}
	if (print_result) {
		this->tab.update_output_text("The graph doesn't contain a single node.");
	}
	return true;
}

void Program::components_structure(std::vector<int>& component_heads) {
	bool visited[NODE_LIMIT] = { 0 };
	int size = this->structed_graph.get_size();
	for (int i = 0; i < size; i++)
	{
		if (!visited[i])
		{
			this->structed_graph.component_detection(i, visited, this->oriented_graph, component_heads, -1);
		}
	}
	
}

void Program::components_structure_show() {
	if (autoconvert) {
		this->convert();
	}
	std::vector<int> heads;
	this->components_structure(heads);
	std::string to_print = "Components: ";
	int size = heads.size();
	for (int i = 0; i < size; i++) {
		to_print += std::to_string(heads[i]);
		to_print += ' ';
	}
	this->tab.update_output_text(to_print);
}

bool Program::has_cycle(bool print_result = false) {
	if (this->autoconvert) {
		this->convert();
	}
	bool to_return = false;
	
	if (this->structed_graph.get_size() > 0)
	{
		std::vector<int> components;
		this->components_structure(components);
		for (std::size_t i = 0; i < components.size(); i++)
		{
			bool visited[NODE_LIMIT] = { 0 };
			if (this->oriented_graph)
				this->structed_graph.dfs_oriented_cycle(components[i], &to_return);
			else
				this->structed_graph.bfs_cycle_structure_recursive(components[i], visited, -1, &to_return);
			if (to_return) {
				this->tab.update_output_text("Has cycle.");
				return true;
			}
		}
		if (print_result)
		{
			this->tab.update_output_text("Doesn't have cycle.");
		}
		return false;
	}
	if (print_result) {
		this->tab.update_output_text("The graph doesn't contain a single node.");
	}
	return false;
}
