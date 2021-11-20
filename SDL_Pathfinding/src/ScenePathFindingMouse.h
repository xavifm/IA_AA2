#pragma once
#include <vector>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Seek.h"
#include "PathFollowing.h"
#include "Grid.h"
#include "PathfindingAlgorythm.h"
#include "Graph.h"
#include "Dijkstra.h"
#include "BFS.h"
#include "Greedy.h"


class ScenePathFindingMouse :
	public Scene
{
public:
	ScenePathFindingMouse();
	~ScenePathFindingMouse();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D coinPosition;

	PathfindingAlgorythm* pathFinder;

	Grid *maze;
	bool draw_grid;
		
	void drawMaze();
	void drawCoin();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);

};
