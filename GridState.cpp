#include "GridState.h"

GridState::GridState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	map = new Map(tileSize, this->window->getSize().x, this->window->getSize().y, startPos, endPos);
}

GridState::~GridState()
{
}

void GridState::endState()
{
	std::cout << "ENDING GRIDSTATE" << std::endl;
}

void GridState::updateKeybinds()
{
	this->checkForQuit();
}

void GridState::update()
{
	this->updateKeybinds();
	this->updateMousePos();
}

void GridState::render(sf::RenderTarget* target)
{
	this->window->clear();
	this->window->draw(*map);
}
