#include "Program.h"

void Program::poll_events()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
				break;
			}
		}
	}
}

void Program::init_window()
{
	this->video_mode.width = 1020;
	this->video_mode.height = 840;
	this->window = new sf::RenderWindow(this->video_mode, "Lab5 - Graphs", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Program::init_font()
{
	this->font.loadFromFile("Fonts//prstart.ttf");
	this->button_font.loadFromFile("Fonts//Lato-Black.ttf");
}
bool Program::mouse_on_screen() {
	sf::Vector2i pos = this->mouse.getPosition(*this->window);
	if (pos.x > 0 and pos.x < this->window->getSize().x)
		if (pos.y > 0 and pos.y < this->window->getSize().y)
			return true;
	return false;
}
void Program::update_edges() {
	List_edges* current = all_edges;
	while (current) {
		if (current->edge->get_beginning() == active_node or current->edge->get_ending() == active_node)
		{
			current->edge->update();
		}
		
		current = current->next;
	}
}
void Program::input()
{
	if (text_bar_input()) return;
	if (mouse.isButtonPressed(sf::Mouse::Left) and mouse_on_screen() and this->window->hasFocus() and this->using_ui()) {
		if (this->tab.text_bar_under_mouse(mouse_position())) {
			this->tab.set_text_bar_active(true);
			this->tab.update_text_bar('|');
		}
	}
	if (mouse.isButtonPressed(sf::Mouse::Left) and mouse_on_screen() and this->window->hasFocus() and !this->using_ui())
	{
		if (keyboard.isKeyPressed(sf::Keyboard::LControl))
		{
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
		else if (keyboard.isKeyPressed(sf::Keyboard::LShift))
		{
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
		else
		{
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
					this->nodes.push_back(new Node(new_number, this->mouse.getPosition(*this->window), &this->font));
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
			Node* temp = is_over_node();
			if (temp and temp != this->active_edge->get_beginning())
			{
				this->active_edge->end_installation(temp);
				this->establish_edge();
				this->active_edge = nullptr;
			}
			else {
				this->pop_edge(this->all_edges->edge);
				this->active_edge = nullptr;
			}
		}
		
	}
}
void Program::delete_edge() {
	List_edges* edge_to_delete = nullptr;
	List_edges* current = all_edges;
	while (current) {
		if (current->edge->contains_mouse_position(mouse_position()))
		{
			edge_to_delete = current;
			break;
		}
		current = current->next;
	}
	if (edge_to_delete) {
		pop_edge(edge_to_delete->edge);
	}
}
Node* Program::is_over_node()
{
	size_t size = this->nodes.size();
	for (int i = 0; i < size; i++)
	{
		float target_radius = this->nodes[i]->get_radius() + 2.f;
		if (this->nodes[i]->calculate_dist_to_mouse(this->mouse.getPosition(*this->window)) < target_radius) {
			return this->nodes[i];
		}
	}
	return nullptr;
}
Node* Program::is_over_node(Node* exception) {
	size_t size = this->nodes.size();
	for (int i = 0; i < size; i++)
	{
		float target_radius = this->nodes[i]->get_radius() + 2.f;
		if (this->nodes[i]->calculate_dist_to_mouse(this->mouse.getPosition(*this->window)) < target_radius) {
			if (this->nodes[i] != exception)
				return this->nodes[i];
		}
	}
	return nullptr;
}
sf::Vector2f Program::mouse_position() {
	return sf::Vector2f(this->mouse.getPosition(*this->window).x, this->mouse.getPosition(*this->window).y);
}
bool Program::using_ui()
{
	if (mouse_position().x > tab.get_bounds().x and mouse_position().y > tab.get_bounds().y)
		return true;
	return false;
}
Program::Program(bool graph_mode, short input_mode)
{
	this->graph_mode = graph_mode;
	this->current_weight = 1;
	this->init_window();
	this->init_font();
	this->tab = Tab(this->window, &this->button_font);
	this->active_edge = nullptr;
	this->active_node = nullptr;
	switch (input_mode) {
	case 0: is_iterational = true; break;
	case 1: is_demonstration = true; break;
	case 2: is_benchmark = true; break;
	default: std::cout << "Unknown input mode. Default: Iterational.\n";
	}
}

Program::~Program()
{
	delete this->window;
	clear_list();
	for (int i = 0; i < nodes.size(); i++)
	{
		delete nodes[i];
	}
}

const bool Program::get_window_opened() const
{
	return this->window->isOpen();
}

void Program::update()
{
	this->input();
	this->tab.update(this->mouse_position());
	this->poll_events();
}

void Program::render()
{
	this->window->clear(sf::Color::White);

	List_edges* current = all_edges;
	while (current) {
		current->edge->render(this->window);
		current = current->next;
	}
	for (int i = 0; i < this->nodes.size(); i++) {
		this->nodes[i]->render(this->window);
	}
	this->tab.render(this->window);
	this->window->display();
}
