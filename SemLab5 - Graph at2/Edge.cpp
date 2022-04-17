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

void Edge::set_beginning(Node* beginning, sf::Font* font, int weight)
{
	sf::Vector2f position = beginning->get_position();
	this->weight = weight;
	this->text.setFont(*font);
	this->text.setString(std::to_string(this->weight));
	this->text.setFillColor(sf::Color::Red);
	this->text.setCharacterSize(8);
	this->line.setPosition(position);
	this->thickness = 2.f;
	
	this->line.setFillColor(sf::Color(0, 0, 0));
	this->line.setSize(sf::Vector2f(thickness, thickness));
	this->is_installed = false;
	this->beginning = beginning;
	this->ending = nullptr;
}

bool Edge::contains_mouse_position(sf::Vector2f mouse_position)
{
	float delta_x = this->ending->get_position().x - this->beginning->get_position().x;
	float delta_y = this->ending->get_position().y - this->beginning->get_position().y;

	return false;
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
	install_text(pos);
}
void Edge::update()
{
	this->line.setPosition(this->beginning->get_position());
	float width = calculate_width(this->beginning->get_position(), this->ending->get_position());
	float rotation = calculate_rotation(this->beginning->get_position(), this->ending->get_position());
	this->line.setRotation(rotation);
	this->line.setSize(sf::Vector2f(width, this->thickness));
	update_text();

}
void Edge::update_text()
{
	sf::Vector2f new_position = sf::Vector2f((this->beginning->get_position().x + this->ending->get_position().x) / 2.f,
		(this->beginning->get_position().y + this->ending->get_position().y) / 2.f - 10.f);
	this->text.setPosition(new_position);
}
void Edge::install_text(sf::Vector2f pos)
{
	sf::Vector2f new_position = sf::Vector2f((pos.x + this->beginning->get_position().x ) / 2.f,
		(this->beginning->get_position().y + pos.y) / 2.f - 10.f);
	this->text.setPosition(new_position);
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
