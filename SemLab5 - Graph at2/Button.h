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
	void push_text(char ch) {
		if (this->text.getString().toAnsiString().length() < 12) //12???
		{
			if (ch != '|')
			{
				std::string str = "";
				for (int i = 0; i < text.getString().toAnsiString().length() - 1; i++)
				{
					str += text.getString().toAnsiString()[i];
				}
				this->text.setString(str += ch);
			}
			this->text.setString(this->text.getString().toAnsiString() += '|');
		}
		
	}
	void set_text(std::string text) {
		this->text.setString(text);
	}
	void erase_text() {
		if (this->text.getString().toAnsiString().length() > 1)
		{
			std::string str = "";
			for (int i = 0; i < text.getString().toAnsiString().length() - 2; i++)
			{
				str += text.getString().toAnsiString()[i];
			}
			str += '|';
			text.setString(str);
		}
	}
	Button() {

	}
	std::string get_text() {
		return this->text.getString().toAnsiString();
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
class TextBar : public Button
{
private:
	bool is_active = false;
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
};
