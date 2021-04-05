#include "GridState.h"

void GridState::initButtons()
{
	this->buttons["START_BUTTON"] = new Button(10, 10, 150, 50,
		&this->font, "Start",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["END_BUTTON"] = new Button(10, 70, 150, 50,
		&this->font, "End",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EMPTY_BUTTON"] = new Button(10, 130, 150, 50,
		&this->font, "Empty",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["BLOCK_BUTTON"] = new Button(10, 190, 150, 50, &this->font, "Block", button_textures::BLOCK_TEXTURE);
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
	map = new Map(tileSize, this->window->getSize().x, this->window->getSize().y);
	//this->path((sf::Vector2i)this->startPos, (sf::Vector2i)this->endPos);
}

GridState::~GridState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

/*void GridState::path(sf::Vector2i startPos, sf::Vector2i endPos)
{
	int w = this->window->getSize().x / this->tileSize;
	int h = this->window->getSize().y / this->tileSize;
	int** grid = new int*[h];
	for (int i = 0; i < h; i++) grid[i] = new int[w];

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++)
			grid[i][j] = -2;
	}

	int* px = new int[w * h];
	int* py = new int[w * h];

	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };

	int d, x, y, k;
	bool stop;

	d = 0;
	grid[startPos.y / this->tileSize][startPos.x / this->tileSize] = 0;
	do {
		stop = true;               // предполагаем, что все свободные клетки уже помечены
		for (y = 0; y < h; ++y)
			for (x = 0; x < w; ++x)
				if (grid[y][x] == d)                         // ячейка (x, y) помечена числом d
				{
					for (k = 0; k < 4; ++k)                    // проходим по всем непомеченным соседям
					{
						int iy = y + dy[k], ix = x + dx[k];
						if (iy >= 0 && iy < h && ix >= 0 && ix < w &&
							grid[iy][ix] == -2)
						{
							stop = false;              // найдены непомеченные клетки
							grid[iy][ix] = d + 1;      // распространяем волну
						}
					}
				}
		d++;
	} while (!stop && grid[endPos.y / this->tileSize][endPos.x / this->tileSize] == -2);



	// восстановление пути
	x = endPos.x / this->tileSize;
	y = endPos.y / this->tileSize;
	d = grid[endPos.y / this->tileSize][endPos.x / this->tileSize];
	while (d > 0)
	{
		px[d] = x;
		py[d] = y;                // записываем ячейку (x, y) в путь
		d--;
		for (k = 0; k < 4; ++k)
		{
			int iy = y + dy[k], ix = x + dx[k];
			if (iy >= 0 && iy < h && ix >= 0 && ix < w &&
				grid[iy][ix] == d)
			{
				x = x + dx[k];
				y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
				break;
			}
		}
	}
	px[0] = startPos.x / this->tileSize;
	py[0] = startPos.y / this->tileSize;


	for (int i = 0; i < endPos.y / this->tileSize + endPos.x / this->tileSize; i++)
		std::cout << px[i] << " " << py[i] << std::endl;


	for (int i = 0; i < endPos.y / this->tileSize + endPos.x / this->tileSize; i++)
		map->setIDtoTile(sf::Vector2f(px[i] * this->tileSize, py[i] * this->tileSize), tile::Path);
}*/

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
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->mousePosView.x > 170)
	//{
	//	map->setIDtoTile(this->mousePosView, id);
	//}

	this->updateKeybinds();
	this->updateMousePos();

	this->updateButtons();

	if (this->buttons["START_BUTTON"]->isPressed()) id = tile::Start;

	if (this->buttons["END_BUTTON"]->isPressed()) id = tile::End;

	if (this->buttons["EMPTY_BUTTON"]->isPressed()) id = tile::Empty;


	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << std::endl;
	//system("cls");
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
	this->window->draw(*map);
	this->renderButtons(target);
}
