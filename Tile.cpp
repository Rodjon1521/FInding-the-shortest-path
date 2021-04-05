#include "Tile.h"


Tile::Tile() = default;

Tile::Tile(sf::IntRect intrect, tile::ID Id) :
	rect(sf::Vector2f(intrect.width, intrect.height)), id(Id) {
	rect.setPosition(intrect.left, intrect.top);

	this->texture = new sf::Texture();
	this->texture->loadFromFile("textures/grass.jpg");
	//IDtoTexture(id);
	rect.setTexture(this->texture);
	//make it look like a grid
}


void Tile::IDtoTexture(tile::ID id) {
	switch (id) {
	case tile::Empty: this->texture->loadFromFile("textures/grass.jpg"); break;
	//case tile::Path: return sf::Color(0, 76, 132); //good looking blue
	//case tile::Start: return sf::Color(200, 50, 50); //good looking red
	//case tile::End: return sf::Color(250, 150, 100); //orange
	case tile::Block: this->texture->loadFromFile("textures/block.png"); break;
	default: break;
	}
}

