#include "DynamicScenePathFinding.h"

using namespace std;

DynamicScenePathFinding::DynamicScenePathFinding(PathFindingTypes type)
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	pathType = type;

	Agent *agent = new Agent(this, maze);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20,-20));

	Agent* agent2 = new Agent(this, maze);
	agent2->loadSpriteTexture("../res/soldier.png", 4);
	agent2->setBehavior(new PathFollowing);
	agent2->setTarget(Vector2D(-20, -20));

	agents.push_back(agent);
	agents.push_back(agent2);

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(817.77f, 563.64f);
	srand(1);
	agents[0]->setPosition(rand_cell);

	rand_cell = Vector2D(800.266f, 48.1198f);
	agents[1]->setPosition(rand_cell);

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

DynamicScenePathFinding::~DynamicScenePathFinding()
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

void DynamicScenePathFinding::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	default:
		break;
	}

	agents[0]->update(dtime, event);
	agents[1]->update(dtime, event);

	// if we have arrived to the coin, replace it in a random cell!

	for (int i = 0; i < 2; i++)
	{
		for (size_t o = 0; o < agents[i]->getPathSize(); o++)
		{
			size_t i2 = 0;
			if (i == 0)
				i2 = 1;

			/*for (size_t l = 0; l < agents[i2]->getPathSize(); l++)
			{
				if (Vector2D::Distance(agents[i]->getPosition(), agents[i2]->getPosition()) < 100 && agents[i]->getPathPoint(o) == agents[i2]->getPathPoint(l) && agents[i]->getPathPoint(o) != coinPosition)
				calculateNewPathSeparate(i2, false);
			}*/
		}
	}

	for (size_t i = 0; i < 2; i++)
	{
		if ((agents[i]->getCurrentTargetIndex() == -1) && (maze->pix2cell(agents[i]->getPosition()) == coinPosition))
		{
			coinPosition = Vector2D(-1, -1);

			if (index < 20)
			{
				coinPosition = coinLocations[index];
				//calculateNewPath();
				index++;
			}
		}
		/*else if(agents[i]->getPathSize() <= 0)
			calculateNewPathSeparate(i, true);*/
	}
}

/*void DynamicScenePathFinding::calculateNewPath()
{
	Vector2D cell = coinPosition;
	for (size_t i = 0; i < 2; i++)
	{
		if (maze->isValidCell(cell))
		{
			if (agents[i]->getPathSize() != 0) { agents[i]->clearPath(); }
			Vector2D pos = maze->pix2cell(agents[i]->getPosition());
			pathFinder = new A_Estrella();
			std::stack<Node*> pathfinding = pathFinder->calculatePath(&pos, &cell, agents[i]->GetBlackboard()->GetGraphPtr());
			while (!pathfinding.empty())
			{
				agents[i]->addPathPoint(maze->cell2pix(pathfinding.top()->GetPosition()));
				pathfinding.pop();
			}
		}
	}
}*/

std::stack<Node*> DynamicScenePathFinding::calculateNewPath(Vector2D target)
{
	Vector2D cell = target;
	if (maze->isValidCell(cell))
	{
		if (agents[0]->getPathSize() != 0) { agents[0]->clearPath(); }
		Vector2D pos = maze->pix2cell(agents[0]->getPosition());
		std::stack<Node*> pathfinding = pathFinder->calculatePath(&pos, &cell, agents[0]->GetBlackboard()->GetGraphPtr());
		return pathfinding;
	}

	return std::stack<Node*>();
}

void DynamicScenePathFinding::draw()
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

	agents[0]->draw();
	agents[1]->draw();
}

const char* DynamicScenePathFinding::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void DynamicScenePathFinding::drawMaze()
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

void DynamicScenePathFinding::drawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = {(int)coin_coords.x-offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}


bool DynamicScenePathFinding::loadTextures(char* filename_bg, char* filename_coin)
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
