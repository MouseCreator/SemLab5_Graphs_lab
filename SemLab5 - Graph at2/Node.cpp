#include "Node.h"



void Node::init_shape(sf::Vector2i position)
{
	this->shape.setFillColor(sf::Color::Blue);
	this->shape.setRadius(8.f);
	this->shape.setOrigin(sf::Vector2f(this->shape.getRadius(), this->shape.getRadius()));
	this->shape.setPosition(position.x, position.y);
}

Node::Node(int id, sf::Vector2i position, sf::Font* font)
{
	this->id = id;
	init_shape(position);
	this->text.setFont(*font);
	this->update_text();
	this->text.setCharacterSize(6.f);
	this->text.setOrigin(sf::Vector2f(this->shape.getOrigin().x/2, this->shape.getOrigin().y/2));
	this->text.setFillColor(sf::Color::White);
	this->text.setPosition(this->get_position());
	
}

float Node::calculate_dist_to_mouse(sf::Vector2i mouse_position)
{
	float delta_x = this->get_position().x - float(mouse_position.x);
	delta_x *= delta_x;
	float delta_y = this->get_position().y - float(mouse_position.y);
	delta_y *= delta_y;
	return sqrt(delta_x + delta_y);
}

void Node::change_color(bool is_selected)
{
	if (is_selected) this->shape.setFillColor(sf::Color(30, 180, 255));
	else this->shape.setFillColor(sf::Color::Blue);
}

Node::~Node()
{
}
