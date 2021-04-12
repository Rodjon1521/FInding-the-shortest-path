#include "GridState.h"

void GridState::initButtons()
{
	this->buttons["START_BUTTON"] = new Button(10, 10, 180, 70,
		&this->font, "Start",
		sf::Color(40, 40, 40, 255), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["END_BUTTON"] = new Button(10, 110, 180, 70,
		&this->font, "End",
		sf::Color(40, 40, 40, 255), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EMPTY_BUTTON"] = new Button(10, 210, 180, 70,
		&this->font, "Empty",
		sf::Color(40, 40, 40, 255), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["BLOCK_BUTTON"] = new Button(10, 310, 180, 70,
		&this->font, "Block",
		sf::Color(40, 40, 40, 255), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["DIAGONALLY"] = new Button(10, 450, 180, 70,
		&this->font, "Diagonaly",
		sf::Color(40, 40, 40, 255), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["CLEAR_BUTTON"] = new Button(10, 550, 180, 70,
		&this->font, "Clear",
		sf::Color(40, 40, 40, 255), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["PATH_BUTTON"] = new Button(10, 650, 180, 70,
		&this->font, "Path",
		sf::Color(40, 40, 40, 255), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	
}

void GridState::initFonts()
{
	this->font.loadFromFile("Fonts/arial.ttf");
}

GridState::GridState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	initFonts();
	initButtons();
	this->background.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->background.setFillColor(sf::Color(40,40,40,255));
	map = new Map(tileSize, this->window->getSize().x, this->window->getSize().y);
	map->setIDtoTile(sf::Vector2f{ 230.0, 30.0 }, tile::Start);
	map->setIDtoTile(sf::Vector2f{ 1250.0, 660.0 }, tile::End);
}

GridState::~GridState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void GridState::path()
{
	std::vector<int> dx;
	std::vector<int> dy;
	if (this->canMoveDiagonally) {
		dx = { 1, 0, -1, 0, 1,1,-1,-1 };
		dy = { 0, 1, 0, -1, 1,-1,1,-1 };
	}
	else
	{
		dx = { 1, 0, -1, 0 };
		dy = { 0, 1, 0, -1 };
	}



	int d, x, y, k;
	bool stop = false;
	d = 0;
	while (!stop && map->grid[map->endPos.y][map->endPos.x] == -2){
		stop = true;               // предполагаем, что все свободные клетки уже помечены
		for (y = 0; y < map->grid.size(); ++y)
			for (x = 0; x < map->grid[y].size(); ++x)
				if (map->grid[y][x] == d)                         // ячейка (x, y) помечена числом d
				{
					for (k = 0; k < dx.size(); ++k)                    // проходим по всем непомеченным соседям
					{
						int iy = y + dy[k], ix = x + dx[k];
						if (iy >= 0 && iy < map->grid.size() && ix >= 0 && ix < map->grid[y].size() &&
							map->grid[iy][ix] == -2 && map->grid[iy][ix] != -1)
						{
							map->grid[iy][ix] = d + 1;      // распространяем волну
							map->setIDtoTile(sf::Vector2f{ (float)((ix + 1) * tileSize + 200), (float)(iy * tileSize + 30) }, tile::Wave);
							map->setTexttoTile(sf::Vector2f{ (float)((ix + 1) * tileSize + 200), (float)(iy * tileSize + 30) }, std::to_string(d));
							this->window->draw(*map);
							this->window->display();
							for (int i = 0; i < 1000; i++);
							stop = false;              // найдены непомеченные клетки
							
						}
					}
				}
		d++;
	} 
	map->setIDtoTile(sf::Vector2f{ (float)((map->endPos.x + 1) * tileSize + 200), (float)(map->endPos.y * tileSize + 30) }, tile::End);

	std::vector<sf::Vector2f> p;
	x = map->endPos.x;
	y = map->endPos.y;
	d = map->grid[map->endPos.y][map->endPos.x];
	while (d > 0)
	{
		if(d!= map->grid[map->endPos.y][map->endPos.x])
			p.push_back(sf::Vector2f{ (float)((x+1)*tileSize+200), (float)(y*tileSize+30) });
		d--;
		for (k = 0; k < dx.size(); ++k)
		{
			int iy = y + dy[k], ix = x + dx[k];
			if (iy >= 0 && iy < map->grid.size() && ix >= 0 && ix < map->grid[iy].size() &&
				map->grid[iy][ix] == d)
			{
				x = x + dx[k];
				y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
				break;
			}
		}
	}

	for (int i = 0; i < p.size(); i++) {
		map->setIDtoTile(p[i], tile::Path);
		this->window->draw(*map);
		this->window->display();
		for (int i = 0; i < 100000; i++);
	}
}

void GridState::endState()
{
	std::cout << "ENDING GRIDSTATE" << std::endl;
}

void GridState::updateKeybinds()
{
	this->checkForQuit();
}

void GridState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
}

void GridState::update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->mousePosView.x > 200)
	{
		map->setIDtoTile(this->mousePosView, id);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		this->states->push(new MainMenuState(this->window, this->states));

	this->updateKeybinds();
	this->updateMousePos();

	this->updateButtons();
	this->startPos = map->getStart().getPosition();
	this->endPos = map->getEnd().getPosition();

	if (this->buttons["START_BUTTON"]->isPressed()) id = tile::Start;
	if (this->buttons["END_BUTTON"]->isPressed()) id = tile::End;
	if (this->buttons["BLOCK_BUTTON"]->isPressed()) id = tile::nonWalkable;
	if (this->buttons["EMPTY_BUTTON"]->isPressed()) id = tile::Empty;

	if (this->buttons["PATH_BUTTON"]->isPressed()) this->path();
	if(this->buttons["CLEAR_BUTTON"]->isPressed()) map->clearPath(200,30,this->window->getSize().x-30, this->window->getSize().y-30);
	if (this->buttons["DIAGONALLY"]->isPressed()) this->canMoveDiagonally = !this->canMoveDiagonally;
}

void GridState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void GridState::render(sf::RenderTarget* target)
{
	this->window->clear();
	this->window->draw(this->background);
	this->window->draw(*map);
	this->renderButtons(target);
}
