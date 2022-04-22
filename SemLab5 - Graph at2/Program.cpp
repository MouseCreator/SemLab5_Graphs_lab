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

void Program::init_texture() {
	this->arrow_texture.loadFromFile("Icons//Arrow.png");
	this->check_box_texture.loadFromFile("Icons//Checkbox.png");
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


void Program::prepare_checkboxes() {
	this->tab.oriented_check_box()->set_state(this->oriented_graph);
	this->tab.weight_box()->set_state(this->weight_mode);
	this->tab.autoconvert_box()->set_state(this->autoconvert);
	this->tab.to_vector_box()->set_state(this->to_vector);
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
	if (all_edges == nullptr) {
		this->tab.oriented_check_box()->set_avaliable(true);
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
Program::Program(short input_mode)
{
	//Varialbes
	this->oriented_graph = false;
	this->weight_mode = false;
	this->to_vector = false;
	this->autoconvert = true;
	this->current_weight = 1;

	//GUI
	this->init_window();
	this->init_texture();
	this->init_font();
	
	this->tab = Tab(this->window, &this->button_font, &this->check_box_texture);

	//Dynamic elements
	this->prepare_checkboxes();
	this->active_edge = nullptr;
	this->active_node = nullptr;
	//Mode
	switch (input_mode) {
	case 0: is_iterational = true; break;
	case 1: is_demonstration = true; break;
	case 2: is_benchmark = true; break;
	default: std::cout << "Unknown input mode. Default: Iterational.\n";
	}
}
void Program::clear_canvas() {
	this->clear_list();
	this->nodes.clear();
	this->tab.oriented_check_box()->set_avaliable(true);
}
Program::~Program()
{
	delete this->window;
	clear_list();
	clear_structure();
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
	this->delta_time = this->clock.restart().asSeconds();
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
