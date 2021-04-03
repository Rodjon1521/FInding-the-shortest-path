#ifndef APP_H
#define APP_H

#include<SFML/Graphics.hpp>
#include"GridState.h"
#include"MainMenuState.h"


class App
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;

	std::stack<State*> states;

	//Init
	void initWindow();
	void initStates();

public:
	//Constructors/Destructors
	App();
	virtual ~App();

	//Methods

	void endApp();

	void updateSFMLEvents();
	void update();

	void render();

	void run();
};

#endif