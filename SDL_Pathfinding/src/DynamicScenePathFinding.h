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
#include "A_Estrella.h"
#include "Blackboard.h"


class DynamicScenePathFinding :
	public Scene
{
	
public:
	enum class PathFindingTypes { DIJKSTRA, A_ESTRELLA, GREEDY, BREADTH_FIRST_SEARCH};
	DynamicScenePathFinding() {};
	DynamicScenePathFinding(PathFindingTypes);
	~DynamicScenePathFinding();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
	void ChangeType(PathFindingTypes);
	
private:
	std::vector<Agent*> agents;
	Vector2D coinPosition;

	PathfindingAlgorythm* pathFinder;
	PathFindingTypes pathType;

	Grid *maze;
	bool draw_grid;

	Vector2D coinLocations[20];

	int index = 0;
	
	void calculateNewPath();
	void calculateNewPathSeparate(int pos, bool searchCoin);
	void drawMaze();
	void drawCoin();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);

};
