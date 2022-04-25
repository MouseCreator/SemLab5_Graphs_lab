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

void Edge::set_beginning(Node* beginning, sf::Font* font, int weight, bool oriented, sf::Texture* arrow_texture)
{
	sf::Vector2f position = beginning->get_position();
	this->weight = weight;
	this->oriented = oriented;
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

	if (oriented) {
		this->arrow = new sf::Sprite;
		this->arrow->setTexture(*arrow_texture);
		this->arrow->setOrigin(5.f, 5.f);
	}
}

bool Edge::contains_mouse_position(sf::Vector2f mouse_position)
{
	if (this->text.getGlobalBounds().contains(mouse_position))
		return true;
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
	if (oriented) {
		this->arrow->setPosition(pos);
		this->arrow->setRotation(rotation);
	}
	install_text(pos, rotation);
}
void Edge::update()
{
	this->line.setPosition(this->beginning->get_position());
	float width = calculate_width(this->beginning->get_position(), this->ending->get_position());
	float rotation = calculate_rotation(this->beginning->get_position(), this->ending->get_position());
	this->line.setRotation(rotation);
	this->line.setSize(sf::Vector2f(width, this->thickness));
	if (oriented) {
		this->arrow->setPosition(this->ending->get_position() + calculate_circle_offset(10.f, rotation + 180, 0.f));
		this->arrow->setRotation(rotation);
	}
	update_text(rotation);

}
void Edge::update_text(float rotation)
{
	install_text(this->get_ending()->get_position(), rotation);
}
void Edge::install_text(sf::Vector2f pos, float rotation)
{;
	float real_rotation = rotation + 90;
	sf::Vector2f new_position = sf::Vector2f((pos.x + this->beginning->get_position().x ) / 2.f,
		(this->beginning->get_position().y + pos.y) / 2.f);
	sf::Vector2f circle_offset = calculate_circle_offset(15.f + this->text.getGlobalBounds().width, real_rotation, 5.f);
	new_position += circle_offset;
	this->text.setPosition(new_position);
}
sf::Vector2f Edge::calculate_circle_offset(const float offset, float rotation, float to_add = 0.f) {
	return sf::Vector2f(offset * cos(rotation * 3.141592 / 180) - to_add, offset * sin(rotation * 3.141592 / 180) - to_add);
}
Edge::~Edge()
{
	if (this->arrow) delete arrow;
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
