#include "Tab.h"

void Tab::init_buttons() {
	sf::Vector2f beginning = this->background.getPosition();
	sf::Vector2f tab_offset = sf::Vector2f(20.f, 20.f);
	this->font.loadFromFile("Fonts//prstart.ttf");
	this->tab1 = TabButton(beginning + tab_offset, sf::Vector2f(64, 20), "Add", &this->font, 0);
	tab_offset = sf::Vector2f(20.f, 60.f);
	this->tab2 = TabButton(beginning + tab_offset, sf::Vector2f(64, 20), "Edit", &this->font, 1);
}

sf::Vector2i Tab::get_bounds()
{
	return sf::Vector2i(int(this->background.getPosition().x), int(this->background.getPosition().y));
}

void Tab::init_background(sf::RenderWindow* window)
{
	float width = 192.f;
	float height = 128.f;
	this->background.setFillColor(sf::Color(200, 200, 255));
	this->background.setPosition(window->getSize().x - width, window->getSize().y - height);
	this->background.setSize(sf::Vector2f(width, height));
}
void Tab::render(sf::RenderTarget* target) {
	target->draw(this->background);
	this->tab1.render(target);
	this->tab2.render(target);
}