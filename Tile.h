#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <vector>


namespace tile {
	enum ID {
		Start, End, Path, Empty, Block
	};
}

class Tile
{
	tile::ID id;
	sf::Texture* texture;

	void IDtoTexture(tile::ID id);
public:
	sf::RectangleShape rect;

	Tile();
	Tile(sf::IntRect, tile::ID = tile::Empty);
};



#endif

