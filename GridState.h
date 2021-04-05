#ifndef GRIDSTATE_H
#define GRIDSTATE_H

#include "State.h"
#include "MainMenuState.h"
#include "Button.h"
#include "Map.h"

class GridState :
	public State
{
private:
	int tileSize = 50;
	sf::Vector2f startPos;
	sf::Vector2f endPos;
	Map* map;

	tile::ID id = tile::Empty;

	sf::Font font;

	std::map<std::string, Button*> buttons;

	void initButtons();
	void initFonts();
public:
	GridState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~GridState();

	void path(sf::Vector2i startPos, sf::Vector2i endPos);

	void endState();
	void updateKeybinds();
	void updateButtons();
	void update();
	void renderButtons(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = nullptr);
};

#endif // !GRIDSTATE_H







