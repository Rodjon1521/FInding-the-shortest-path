#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"
#include "Button.h"

class MainMenuState :
	public State
{
private:
	sf::RectangleShape background;

public:
	MainMenuState(sf::RenderWindow* window);
	virtual ~MainMenuState();

	void endState();
	void updateKeybinds();
	void update();
	void render(sf::RenderTarget* target = nullptr);
};

#endif // !MAINMENUSTATE





