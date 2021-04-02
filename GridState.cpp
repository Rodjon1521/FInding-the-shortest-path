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

}

void GridState::update()
{
	std::cout << "HELLO FROM GRIDSTATE" << std::endl;
}

void GridState::render(sf::RenderTarget* target)
{

}
