#include "Tab.h"

void Tab::init_buttons(sf::Font* button_font, sf::Texture* check_box_texture) {
	this->font = button_font;
	sf::Vector2f distance_between_btns = sf::Vector2f(0.f, 25.f);
	sf::Vector2f beginning = this->background.getPosition();
	sf::Vector2f tab_offset = sf::Vector2f(10.f, 20.f);
	this->convert_btn = Button(beginning + tab_offset, sf::Vector2f(72, 20), "Convert", button_font);
	tab_offset += distance_between_btns;
	this->clear_btn = Button(beginning + tab_offset, sf::Vector2f(72, 20), "Clear", button_font);
	tab_offset += distance_between_btns;
	this->bfs_btn = Button(beginning + tab_offset, sf::Vector2f(72, 20), "BFS", button_font);
	tab_offset += distance_between_btns;
	this->dfs_btn = Button(beginning + tab_offset, sf::Vector2f(72, 20), "DFS", button_font);
	tab_offset += distance_between_btns;
	this->connected_btn = Button(beginning + tab_offset, sf::Vector2f(72, 20), "Connected", button_font);
	tab_offset += distance_between_btns;
	this->cycle_btn = Button(beginning + tab_offset, sf::Vector2f(72, 20), "Cycled", button_font);
	tab_offset = sf::Vector2f(240.f, 20.f);
	this->component_btn = Button(beginning + tab_offset, sf::Vector2f(72, 20), "Components", button_font);

	tab_offset = sf::Vector2f(100.f, 20.f);
	this->text_tab = TextBar(beginning + tab_offset, sf::Vector2f(128, 32), "Enter weight", button_font);

	this->oriented_box = Checkbox("Oriented", font);
	tab_offset = sf::Vector2f(100.f, 60.f);
	this->oriented_box.init_sprite(beginning + tab_offset, check_box_texture);

	this->weight_matters = Checkbox("Sort by weight", font);
	tab_offset += distance_between_btns;
	this->weight_matters.init_sprite(beginning + tab_offset, check_box_texture);

	this->to_vector = Checkbox("Bitvector mode", font);
	tab_offset += distance_between_btns;
	this->to_vector.init_sprite(beginning + tab_offset, check_box_texture);

	this->auto_convert = Checkbox("Autoconvert", font);
	tab_offset += distance_between_btns;
	this->auto_convert.init_sprite(beginning + tab_offset, check_box_texture);

	

}
void Tab::init_deco_texts() {
	sf::Vector2f beginning = this->background.getPosition();
	sf::Vector2f tab_offset = sf::Vector2f(100.f, 2.f);
	this->deco_texts[0].setFillColor(sf::Color::Black);
	this->deco_texts[0].setFont(*this->font);
	this->deco_texts[0].setPosition(beginning + tab_offset);
	this->deco_texts[0].setString("Weight: ");
	this->deco_texts[0].setCharacterSize(10);

	tab_offset = sf::Vector2f(10.f, 2.f);
	this->deco_texts[1].setFillColor(sf::Color::Black);
	this->deco_texts[1].setFont(*this->font);
	this->deco_texts[1].setPosition(beginning + tab_offset);
	this->deco_texts[1].setString("Mode: ");
	this->deco_texts[1].setCharacterSize(10);

	tab_offset = sf::Vector2f(0.f, -14.f);
	this->deco_texts[2].setFillColor(sf::Color::Black);
	this->deco_texts[2].setFont(*this->font);
	this->deco_texts[2].setPosition(this->output_bg.getPosition() + tab_offset);
	this->deco_texts[2].setString("Output: ");
	this->deco_texts[2].setCharacterSize(10);

}

void Tab::update(sf::Vector2f mouse_pos) {
	this->convert_btn.update(mouse_pos);
	this->dfs_btn.update(mouse_pos);
	this->bfs_btn.update(mouse_pos);
	this->clear_btn.update(mouse_pos);
	this->component_btn.update(mouse_pos);
	this->connected_btn.update(mouse_pos);
	this->cycle_btn.update(mouse_pos);
	this->text_tab.update(mouse_pos);
}
sf::Vector2i Tab::get_bounds()
{
	return sf::Vector2i(int(this->background.getPosition().x), int(this->background.getPosition().y));
}

void Tab::init_background(sf::RenderWindow* window)
{
	float width = 320.f;
	float height = 284.f;
	this->background.setFillColor(sf::Color(200, 200, 255));
	this->background.setPosition(window->getSize().x - width, window->getSize().y - height);
	this->background.setSize(sf::Vector2f(width, height));

	width -= 12;
	height = 72.f;
	float offset = 6.f;
	this->output_bg.setFillColor(sf::Color(255, 255, 255));
	this->output_bg.setPosition(window->getSize().x - width - offset, window->getSize().y - height - offset);
	this->output_bg.setSize(sf::Vector2f(width, height));
}
void Tab::init_output_text()
{
	sf::Vector2f beginning = this->output_bg.getPosition();
	sf::Vector2f tab_offset = sf::Vector2f(2.f, 2.f);
	this->output_text.setFillColor(sf::Color::Black);
	this->output_text.setFont(*this->font);
	this->output_text.setPosition(beginning + tab_offset);
	this->output_text.setString("");
	this->output_text.setCharacterSize(12);
}
void Tab::update_output_text(std::string str)
{
	const int max_char_in_a_row = 40;
	int length = 0;
	int current_char = 0;
	std::string to_set;
	std::stringstream ss;
	ss << str;
	std::string temp;
	while (true) {
		ss >> temp;
		if (ss.fail())
			break;
		else {
			length = temp.length();
			if (current_char + length > max_char_in_a_row) {
				to_set += '\n';
				current_char = length;
			}
			else {
				current_char += length;
			}
			to_set += temp;
			to_set += ' ';
			current_char++;
		}
	}
	this->output_text.setString(to_set);

}
void Tab::render(sf::RenderTarget* target) {
	target->draw(this->background);
	target->draw(this->output_bg);
	this->convert_btn.render(target);
	this->bfs_btn.render(target);
	this->dfs_btn.render(target);
	this->clear_btn.render(target);
	this->connected_btn.render(target);
	this->cycle_btn.render(target);
	this->component_btn.render(target);
	for (int i = 0; i < num_deco_texts; i++) {
		target->draw(deco_texts[i]);
	}
	this->text_tab.render(target);
	this->oriented_box.render(target);
	this->weight_matters.render(target);
	this->auto_convert.render(target);
	this->to_vector.render(target);
	target->draw(this->output_text);
}

Button* Tab::convert_button() {
	return &this->convert_btn;
}
Button* Tab::dfs_button()
{
	return &this->dfs_btn;
}
Button* Tab::bfs_button()
{
	return &this->bfs_btn;
}
Button* Tab::clear_button()
{
	return &this->clear_btn;
}
Button* Tab::connected_button()
{
	return &this->connected_btn;
}
Button* Tab::component_button()
{
	return &this->component_btn;
}
Button* Tab::cycle_button()
{
	return &this->cycle_btn;
}
Checkbox* Tab::oriented_check_box() {
	return &this->oriented_box;
}
Checkbox* Tab::weight_box()
{
	return &this->weight_matters;
}
Checkbox* Tab::to_vector_box()
{
	return &this->to_vector;
}
Checkbox* Tab::autoconvert_box()
{
	return &this->auto_convert;
}
TextBar* Tab::text_box() {
	return &this->text_tab;
}