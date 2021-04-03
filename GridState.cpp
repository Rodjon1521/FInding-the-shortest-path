#include "GridState.h"

GridState::GridState(sf::RenderWindow* window)
	: State(window)
{
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

}
