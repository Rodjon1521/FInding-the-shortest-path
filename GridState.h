#ifndef GRIDSTATE_H
#define GRIDSTATE_H

#include "State.h"


class GridState :
	public State
{
private:

public:
	GridState(sf::RenderWindow* window);
	virtual ~GridState();

	void endState();
	void updateKeybinds();
	void update();
	void render(sf::RenderTarget* target = nullptr);
};

#endif // !GRIDSTATE_H







