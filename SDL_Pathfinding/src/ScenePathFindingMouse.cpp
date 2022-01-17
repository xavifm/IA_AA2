#include "ScenePathFindingMouse.h"

using namespace std;

void ScenePathFindingMouse::ChangeType(PathFindingTypes type)
{
	delete pathFinder;
	switch (type)
	{
	case PathFindingTypes::DIJKSTRA:
		pathFinder = new Dijkstra();
		break;
	case PathFindingTypes::A_ESTRELLA:
		pathFinder = new A_Estrella();
		break;
	case PathFindingTypes::GREEDY:
		pathFinder = new Greedy();
		break;
	case PathFindingTypes::BREADTH_FIRST_SEARCH:
		pathFinder = new BFS();
		break;
	}
}

Vector2D ScenePathFindingMouse::RandomPos()
{
	while(true) 
	{
		Vector2D ramdomVector = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));;
		if (maze->isValidCell(ramdomVector))
			return ramdomVector;
	}
}

ScenePathFindingMouse::ScenePathFindingMouse(PathFindingTypes type)
{
	ChangeType(type);
	draw_grid = false;
	maze = new Grid("../res/maze.csv");
	
	loadTextures("../res/maze.png", "../res/coin.png");

	pathType = type;

	Agent *agent = new Agent(this, maze);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20,-20));
	agents.push_back(agent);

	agent = new Agent(this, maze);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20, -20));
	agents.push_back(agent);

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1,-1);
	while (!maze->isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	agents[0]->setPosition(maze->cell2pix(Vector2D(rand_cell.x - 4, rand_cell.y)));
	agents[0]->setVelocity(Vector2D(0, -1));
	agents[0]->setTarget(agents[0]->getPosition());
	agents[1]->setPosition(maze->cell2pix(Vector2D(rand_cell.x - 4, rand_cell.y - 3)));
	agents[1]->setVelocity(Vector2D(0, 1));
	agents[1]->setTarget(agents[1]->getPosition());

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1,-1);
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell)<3))
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	//calculateNewPath();

	for (size_t i = 0; i < 20; i++)
	{
		coinLocations[i] = coinPosition;
		coinPosition = Vector2D(-1, -1);
		while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3))
			coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	}
	coinPosition = coinLocations[0];
}

ScenePathFindingMouse::~ScenePathFindingMouse()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}

	delete maze;
}

void ScenePathFindingMouse::update(float dtime, SDL_Event *event)
{
	for (size_t i = 0; i < agents.size(); i++)
	{
		agents[i]->update(dtime, event);

		// if we have arrived to the coin, replace it in a random cell!
		if ((agents[i]->getCurrentTargetIndex() == -1) && (maze->pix2cell(agents[i]->getPosition()) == coinPosition))
		{
			coinPosition = Vector2D(-1, -1);

			if(index < 20) 
			{
				coinPosition = coinLocations[index];
				//calculateNewPath();
				index++;
			}
		}
	}
}

std::vector<Vector2D> ScenePathFindingMouse::calculateNewPath(Vector2D target)
{
	std::vector<Vector2D> tmp;
	Vector2D cell = target;
	if (maze->isValidCell(cell))
	{
		if (agents[0]->getPathSize() != 0) { agents[0]->clearPath(); }
		Vector2D pos = maze->pix2cell(agents[0]->getPosition());
		std::stack<Node*> pathfinding = pathFinder->calculatePath(&pos, &cell, agents[0]->GetBlackboard()->GetGraphPtr());
		while (!pathfinding.empty())
		{
			tmp.push_back(maze->cell2pix(pathfinding.top()->GetPosition()));
			pathfinding.pop();
		}
	}

	return tmp;
}

void ScenePathFindingMouse::draw()
{
	drawMaze();
	drawCoin();

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i+=CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	for (size_t i = 0; i < agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* ScenePathFindingMouse::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void ScenePathFindingMouse::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{		
			if (!maze->isValidCell(Vector2D((float)i, (float)j)))
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			} else {
				// Do not draw if it is not necessary (bg is already black)
			}
					
			
		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void ScenePathFindingMouse::drawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = {(int)coin_coords.x-offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}


bool ScenePathFindingMouse::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}
