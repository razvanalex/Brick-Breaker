#pragma once
#include "Brick.h"
#include "PowerUp.h"
#include "Ball.h"
#include "CollisionDetection.h"

#include <vector>
#include <ctime>

/*
	Brick manager class is used to manage the bricks, the powerups and realize
	the communication between components.
*/
class BrickManager {
public:
	BrickManager(int procRandom);
	BrickManager(std::vector<Brick*> bricks, int procRandom);
	~BrickManager();

private:
	const int minDuration = 30;
	const int maxDuration = 60;
	const int pwSize = 20;

	int procRandom;
	std::vector<Brick*> bricks;
	std::vector<PowerUp*> powerUps;
	std::unordered_map<std::string, Mesh*> *meshes;
	Ball *ballRef;
	glm::vec2 paddlePos;
	glm::vec2 paddleSize;

	void GenerateRandomPowerUp(glm::vec2 position);

public:
	std::vector<Brick*> GetAllBricks();
	std::vector<PowerUp*> GetAllPowerUpsOnDisplay();
	std::vector<CollidableSquare*> GetAllCollidableSquares();

	void AddBrick(Brick* brick);
	void Update(float gameTime);
	void SetMeshes(std::unordered_map<std::string, Mesh*> &meshes);
	void SetPaddlePos(glm::vec2 paddlePos);
	void SetPaddleSize(glm::vec2 paddleSize);
	void SetBallRef(Ball* ball);
	void Reset();
	void SetBoard(int numHorizontal, int numVertical,
		int brickWidth, int brickHeight, int padding, glm::vec2 screenSize,
		int weight);
};