#pragma once
#include "Header.h"
class Checkbox
{
private:
	bool is_avaialable;
	bool checked;
	sf::Sprite sprite;
	sf::Texture* texture;
	sf::Text text;
	sf::IntRect rect;
	bool is_selected;
	void update_texture() {
		this->rect = sf::IntRect(16 * !this->is_avaialable, 16 * this->checked, 16, 16);
		this->sprite.setTextureRect(this->rect);
		if (this->is_avaialable) {
			this->text.setFillColor(sf::Color(0, 0, 0));
		}
		else {
			this->text.setFillColor(sf::Color(72, 72, 72));
		}
	}
public:
	Checkbox() 
	{ 
	}
	Checkbox(std::string text, sf::Font* font, bool checked = false, bool is_avaliable = true) {
		this->checked = checked;
		this->is_avaialable = is_avaliable;
		this->text.setFont(*font);
		this->text.setCharacterSize(10);
		this->text.setString(text);
	}
	bool is_under_mouse(sf::Vector2f mouse_position) {
		return this->sprite.getGlobalBounds().contains(mouse_position);
	}
	void init_sprite(sf::Vector2f pos, sf::Texture* texture) {
		this->sprite.setPosition(pos);
		this->sprite.setTexture(*texture);
		this->text.setPosition(pos.x + 16.f, pos.y);
		this->update_texture();
	}
	void render(sf::RenderTarget* target) {
		target->draw(this->sprite);
		target->draw(this->text);
	}
	void change_state() {
		if (this->is_avaialable)
		{
			this->checked = !this->checked;
		}
		update_texture();
	}
	void set_avaliable(bool value) {
		this->is_avaialable = value;
		update_texture();
	}
	bool get_state() {
		return this->checked;
	}
	~Checkbox() {
	}
};

