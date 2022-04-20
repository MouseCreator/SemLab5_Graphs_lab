#include "Tab.h"

void Tab::init_buttons(sf::Font* button_font, sf::Texture* check_box_texture) {
	this->font = button_font;
	sf::Vector2f beginning = this->background.getPosition();
	sf::Vector2f tab_offset = sf::Vector2f(20.f, 20.f);
	this->convert_btn = TabButton(beginning + tab_offset, sf::Vector2f(72, 20), "Convert", button_font, 0);
	tab_offset = sf::Vector2f(20.f, 60.f);
	this->tab2 = TabButton(beginning + tab_offset, sf::Vector2f(72, 20), "Edit", button_font, 1);
	tab_offset = sf::Vector2f(100.f, 20.f);
	this->text_tab = TextBar(beginning + tab_offset, sf::Vector2f(128, 32), "Enter weight", button_font);
	this->oriented_box = Checkbox("Oriented", font);
	tab_offset = sf::Vector2f(100.f, 60.f);
	this->oriented_box.init_sprite(beginning + tab_offset, check_box_texture);

}

void Tab::init_deco_texts() {
	sf::Vector2f beginning = this->background.getPosition();
	sf::Vector2f tab_offset = sf::Vector2f(100.f, 2.f);
	this->deco_texts[0].setFillColor(sf::Color::Black);
	this->deco_texts[0].setFont(*this->font);
	this->deco_texts[0].setPosition(beginning + tab_offset);
	this->deco_texts[0].setString("Weight: ");
	this->deco_texts[0].setCharacterSize(10);

	tab_offset = sf::Vector2f(20.f, 2.f);
	this->deco_texts[1].setFillColor(sf::Color::Black);
	this->deco_texts[1].setFont(*this->font);
	this->deco_texts[1].setPosition(beginning + tab_offset);
	this->deco_texts[1].setString("Mode: ");
	this->deco_texts[1].setCharacterSize(10);
}
sf::Vector2i Tab::get_bounds()
{
	return sf::Vector2i(int(this->background.getPosition().x), int(this->background.getPosition().y));
}

void Tab::init_background(sf::RenderWindow* window)
{
	float width = 256.f;
	float height = 128.f;
	this->background.setFillColor(sf::Color(200, 200, 255));
	this->background.setPosition(window->getSize().x - width, window->getSize().y - height);
	this->background.setSize(sf::Vector2f(width, height));
}
void Tab::render(sf::RenderTarget* target) {
	target->draw(this->background);
	this->convert_btn.render(target);
	this->tab2.render(target);
	for (int i = 0; i < num_deco_texts; i++) {
		target->draw(deco_texts[i]);
	}
	this->text_tab.render(target);
	this->oriented_box.render(target);
}

Button* Tab::convert_button() {
	return &this->convert_btn;
}
Checkbox* Tab::oriented_check_box() {
	return &this->oriented_box;
}
TextBar* Tab::text_box() {
	return &this->text_tab;
}