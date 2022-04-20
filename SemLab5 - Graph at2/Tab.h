#pragma once
#include "Header.h"
#include "Checkbox.h"
#include "Button.h"

const unsigned int num_deco_texts = 2;

class Tab
{
private:
	sf::RectangleShape background;
	TabButton convert_btn;
	TabButton tab2;
	Checkbox oriented_box;
	TextBar text_tab;
	sf::Font* font;
	sf::Text deco_texts[num_deco_texts];
	void init_buttons(sf::Font* button_font, sf::Texture* check_box_texture);
	void init_deco_texts();
	void init_background(sf::RenderWindow* window);
public:
	Tab() { }
	~Tab() { }
	Tab(sf::RenderWindow* window, sf::Font* button_font, sf::Texture* check_box_texture) {
		init_background(window);
		init_buttons(button_font, check_box_texture);
		init_deco_texts();
	}
	sf::Vector2i get_bounds();
	int get_button_activated(sf::Vector2f(mouse_pos)) {
		if (this->convert_btn.is_selected(mouse_pos)) return 1;
		if (this->tab2.is_selected(mouse_pos)) return 2;
		if (this->oriented_box.is_under_mouse(mouse_pos)) return 3;
		return 0;
	}
	
	void update(sf::Vector2f mouse_pos) {
		this->convert_btn.update(mouse_pos);
		this->tab2.update(mouse_pos);
		this->text_tab.update(mouse_pos);
	}
	void render(sf::RenderTarget* target);
	Button* convert_button();
	Checkbox* oriented_check_box();
	TextBar* text_box();
};

