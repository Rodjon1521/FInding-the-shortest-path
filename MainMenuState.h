#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <map>

#include "State.h"
#include "Button.h"
#include "GridState.h"

class MainMenuState :
	public State
{
private:
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	void initFonts();
	void initButtons();

public:
	MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~MainMenuState();

	void endState();
	void updateKeybinds();
	void updateButtons();
	void update();
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};

#endif // !MAINMENUSTATE





