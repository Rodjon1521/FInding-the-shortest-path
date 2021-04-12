#include "Map.h"
#include <stdexcept>
#include <iostream>

Map::Map(int tileSize, int width, int height) :
	tileSize(tileSize), horizontalTiles(width / tileSize), width(width), height(height) {
	this->initMap(200, 30, width - 30, height - 30);
	this->font.loadFromFile("Fonts/arial.ttf");
}

void Map::initMap(int x, int y, int width, int height)
{
	for (int py = y; py < height; py += tileSize) {
		for (int px = x; px < width; px += tileSize) {
			Tile t(sf::IntRect(px, py, tileSize, tileSize), tile::Empty);
			tiles.push_back(t);
		}
	}

	grid.assign((height - y) / tileSize, std::vector<int>((width - x) / tileSize));
	for (int py = 0; py < (height-y)/tileSize; py++) {
		for (int px = 0; px < (width-x)/tileSize; px++) {
			grid[py][px] = -2;
		}
	}
}

inline int Map::indexAt(sf::Vector2f position) const {
	auto positionX = static_cast<int>(position.x),
		positionY = static_cast<int>(position.y);

	positionX = (positionX - (positionX % tileSize)) / tileSize;
	positionY = (positionY - (positionY % tileSize)) / tileSize;

	return (positionY * (horizontalTiles)+positionX);
}

Tile& Map::operator[](sf::Vector2f position) {
	return tiles[indexAt(position)];
}

const Tile& Map::operator[](sf::Vector2f position) const {
	return tiles[indexAt(position)];
}


Map::Map() = default;

void Map::setIDtoTile(sf::Vector2f position, tile::ID id) {
	float x = ((int)position.x / tileSize) * tileSize - 10;
	float y = ((int)position.y / tileSize) * tileSize;

	for (auto& tile : tiles)
	{
		if (id == tile::Start || id == tile::End) {
			if (tile.getID() == id)
				tile.setID(tile::Empty);
			if (tile.getPosition() == sf::Vector2f{ x,y }) {
				tile.setID(id);
				if (id == tile::Start)
					grid[(tile.getPosition().y - 30) / tileSize][(tile.getPosition().x - 200) / tileSize] = 0;
				if (id == tile::End)
					endPos = { (int)((tile.getPosition().x - 200) / tileSize), (int)((tile.getPosition().y - 30)) / tileSize };
			}
		}
		else
			if (tile.getPosition() == sf::Vector2f{ x,y }) {
				tile.setID(id);
				if(id == tile::nonWalkable)
					grid[(tile.getPosition().y - 30) / tileSize][(tile.getPosition().x - 200) / tileSize] = -1;
			}
	}
}

void Map::setTexttoTile(sf::Vector2f position, std::string str)
{
	for (auto& tile : tiles)
	{
		if (tile.getPosition() == position) {
			tile.setText(str, &this->font);
		}
	}
}


void Map::draw(sf::RenderTarget & target, sf::RenderStates) const {
	for (const auto& tile : tiles)
		target.draw(tile);
}

const Tile& Map::getStart() const {
	for (const auto& tile : tiles) {
		if (tile.getID() == tile::Start) {
			return tile;
		}
	}
}

const Tile& Map::getEnd() const {
	for (const auto& tile : tiles) {
		if (tile.getID() == tile::End) {
			return tile;
		}
	}
}

void Map::clearPath(int x, int y, int width, int height) {
	for (int py = 0; py < (height - y) / tileSize; py++) {
		for (int px = 0; px < (width - x) / tileSize; px++) {
			grid[py][px] = -2;
		}
	}

	for (auto& tile : tiles) {
		tile.setText("", &this->font);
		if (tile.getID() == tile::Path || tile.getID() == tile::Wave) {
			tile.setID(tile::Empty);
		}
		if (tile.getID() == tile::Start)
			grid[(tile.getPosition().y - 30) / tileSize][(tile.getPosition().x - 200) / tileSize] = 0;
		if (tile.getID() == tile::End) {
			endPos = { (int)((tile.getPosition().x - 200) / tileSize), (int)((tile.getPosition().y - 30)) / tileSize };
		}
		if (tile.getID() == tile::nonWalkable)
			grid[(tile.getPosition().y - 30) / tileSize][(tile.getPosition().x - 200) / tileSize] = -1;
	}

}

tile::ID Map::tileAt(sf::Vector2f position) const {
	return (*this)[position].getID();

}
