#include "Program.h"

void Program::input()
{
	static float delay = 0.f;
	static bool was_pressed = false;
	if (text_bar_input()) return;
	if (mouse.isButtonPressed(sf::Mouse::Left) and is_selecting) {
		if (was_pressed == false)
		{
			this->stop_selection();
		}
		was_pressed = true;
		return;
	}
	if (mouse.isButtonPressed(sf::Mouse::Left) and mouse_on_screen() and this->window->hasFocus() and this->using_ui()) {
		if (this->active_node) {
			this->active_node->move(this->last_position);
			this->active_node = nullptr;
		}
		if (this->tab.text_box()->is_selected(mouse_position())) 
		{
			this->tab.text_box()->set_is_active(true);
			this->tab.text_box()->add_column();
		}
		int button_activated = this->tab.get_button_activated(mouse_position());
		if (was_pressed == false)
		{
			was_pressed = true;
			buttons_input(button_activated);
		}
	}
	if (mouse.isButtonPressed(sf::Mouse::Left) == false) {
		was_pressed = false;
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
			if (!was_pressed)
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
		this->active_node->move(mouse_position());
		update_edges();
	}
	else {
		this->active_node = is_over_node();
		if (this->active_node) {
			this->last_position = sf::Vector2f(active_node->get_position().x, active_node->get_position().y);
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
		for (size_t i = 0; i < this->nodes.size(); i++) {
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
		this->active_node->move(mouse_position());
	}
	if (this->active_edge) {
		this->active_edge->installation(this->mouse.getPosition(*this->window));
	}
}

void Program::buttons_input(int button_activated = 0) {
	if (button_activated == 0) return;
	else if (button_activated == 1) {
		this->convert();
		this->tab.update_output_text("Converted!");
	}
	else if (button_activated == 2) {
		this->clear_canvas();
	}
	else if (button_activated == 3) {
		this->tab.oriented_check_box()->change_state();
		this->oriented_graph = tab.oriented_check_box()->get_state();

	}
	else if (button_activated == 4) {
		this->tab.weight_box()->change_state();
		this->weight_mode = tab.weight_box()->get_state();

	}
	else if (button_activated == 5) {
		if (this->to_vector)
			this->bfs_vector();
		else
			this->bfs_structure();
	}
	else if (button_activated == 6) {
		if (this->to_vector)
			this->dfs_vector();
		else
			this->dfs_structure();
	}
	else if (button_activated == 7) {
		this->tab.to_vector_box()->change_state();
		this->to_vector = tab.to_vector_box()->get_state();

	}
	else if (button_activated == 8) {
		this->tab.autoconvert_box()->change_state();
		this->autoconvert = tab.autoconvert_box()->get_state();

	}
	else if (button_activated == 9) {
		this->connected_structure(true);
	}
	else if (button_activated == 10) {
		this->has_cycle(true);
	}
	else if (button_activated == 11) {
		this->components_structure_show();
	}
	else if (button_activated == 12) {
		this->start_selection();
	}
}

void Program::start_selection() {
	this->is_selecting = true;
	this->cursor.loadFromSystem(sf::Cursor::Cross);
	this->window->setMouseCursor(cursor);
}
void Program::stop_selection() {
	this->is_selecting = false;
	this->cursor.loadFromSystem(sf::Cursor::Arrow);
	this->window->setMouseCursor(cursor);
	if (this->selected) {
		this->selected->change_color(false);
	}
	this->selected = is_over_node();
	if (this->selected)
	{
		this->selected->change_color(true);
	}
}