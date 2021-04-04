#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

enum button_states{BUTTON_IDLE = 0, BUTTON_HOVER, BUTTON_PRESSED};

class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape rect;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	const bool isPressed() const;

	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);


};

#endif