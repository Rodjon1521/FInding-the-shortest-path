#ifndef MAP_H
#define MAP_H

#include <random>
#include "Tile.h"


class Map : public sf::Drawable {
	int tileSize, horizontalTiles;
	int width, height;
	std::vector<Tile> tiles;
	Tile endTile, startTile;

public:
	Map(int tileSize, int width, int height);
	Map();

	void setIDtoTile(sf::Vector2f position, tile::ID id);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif

