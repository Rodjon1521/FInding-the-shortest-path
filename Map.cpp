#include "Map.h"
#include <stdexcept>
#include <iostream>

Map::Map(int tileSize, int width, int height) :
	tileSize(tileSize), horizontalTiles(width / tileSize), width(width), height(height) {
	for (auto y = 0; y <= height; y += tileSize) {
		for (auto x = 170; x < width; x += tileSize) {
			Tile t(sf::IntRect(x, y, tileSize, tileSize));
			tiles.push_back(t);
		}
	}
}


Map::Map() = default;

//void Map::setIDtoTile(sf::Vector2f position, tile::ID id) {
//	float x = ((int)position.x / tileSize) * tileSize - 10;
//	float y = ((int)position.y / tileSize) * tileSize;
//
//	for (auto& tile : tiles)
//	{
//		if (id == tile::Start || id == tile::End) {
//			if (tile.getID() == id)
//				tile.setID(tile::Empty);
//			if (tile.rect.getPosition() == sf::Vector2f{ x,y })
//				tile.setID(id);
//		}
//		else
//			if (tile.rect.getPosition() == sf::Vector2f{ x,y })
//				tile.setID(id);
//	}
//}


void Map::draw(sf::RenderTarget & target, sf::RenderStates) const {
	for (const auto& tile : tiles)
		target.draw(tile.rect);
}
