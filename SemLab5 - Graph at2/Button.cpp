#include "Button.h"

bool Button::is_selected(sf::Vector2f mouse_position) {
	if (this->shape.getGlobalBounds().contains(mouse_position))
		return true;
	return false;

}

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font *font) {
	this->shape.setPosition(position);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setSize(size);
	this->shape.setOutlineThickness(2.f);
	this->shape.setFillColor(sf::Color::White);
	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setPosition(sf::Vector2f(this->shape.getPosition().x + 4.f, this->shape.getPosition().y + 4.f));
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(12);
	selected = false;
	was_selected = false;
}
void Button::render(sf::RenderTarget* target) {
	target->draw(this->shape);
	target->draw(this->text);
}
void Button::update(sf::Vector2f mouse_position) {
	if (is_selected(mouse_position)) {
		if (was_selected == false) {
			this->shape.setFillColor(sf::Color(200, 200, 200));
			was_selected = true;
		}
	}
	else {
		if (was_selected == true) {
			this->shape.setFillColor(sf::Color::White);
			was_selected = false;
		}
	}
}