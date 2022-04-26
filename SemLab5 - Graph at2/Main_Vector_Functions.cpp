#include "Program.h"

void Program::convert_to_vector()
{
	this->bitgraph.clear();
	List_edges* current = this->all_edges;
	int id_1 = 0;
	int id_2 = 0;
	int weight = 0;
	while (current) {
		id_1 = current->edge->get_beginning()->get_id();
		id_2 = current->edge->get_ending()->get_id();
		weight = current->edge->get_weight();
		this->bitgraph.add_element(id_1, id_2, weight);
		if (this->oriented_graph == false) {
			this->bitgraph.add_element(id_2, id_1, weight);
		}
		current = current->next;
	}
	this->bitgraph.set_size(this->nodes.size());
}

void Program::dfs_vector() {
	if (this->autoconvert) {
		this->convert();
	}
	std::string to_show = "DFS: ";
	int starter = 0;
	BitVector visited;
	if (this->selected) {
		starter = this->selected->get_id();
	}
	std::size_t size = this->bitgraph.get_size();
	if (size > 0)
	{
		this->bitgraph.dfs_vector_recursive(starter, to_show, this->weight_mode, &visited);
		for (std::size_t i = 0; i < size; i++) {
			if (visited.get(i)) {
				this->bitgraph.bfs_vector_recursive(i, to_show, this->weight_mode, &visited);
			}
		}
	}
	this->tab.update_output_text(to_show);
}

void Program::bfs_vector() {
	if (this->autoconvert) {
		this->convert();
	}
	std::string to_show = "BFS: ";
	BitVector visited;
	int starter = 0;
	if (this->selected) {
		starter = this->selected->get_id();
	}
	std::size_t size = this->bitgraph.get_size();
	if (size > 0)
	{
		this->bitgraph.bfs_vector_recursive(starter, to_show, this->weight_mode, &visited);
		for (std::size_t i = 0; i < size; i++) {
			if (visited.get(i)) {
				this->bitgraph.bfs_vector_recursive(i, to_show, this->weight_mode, &visited);
			}
		}
	}
	this->tab.update_output_text(to_show);
}