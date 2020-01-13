#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
class ControlEntradas {
public:
	ControlEntradas() {

	}
	bool spriteMouseHover(Sprite &obj, RenderWindow &win,bool origenCentro=false) {
		IntRect tmpRect;
		if (origenCentro) {
			tmpRect.left = obj.getPosition().x- obj.getGlobalBounds().width/2;
			tmpRect.top = obj.getPosition().y- obj.getGlobalBounds().height/2;
			tmpRect.width = obj.getGlobalBounds().width;
			tmpRect.height = obj.getGlobalBounds().height;
		}
		else {
			tmpRect.left = obj.getPosition().x;
			tmpRect.top = obj.getPosition().y;
			tmpRect.width = obj.getGlobalBounds().width;
			tmpRect.height = obj.getGlobalBounds().height;
		}

		if (tmpRect.contains(Mouse::getPosition(win))) {
			return true;
		}
		return false;
	}
	bool spriteMouseClick(Sprite &obj, RenderWindow &win,bool origenCentro = false) {
		if (Mouse::isButtonPressed(Mouse::Button::Left)) {
			IntRect tmpRect;
			if (origenCentro) {
				tmpRect.left = obj.getPosition().x - obj.getGlobalBounds().width / 2;
				tmpRect.top = obj.getPosition().y - obj.getGlobalBounds().height / 2;
				tmpRect.width = obj.getGlobalBounds().width;
				tmpRect.height = obj.getGlobalBounds().height;
			}
			else {
				tmpRect.left = obj.getPosition().x;
				tmpRect.top = obj.getPosition().y;
				tmpRect.width = obj.getGlobalBounds().width;
				tmpRect.height = obj.getGlobalBounds().height;
			}
			if (tmpRect.contains(Mouse::getPosition(win))) {
				return true;
			}
		}
		return false;

	}

};