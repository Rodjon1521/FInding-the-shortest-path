#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window)
	: State(window)
{
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::endState()
{
	std::cout << "ENDING MAINMENUSTATE" << std::endl;
}

void MainMenuState::updateKeybinds()
{
	this->checkForQuit();
}

void MainMenuState::update()
{
	this->updateKeybinds();
	this->updateMousePos();

	std::cout << this->mousePosView.x << " " << this->mousePosView.y << std::endl;
	system("cls");
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
}

