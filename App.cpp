#include "App.h"

//Init
void App::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Finding the shortest path");
}

void App::initStates()
{
	this->states.push(new GridState(this->window));
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
