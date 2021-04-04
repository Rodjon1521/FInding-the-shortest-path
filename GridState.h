#ifndef GRIDSTATE_H
#define GRIDSTATE_H

#include "State.h"
#include "MainMenuState.h"
#include "Map.h"

class GridState :
	public State
{
private:
	int tileSize = 30;
	sf::Vector2f startPos = { 0.f, 0.f };
	sf::Vector2f endPos = { 200.f, 200.f };
	Map* map;

public:
	GridState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~GridState();

	void endState();
	void updateKeybinds();
	void update();
	void render(sf::RenderTarget* target = nullptr);
};

#endif // !GRIDSTATE_H







