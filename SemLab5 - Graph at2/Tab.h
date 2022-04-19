#pragma once
#include "Header.h"
#include "Button.h"
const unsigned int num_deco_texts = 2;
class Tab
{
private:
	sf::RectangleShape background;
	TabButton tab1;
	TabButton tab2;
	TextBar text_box;
	sf::Font* font;
	sf::Text deco_texts [num_deco_texts];
	void init_buttons(sf::Font* button_font);
	void init_deco_texts();
	void init_background(sf::RenderWindow* window);
public:
	Tab() { }
	~Tab() { }
	Tab(sf::RenderWindow* window, sf::Font* button_font) {
		init_background(window);
		init_buttons(button_font);
		init_deco_texts();
	}
	sf::Vector2i get_bounds();
	bool get_text_bar_active() {
		return this->text_box.get_is_active();
	}
	bool text_bar_under_mouse(sf::Vector2f mouse_pos) {
		return this->text_box.under_mouse(mouse_pos);
	}
	void set_text_bar_active(bool state) {
		this->text_box.set_is_active(state);
	}
	void update_text_bar(char ch) {
		if (ch != -1)
			this->text_box.push_text(ch);
		else
			this->text_box.erase_text();
	}
	void update_text_bar(std::string to_set) {
		this->text_box.update_text(to_set);
	}
	std::string get_text_bar_text() {
		return this->text_box.get_text();
	}
	void add_column_to_text_bar() {
		this->text_box.add_column();
	}
	void update(sf::Vector2f mouse_pos) {
		this->tab1.update(mouse_pos);
		this->tab2.update(mouse_pos);
		this->text_box.update(mouse_pos);
	}
	void render(sf::RenderTarget* target);
};

class AddingTab : public Tab
{

};

class EditTab : public Tab
{

};

