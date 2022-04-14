#include "Edge.h"


void Edge::end_installation(Node* ending)
{
	this->ending = ending;
	this->update();
}

bool Edge::under_mouse(sf::Vector2i mouse_position)
{
	return false;
}

void Edge::set_beginning(Node* beginning)
{
	sf::Vector2f position = beginning->get_position();
	this->line.setPosition(position);
	this->thickness = 2.f;
	this->line.setFillColor(sf::Color(0, 0, 0));
	this->line.setSize(sf::Vector2f(thickness, thickness));
	this->is_installed = false;
	this->beginning = beginning;
	this->ending = nullptr;
}

Edge::Edge()
{
}

void Edge::installation(sf::Vector2i mouse_position)
{
	sf::Vector2f pos = sf::Vector2f(mouse_position.x, mouse_position.y);
	float width = calculate_width(this->line.getPosition(), pos);
	this->line.setSize(sf::Vector2f(width, this->thickness));
	float rotation = calculate_rotation(this->beginning->get_position(), pos);
	this->line.setRotation(rotation);
}
void Edge::update()
{
	this->line.setPosition(this->beginning->get_position());
	float width = calculate_width(this->beginning->get_position(), this->ending->get_position());
	float rotation = calculate_rotation(this->beginning->get_position(), this->ending->get_position());
	this->line.setRotation(rotation);
	this->line.setSize(sf::Vector2f(width, this->thickness));

}
Edge::~Edge()
{
}
float Edge::calculate_width(sf::Vector2f pos1, sf::Vector2f pos2) {
	float delta_x = pos1.x - pos2.x;
	delta_x *= delta_x;
	float delta_y = pos1.y - pos2.y;
	delta_y *= delta_y;
	return sqrt(delta_x + delta_y);
}
float Edge::calculate_rotation(sf::Vector2f pos1, sf::Vector2f pos2) {
	return atan2f(pos1.y - pos2.y, pos1.x - pos2.x) * 180 / 3.141592 - 180.f;
}
