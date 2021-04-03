#include "App.h"

//Init
void App::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Finding the shortest path");
}

void App::initStates()
{
	this->states.push(new GridState(this->window));
	this->states.push(new MainMenuState(this->window));
}

//Constructors/Destructors
App::App()
{
	this->initWindow();
	this->initStates();
}

App::~App()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void App::endApp()
{
	std::cout << "Ending App" << std::endl;
}

//Methods
void App::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void App::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update();

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();	
		}
	}
	else
	{
		this->endApp();
		this->window->close();
	}
}

void App::render()
{
	this->window->clear();
	
	if (!this->states.empty())
	{
		this->states.top()->render(this->window);
	}

	this->window->display();
}

void App::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}
