#pragma once
#include "Header.h"
class Button
{
private:
	sf::RectangleShape shape;
	sf::Text text;
	bool selected;
	bool was_selected;
public:
	Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font *font);
	void render(sf::RenderTarget* target);
	void update(sf::Vector2f mouse_position);
	bool is_selected(sf::Vector2f mouse_position);
	Button() {

	}
	~Button() {
	}
};

class TabButton : public Button
{
private:
	int tab_number;
public:
	TabButton(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font *font, int tab_id)
		: Button(position, size, text, font) {
		this->tab_number = tab_id;
	}
	void activate(int &current_tab) {
		current_tab = tab_number;
	}
	TabButton() {

	}
	~TabButton() {
	}
};
