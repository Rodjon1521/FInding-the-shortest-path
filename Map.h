#ifndef MAP_H
#define MAP_H

#include <random>
#include "Tile.h"


class Map : public sf::Drawable {
	int tileSize, horizontalTiles;

	sf::Font font;

	void initMap(int x, int y, int width, int height);
	
	std::vector<Tile> tiles;


	inline int indexAt(sf::Vector2f position) const;

public:
	Map(int tileSize, int width, int height);
	Map();

	int width, height;
	std::vector<std::vector<int>> grid;
	sf::Vector2i endPos;

	Tile& operator[](sf::Vector2f position);
	const Tile& operator[](sf::Vector2f position) const;

	tile::ID tileAt(sf::Vector2f position) const;

	void setIDtoTile(sf::Vector2f position, tile::ID id);
	void setTexttoTile(sf::Vector2f position, std::string str);

	const Tile& getStart() const;
	const Tile& getEnd() const;
	

	void clearPath(int x, int y, int width, int height);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif

