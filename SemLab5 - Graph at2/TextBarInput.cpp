#include "Program.h"

bool Program::text_bar_input() {
	if (this->tab.text_box()->get_is_active() == false) return false;
	static float time_passed = 0.f;
	static char waiting_tag = -2;
	char prev_waiting = waiting_tag;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) or sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) { waiting_tag = '0'; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) or sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) { waiting_tag = '1'; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) or sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) { waiting_tag = '2'; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) or sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) { waiting_tag = '3'; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) or sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) { waiting_tag = '4'; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) or sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) { waiting_tag = '5'; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) or sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) { waiting_tag = '6'; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) or sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)) { waiting_tag = '7'; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) or sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) { waiting_tag = '8'; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) or sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)) { waiting_tag = '9'; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) { waiting_tag = '-'; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) { waiting_tag = -1; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		update_current_weight(); 
		this->tab.text_box()->set_is_active(false);
	}
	else {
		waiting_tag = -2; //no key pressed
	}
	if (waiting_tag != -2) // if is waiting
	{
		if (prev_waiting == waiting_tag) { // if timer is the same
			time_passed += this->delta_time;
			if (time_passed > min_delay) {
				waiting_tag = -2;
				time_passed -= min_delay;
			}
		}
		else { //set new timer
			time_passed = 0.f;
			this->tab.text_box()->update_text(waiting_tag);
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