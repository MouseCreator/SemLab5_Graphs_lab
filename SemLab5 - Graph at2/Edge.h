#pragma once
#include "Header.h"
#include "Node.h"
class Edge
{
private:
	sf::RectangleShape line;
	bool is_installed;
	void init_shape();
	float calculate_width(sf::Vector2f pos1, sf::Vector2f pos2);
	float calculate_rotation(sf::Vector2f pos1, sf::Vector2f pos2);
	float thickness;
	Node* beginning;
	Node* ending;
public:
	void end_installation(Node* ending);
	bool under_mouse(sf::Vector2i mouse_position);
	bool get_is_installed() {
		return this->is_installed;
	}
	void set_is_installed(bool value) {
		this->is_installed = value;
	}
	Node* get_beginning() {
		return this->beginning;
	}
	Node* get_ending() {
		return this->ending;
	}
	void set_beginning(Node* beginning);
	Edge();
	void installation(sf::Vector2i mouse_position);
	void update();
	void render(sf::RenderTarget* target) {
		target->draw(this->line);
	}
	~Edge();
};

