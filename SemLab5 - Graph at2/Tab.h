#pragma once
#include "Header.h"
#include "Button.h"
class Tab
{
private:
	sf::RectangleShape background;
	TabButton tab1;
	TabButton tab2;
	sf::Font font;
	void init_buttons();
	void init_background(sf::RenderWindow* window);
public:
	Tab() { }
	~Tab() { }
	Tab(sf::RenderWindow* window, sf::Font* button_font) {
		init_background(window);
		init_buttons();
	}
	sf::Vector2i get_bounds();
	void update(sf::Vector2f mouse_pos) {
		this->tab1.update(mouse_pos);
		this->tab2.update(mouse_pos);
	}
	void render(sf::RenderTarget* target);
};

class AddingTab : public Tab
{

};

class EditTab : public Tab
{

};

