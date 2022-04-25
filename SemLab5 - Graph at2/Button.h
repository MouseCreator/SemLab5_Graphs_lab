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
	bool under_mouse(sf::Vector2f mouse_pos) {
		return this->shape.getGlobalBounds().contains(mouse_pos);
	}
	bool is_selected(sf::Vector2f mouse_position);
	void set_text(std::string text) {
		this->text.setString(text);
	}
	
	Button() {

	}
	std::string get_text() {
		return this->text.getString().toAnsiString();
	}
	~Button() {
	}
};

class TextBar : public Button
{
private:
	bool is_active = false;
	int max_chars = 12;
	std::string my_text;
public:
	TextBar() {}
	~TextBar() {}
	TextBar(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font* font)
		: Button(position, size, text, font) {
	}
	bool get_is_active() {
		return this->is_active;
	}
	void set_is_active(bool state) {
		this->is_active = state;
	}
	void erase_text() {
		if (my_text.size() > 0) {
			my_text = my_text.substr(0, my_text.size() - 1);
		}
		this->set_text(my_text + '|');
	}
	void update_text(char ch) {
		if (ch == -1)
			erase_text();
		else
			push_text(ch);
	}
	void push_text(char ch) {
		if (my_text.length() < max_chars)
			my_text += ch;
		this->set_text(my_text + '|');
	}
	void add_column() {
		this->set_text(my_text + '|');
	}
	std::string get_text() {
		return this->my_text;
	}
	void update_text(std::string str) {
		this->my_text = str;
		this->set_text(my_text);
	}
};
