#ifndef GRIDSTATE_H
#define GRIDSTATE_H

#include "State.h"
#include "MainMenuState.h"

class GridState :
	public State
{
private:

public:
	GridState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~GridState();

	void endState();
	void updateKeybinds();
	void update();
	void render(sf::RenderTarget* target = nullptr);
};

#endif // !GRIDSTATE_H







