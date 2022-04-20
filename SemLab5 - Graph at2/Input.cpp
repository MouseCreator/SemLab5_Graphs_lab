#include "Program.h"

void Program::input()
{
	static float delay = 0.f;
	static bool was_pressed = false;
	if (was_pressed == true) {
		delay += delta_time;
		if (delay > min_delay) {
			was_pressed = false;
			delay -= min_delay;
		}
	}
	if (text_bar_input()) return;
	if (mouse.isButtonPressed(sf::Mouse::Left) and mouse_on_screen() and this->window->hasFocus() and this->using_ui()) {
		if (this->tab.text_box()->is_selected(mouse_position())) 
		{
			this->tab.text_box()->set_is_active(true);
			this->tab.text_box()->add_column();
		}
		int button_activated = this->tab.get_button_activated(mouse_position());
		if (was_pressed == false)
		{
			if (button_activated == 1) {
				convert_to_structure();
			}
			else if (button_activated == 3) {
				this->tab.oriented_check_box()->change_state();
				this->oriented_graph = tab.oriented_check_box()->get_state();
					
			}
			was_pressed = true;
		}
	}
	if (mouse.isButtonPressed(sf::Mouse::Left) and mouse_on_screen() and this->window->hasFocus() and !this->using_ui())
	{
		if (keyboard.isKeyPressed(sf::Keyboard::LControl))
		{
			this->move_mode();
		}
		else if (keyboard.isKeyPressed(sf::Keyboard::LShift))
		{
			this->delete_mode();
		}
		else
		{
			this->add_mode();
		}
	}
	else
	{
		if (this->active_node) {
			if (is_over_node(this->active_node)) {
				this->active_node->move(this->last_position);
				update_edges();
			}
			this->active_node = nullptr;
			this->active_edge = nullptr;
		}
		if (this->active_edge) {
			this->put_new_edge();
		}

	}
}
void Program::put_new_edge() {
	Node* temp = is_over_node();
	if (temp and // has ending
		temp != this->active_edge->get_beginning() and // ending != beginning
		!edge_exists(this->active_edge->get_beginning(), temp)) //the same edge doesn't exist
	{
		this->active_edge->end_installation(temp);
		this->establish_edge();
		this->active_edge = nullptr;
	}
	else {
		this->pop_edge(this->all_edges->edge);
		this->active_edge = nullptr;
	}
	if (all_edges != nullptr) {
		this->tab.oriented_check_box()->set_avaliable(false);
	}
}

bool Program::edge_exists(Node* from, Node* to) {
	List_edges* current = this->all_edges;
	while (current) {
		
		if (current->node1 == from and current->node2 == to) {
			return true;
		}
		if (this->oriented_graph == false and current->node1 == to and current->node2 == from) {
			return true;
		}
		current = current->next;
	}
	return false;
}
void Program::move_mode() {
	if (this->active_node) {
		this->active_node->move(this->mouse.getPosition(*this->window));
		update_edges();
	}
	else {
		this->active_node = is_over_node();
		if (this->active_node) {
			this->last_position = sf::Vector2i(active_node->get_position().x, active_node->get_position().y);
		}

	}
}

void Program::delete_mode(){
	Node* to_delete = is_over_node();
	delete_edge();
	bool check_edges = true;
	if (to_delete) {
		while (check_edges)
		{
			check_edges = false;
			List_edges* current = all_edges;
			while (current) {
				if (current->edge->get_beginning() == to_delete or current->edge->get_ending() == to_delete)
				{
					pop_edge(current->edge); check_edges = true; break;
				}
				current = current->next;
			}
		}
		int j = 0;
		int to_delete_id = to_delete->get_id();
		while (nodes[j] != to_delete)
		{
			j++;
		}
		delete this->nodes[j];
		this->nodes.erase(nodes.begin() + j);
		for (int i = 0; i < this->nodes.size(); i++) {
			if (this->nodes[i]->get_id() > to_delete_id) {
				this->nodes[i]->decrease_id();
			}
		}
	}
}

void Program::add_mode() {
	if (this->active_node == nullptr and this->active_edge == nullptr) {
		this->active_node = is_over_node();
		if (this->active_node) {
			this->add_edge(this->active_node);
			this->active_node = nullptr;
			this->active_edge = this->all_edges->edge;
		}
		else {
			int new_number = 0;
			if (nodes.size() > 0)
			{
				new_number = nodes.back()->get_id() + 1;
			}
			this->nodes.emplace_back(new Node(new_number, this->mouse.getPosition(*this->window), &this->font));
			this->active_node = nodes.back();
		}

	}
	if (this->active_node) {
		this->active_node->move(this->mouse.getPosition(*this->window));
	}
	if (this->active_edge) {
		this->active_edge->installation(this->mouse.getPosition(*this->window));
	}
}