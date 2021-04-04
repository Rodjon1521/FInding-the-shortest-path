#include "MainMenuState.h"

void MainMenuState::initFonts()
{
	this->font.loadFromFile("Fonts/arial.ttf");
}

void MainMenuState::initButtons()
{
	this->buttons["GRID_BUTTON"] = new Button(100, 100, 150, 50,
		&this->font, "Grid",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["QUIT_BUTTON"] = new Button(100, 300, 150, 50,
		&this->font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	initFonts();
	initButtons();

	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{  
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::endState()
{
	std::cout << "ENDING MAINMENUSTATE" << std::endl;
}

void MainMenuState::updateKeybinds()
{
	this->checkForQuit();
}

void MainMenuState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
}

void MainMenuState::update()
{
	this->updateKeybinds();
	this->updateMousePos();

	this->updateButtons();

	if (this->buttons["QUIT_BUTTON"]->isPressed())
	{
		this->quit = true;
	}

	if (this->buttons["GRID_BUTTON"]->isPressed())
	{
		this->states->push(new GridState(this->window, this->states));
	}
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) 
		target = this->window;

	target->draw(this->background);
	this->renderButtons(target);

}

