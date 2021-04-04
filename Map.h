#ifndef MAP_H
#define MAP_H

#include <random>
#include "Tile.h"


class Map : public sf::Drawable {
	int tileSize, horizontalTiles;
	int width, height;
	std::vector<Tile> tiles;
	Tile endTile, startTile;

	inline int indexAt(sf::Vector2f position) const;
	void setEverythingToEmpty();

public:
	Map(int tileSize, int width, int height, sf::Vector2f startPos, sf::Vector2f endPos);
	Map();
	Map(const Map& world);
	Map& operator=(const Map& other);

	Tile& operator[](sf::Vector2f position);
	const Tile& operator[](sf::Vector2f position) const;

	const Tile& getStart() const;
	const Tile& getEnd() const;
	tile::ID tileAt(sf::Vector2f position) const;
	void setIDtoTile(sf::Vector2f position, tile::ID id);

	bool isWalkable(sf::Vector2f position) const;
	bool isOutOfBounds(sf::Vector2f position) const;

	void clearPath();

	void randomize();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif

