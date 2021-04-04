#include "Button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BUTTON_IDLE;

	this->rect.setPosition(sf::Vector2f(x, y));
	this->rect.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(12);
	this->text.setPosition(
		this->rect.getPosition().x + (this->rect.getGlobalBounds().width  / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->rect.getPosition().y + (this->rect.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->rect.setFillColor(this->idleColor);

}

Button::~Button()
{

}

const bool Button::isPressed() const
{
	if (this->buttonState == BUTTON_PRESSED)
		return true;
	return false;
}

void Button::update(const sf::Vector2f mousePos)
{
	this->buttonState = BUTTON_IDLE;
	if (this->rect.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BUTTON_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BUTTON_PRESSED;
		}
	}

	switch (this->buttonState)
	{
	case BUTTON_IDLE:
		this->rect.setFillColor(this->idleColor);
		break;
		
	case BUTTON_HOVER:
		this->rect.setFillColor(this->hoverColor);
		break;

	case BUTTON_PRESSED:
		this->rect.setFillColor(this->activeColor);
		break;

	default:
		this->rect.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->rect);
	target->draw(this->text);
}
