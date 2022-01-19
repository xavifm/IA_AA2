#pragma once
#include "SDL_SimpleApp.h"
#include "Path.h"
#include "SensorySystem.h"
#include "Blackboard.h"
#include "DecisionMakingAlgorithm.h"

class Blackboard;
class SensorySystem;
class Graph;
class Grid;
class DecisionMakingAlgorithm;

class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() = default;
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent, float dtime) {};
	};
private:
	enum class SceneTypes {PATH_FINDING, DYNAMIC_PATH_FINDING};

	SceneTypes type;

	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	Blackboard* blackboard;
	SensorySystem* sensors;

	// Pathfinding
	Path path;
	int currentTargetIndex;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

	DecisionMakingAlgorithm* decisionAlgorithm;

	bool isPlayer;

public:
	Agent(Scene* world, Grid* g, bool player);
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setBehavior(SteeringBehavior *behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	int getCurrentTargetIndex();
	int getPathSize();
	Vector2D getPathPoint(int idx);
	void clearPath();
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	void SetRandomTarget();
	void CalculatePath();

	Blackboard* GetBlackboard();
	
};
