#pragma once
#include <vector>
#include <string>
#include "PathFollowing.h"
#include "Grid.h"
#include "PathfindingAlgorythm.h"
#include "Agent.h"
#include "Dijkstra.h"
#include "BFS.h"
#include "Greedy.h"
#include "A_Estrella.h"

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
	virtual std::vector<Agent*>* GetAgents() override { return &agents; };
	virtual Grid* GetGrid() override { return maze; };
	virtual Vector2D RandomPos() override;


private:
	std::vector<Agent*> agents;
	Vector2D coinPosition;

	PathfindingAlgorythm* pathFinder;
	PathFindingTypes pathType;

	Grid *maze;
	bool draw_grid;

	Vector2D coinLocations[20];

	int index = 0;
	void drawMaze();
	void drawCoin();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);
	virtual std::vector<Vector2D> calculateNewPath(Vector2D target) override;

};
