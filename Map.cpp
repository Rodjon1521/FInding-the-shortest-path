#include "Map.h"
#include <stdexcept>

Map::Map(int tileSize, int width, int height, sf::Vector2f startPos, sf::Vector2f endPos) :
	tileSize(tileSize), horizontalTiles(width / tileSize), width(width), height(height) {
	startTile = Tile(sf::IntRect(startPos.x, startPos.y, tileSize, tileSize), tile::Start);
	endTile = Tile(sf::IntRect(endPos.x, endPos.y, tileSize, tileSize), tile::End);
	for (auto y = 0; y <= height; y += tileSize) {
		for (auto x = 0; x < width; x += tileSize) {
			Tile t(sf::IntRect(x, y, tileSize, tileSize));
			tiles.push_back(t);
		}
	}
	(*this)[startTile.getPosition()] = startTile;
	(*this)[endTile.getPosition()] = endTile;
}

Map::Map(const Map& world) = default;

Map& Map::operator=(const Map& other) = default;

inline int Map::indexAt(sf::Vector2f position) const {
	auto positionX = static_cast<int>(position.x),
		positionY = static_cast<int>(position.y);

	positionX = (positionX - (positionX % tileSize)) / tileSize;
	positionY = (positionY - (positionY % tileSize)) / tileSize;

	return (positionY * (horizontalTiles)+positionX);
}

void Map::setEverythingToEmpty() {
	for (auto& tile : tiles) {
		if (tile.getID() == tile::nonWalkable || tile.getID() == tile::Path) {
			tile.setID(tile::Empty);
		}
	}
}

Map::Map() = default;

Tile& Map::operator[](sf::Vector2f position) {
	return tiles[indexAt(position)];
}

const Tile& Map::operator[](sf::Vector2f position) const {
	return tiles[indexAt(position)];
}

void Map::setIDtoTile(sf::Vector2f position, tile::ID id) {
	return (*this)[position].setID(id);
}

void Map::clearPath() {
	for (auto& tile : tiles) {
		if (tile.getID() == tile::Path) tile.setID(tile::Empty);
	}
}

tile::ID Map::tileAt(sf::Vector2f position) const {
	return (*this)[position].getID();

}

bool Map::isOutOfBounds(sf::Vector2f position) const {
	return position.y < 0 || position.y >= height || position.x < 0 || position.x >= width;
}

bool Map::isWalkable(sf::Vector2f position) const {
	return (*this)[position].getID() != tile::nonWalkable;
}

const Tile& Map::getStart() const {
	for (const auto& tile : tiles) {
		if (tile.getID() == tile::Start) {
			return tile;
		}
	}
	throw std::out_of_range("There is no start in this map");
}

const Tile& Map::getEnd() const {
	for (const auto& tile : tiles) {
		if (tile.getID() == tile::End) {
			return tile;
		}
	}
	throw std::out_of_range("There is no end in this map");
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates) const {
	for (const auto& tile : tiles)
		target.draw(tile);
}


void Map::randomize() {

}