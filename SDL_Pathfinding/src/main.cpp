#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL_SimpleApp.h"
#include "ScenePathFindingMouse.h"
#include "DynamicScenePathFinding.h"

using namespace std;

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;
	
	SDL_SimpleApp *app = SDL_SimpleApp::Instance();

	Scene *curr_scene = new ScenePathFindingMouse(ScenePathFindingMouse::PathFindingTypes::BREADTH_FIRST_SEARCH);
	std::cout << "BREADTH FIRST SEARCH" << std::endl;
	app->setWindowTitle(curr_scene->getTitle());

	
	if (argc > 1) {
		cout << argv[1] << endl; 
		exit(0);
	}

	while (!quit)
	{
		// run app frame by frame
		event = app->run(curr_scene);

		/* Keyboard events */
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_1)
			{
				system("cls");
				std::cout << "BREADTH FIRST SEARCH" << std::endl;
				ScenePathFindingMouse::PathFindingTypes type = ScenePathFindingMouse::PathFindingTypes::BREADTH_FIRST_SEARCH;

				delete(curr_scene);
				curr_scene = new ScenePathFindingMouse(type);
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_2)
			{
				system("cls");
				std::cout << "DIJKSTRA" << std::endl;
				ScenePathFindingMouse::PathFindingTypes type = ScenePathFindingMouse::PathFindingTypes::DIJKSTRA;
				
				delete(curr_scene);
				curr_scene = new ScenePathFindingMouse(type);
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_3)
			{
				system("cls");
				std::cout << "GREEDY" << std::endl;
				ScenePathFindingMouse::PathFindingTypes type = ScenePathFindingMouse::PathFindingTypes::GREEDY;
				
				delete(curr_scene);
				curr_scene = new ScenePathFindingMouse(type);
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_4)
			{
				system("cls");
				std::cout << "A*" << std::endl;
				ScenePathFindingMouse::PathFindingTypes type = ScenePathFindingMouse::PathFindingTypes::A_ESTRELLA;
				
				delete(curr_scene);
				curr_scene = new ScenePathFindingMouse(type);
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_5)
			{
				system("cls");
				std::cout << "D*" << std::endl;
				DynamicScenePathFinding::PathFindingTypes type = DynamicScenePathFinding::PathFindingTypes::A_ESTRELLA;

				delete(curr_scene);
				curr_scene = new DynamicScenePathFinding(type);
				app->setWindowTitle(curr_scene->getTitle());
			}
			if ((event.key.keysym.scancode == SDL_SCANCODE_Q) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				quit = true;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
			{
				app->setFullScreen();
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}

	}

	return 0;
}