#pragma once
#include "Header.h"
#include "Checkbox.h"
#include "Button.h"

const unsigned int num_deco_texts = 3;

class Tab
{
private:
	sf::RectangleShape background;
	sf::RectangleShape output_bg;
	Button convert_btn;
	Button clear_btn;
	Button dfs_btn;
	Button bfs_btn;
	Checkbox oriented_box;
	Checkbox weight_matters;
	TextBar text_tab;
	sf::Font* font;
	sf::Text deco_texts[num_deco_texts];
	sf::Text output_text;
	void init_buttons(sf::Font* button_font, sf::Texture* check_box_texture);
	void init_deco_texts();
	void init_background(sf::RenderWindow* window);
	void init_output_text();
public:
	Tab() { }
	~Tab() { }
	Tab(sf::RenderWindow* window, sf::Font* button_font, sf::Texture* check_box_texture) {
		init_background(window);
		init_buttons(button_font, check_box_texture);
		init_deco_texts();
		init_output_text();
	}
	sf::Vector2i get_bounds();
	int get_button_activated(sf::Vector2f(mouse_pos)) {
		if (this->convert_btn.is_selected(mouse_pos)) return 1;
		if (this->clear_btn.is_selected(mouse_pos)) return 2;
		if (this->oriented_box.is_under_mouse(mouse_pos)) return 3;
		if (this->weight_matters.is_under_mouse(mouse_pos)) return 4;
		if (this->bfs_btn.is_selected(mouse_pos)) return 5;
		if (this->dfs_btn.is_selected(mouse_pos)) return 6;
		return 0;
	}
	void update_output_text(std::string str);
	void update(sf::Vector2f mouse_pos) {
		this->convert_btn.update(mouse_pos);
		this->dfs_btn.update(mouse_pos);
		this->bfs_btn.update(mouse_pos);
		this->clear_btn.update(mouse_pos);
		this->text_tab.update(mouse_pos);
	}
	void render(sf::RenderTarget* target);
	Button* convert_button();
	Button* dfs_button();
	Button* bfs_button();
	Button* clear_button();
	Checkbox* oriented_check_box();
	Checkbox* weight_box();
	TextBar* text_box();
};

