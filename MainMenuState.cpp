#include "MainMenuState.h"

void MainMenuState::initFonts()
{
	this->font.loadFromFile("Fonts/arial.ttf");
}

void MainMenuState::initButtons()
{
	this->buttons["GRID_BUTTON"] = new Button(100, 250, 300, 100,
		&this->font, "Grid",
		sf::Color(40, 40, 40, 255), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["QUIT_BUTTON"] = new Button(100, 500, 300, 100,
		&this->font, "Quit",
		sf::Color(40, 40, 40, 255), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->bgTexture.loadFromFile("Textures/bg.png");
	this->background.setTexture(&this->bgTexture);
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	initFonts();
	initButtons();
	initBackground();
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

	if (this->buttons["GRID_BUTTON"]->isHover())
	{
		this->gridRect.setSize(sf::Vector2f(700.0, 450.0));
		this->gridRect.setPosition(sf::Vector2f(500.0, 200.0));
		this->grid.loadFromFile("Textures/grid.jpg");//загружаем в него файл
		this->gridRect.setTexture(&this->grid);
		this->gridRect.setFillColor(sf::Color::White);
	}
	else
	{
		this->gridRect.setFillColor(sf::Color(255, 255, 255, 0));
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
	target->draw(this->gridRect);
	this->renderButtons(target);

}

