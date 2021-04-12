#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace tile {
	enum ID {
		Start, End, Path, Empty, nonWalkable, Wave
	};
}

class Tile : public sf::Drawable, public sf::Transformable {
	sf::RectangleShape rect;
	tile::ID id;
	sf::Font* font;
	sf::Text text;

	static sf::Color IDtoColor(tile::ID id);
public:
	explicit Tile(sf::IntRect intrect, tile::ID id = tile::Empty);
	Tile();

	void setID(tile::ID id);
	tile::ID getID() const;

	void setText(std::string text, sf::Font* font);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};