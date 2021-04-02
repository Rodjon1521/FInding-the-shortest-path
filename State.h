#ifndef STATE_H
#define STATE_H

#include <vector>
#include <stack>
#include <SFML/Graphics.hpp>

class State
{
private:
	sf::RenderWindow* window;
	std::vector<sf::Texture> textures;

public:
	State(sf::RenderWindow* window);
	virtual ~State();

	virtual void endState() = 0;

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};

#endif

