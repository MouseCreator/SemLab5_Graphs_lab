#include "Program.h"

bool Program::text_bar_input() {
	if (this->tab.get_text_bar_active() == false) return false;
	static float time_passed = 0.f;
	static bool waiting = false;
	if (!waiting) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) { this->tab.update_text_bar('0'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { this->tab.update_text_bar('1'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { this->tab.update_text_bar('2'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) { this->tab.update_text_bar('3'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) { this->tab.update_text_bar('4'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) { this->tab.update_text_bar('5'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) { this->tab.update_text_bar('6'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) { this->tab.update_text_bar('7'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) { this->tab.update_text_bar('8'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) { this->tab.update_text_bar('9'); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) { this->tab.update_text_bar(-1); waiting = true; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			update_current_weight(); 
			this->tab.set_text_bar_active(false);
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
	std::string str = this->tab.get_text_bar_text();
	if (str == "") {
		current_weight = 0;
	}
	else if (str.length() > 5) {
		current_weight = 99999;
	}
	else {
		this->current_weight = stoi(str);
	}
	this->tab.update_text_bar(std::to_string(this->current_weight));
}