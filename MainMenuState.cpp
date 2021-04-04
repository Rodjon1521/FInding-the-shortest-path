#include "MainMenuState.h"

void MainMenuState::initFonts()
{
	this->font.loadFromFile("Fonts/arial.ttf");
}

MainMenuState::MainMenuState(sf::RenderWindow* window)
	: State(window)
{
	initFonts();

	this->appstate_btn = new Button(100, 100, 150, 50,
		&this->font, "GRID",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
	delete this->appstate_btn;
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

	this->appstate_btn->update(this->mousePosView);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->appstate_btn->render(target);
}

