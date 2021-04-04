#ifndef STATE_H
#define STATE_H

#include <vector>
#include <stack>
#include <iostream>
#include <SFML/Graphics.hpp>

class State
{
protected:
	sf::RenderWindow* window;
	bool quit;

	std::stack<State*>* states;

private:
	std::vector<sf::Texture> textures;

	

public:

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();
	virtual void endState() = 0;

	virtual void updateMousePos();
	virtual void updateKeybinds() = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};

#endif

