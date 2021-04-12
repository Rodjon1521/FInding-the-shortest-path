#include "Tile.h"

Tile::Tile() = default;

Tile::Tile(sf::IntRect intrect, tile::ID Id) :
	rect(sf::Vector2f(intrect.width, intrect.height)), id(Id) {
	rect.setFillColor(IDtoColor(id));
	setPosition(intrect.left, intrect.top);
	this->text.setString("");

	//make it look like a grid
	rect.setOutlineColor(sf::Color(160, 160, 160));
	rect.setOutlineThickness(.6f);
	
}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(rect, states);
	target.draw(text, states);
}

void Tile::setID(tile::ID id) {
	this->id = id;
	rect.setFillColor(IDtoColor(id));
}

tile::ID Tile::getID() const {
	return id;
}

void Tile::setText(std::string text, sf::Font* font)
{
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(15);
	this->text.setPosition(
		this->rect.getPosition().x-30 + (this->rect.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->rect.getPosition().y + (this->rect.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);
}

sf::Color Tile::IDtoColor(tile::ID id) {
	switch (id) {
	case tile::Empty: return sf::Color::White;
	case tile::Path: return sf::Color(0, 76, 132); //good looking blue
	case tile::Start: return sf::Color(200, 50, 50); //good looking red
	case tile::End: return sf::Color(250, 150, 100); //orange
	case tile::Wave: return sf::Color(244, 202, 22);
	default: return sf::Color::Black;
	}
}