#include "Program.h"

bool Program::text_bar_input() {
	if (this->tab.text_box()->get_is_active() == false) return false;
	static float time_passed = 0.f;
	static bool waiting = false;
	if (!waiting) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) { this->tab.text_box()->update_text('0'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { this->tab.text_box()->update_text('1'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { this->tab.text_box()->update_text('2'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) { this->tab.text_box()->update_text('3'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) { this->tab.text_box()->update_text('4'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) { this->tab.text_box()->update_text('5'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) { this->tab.text_box()->update_text('6'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) { this->tab.text_box()->update_text('7'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) { this->tab.text_box()->update_text('8'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) { this->tab.text_box()->update_text('9'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) { this->tab.text_box()->update_text('-'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) { this->tab.text_box()->update_text(-1); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			update_current_weight(); 
			this->tab.text_box()->set_is_active(false);
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) or
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) or
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) or
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) or
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) or
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) or
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) or
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) or
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) or
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) or
			sf::Keyboard::isKeyPressed(sf::Keyboard::Dash) or
			sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
			time_passed += this->delta_time;
			if (time_passed > min_delay) {
				waiting = false;
				time_passed -= min_delay;
			}
		}
		else {
			waiting = false;
			time_passed = 0.f;
		}
	}
	return true;
}
void Program::update_current_weight() {
	std::string str = this->tab.text_box()->get_text();
	if (str == "") {
		current_weight = 0;
	}
	else if (str.length() > 5) {
		current_weight = 99999;
	}
	else {
		this->current_weight = stoi(str);
	}
	this->tab.text_box()->update_text(std::to_string(this->current_weight));
}