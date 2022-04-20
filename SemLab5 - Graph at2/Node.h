#pragma once
#include "Header.h"
class Node
{
private:
	int id;
	sf::CircleShape shape;
	sf::Text text;
	void init_shape(sf::Vector2i position);
	void update_text() {
		this->text.setString(std::to_string(id));
	}
public:
	Node(int id, sf::Vector2i position, sf::Font* font);
	float calculate_dist_to_mouse(sf::Vector2i mouse_position);
	int get_id() {
		return this->id;
	}
	void decrease_id(){
		this->id--;
		update_text();
	}
	float get_radius() {
		return this->shape.getRadius();
	}
	void move(sf::Vector2i position) {
		this->shape.setPosition(float(position.x), float(position.y));
		this->text.setPosition(this->shape.getPosition());
	}
	void render(sf::RenderTarget* target) {
		target->draw(this->shape);
		target->draw(this->text);
	}
	sf::Vector2f get_position() {
		return this->shape.getPosition();
	}
	~Node();
};

