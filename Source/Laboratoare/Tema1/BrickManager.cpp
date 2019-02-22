#include "BrickManager.h"
#include <iostream>

/*
	Constructor for brick manager. procRandom is used to set the randomness of 
	powerups. This constructor initializes the vectors bricks and powerUps.
*/
BrickManager::BrickManager(int procRandom)
{
	bricks = std::vector<Brick*>();
	powerUps = std::vector<PowerUp*>();
	this->procRandom = procRandom;
	meshes = NULL;
}

/*
	Constructor for brick manager. It is used to set bricks vector with a 
	custom vector.
*/
BrickManager::BrickManager(std::vector<Brick*> bricks, int procRandom)
{
	powerUps = std::vector<PowerUp*>();
	this->bricks = bricks;
	this->procRandom = procRandom;
	meshes = NULL;
}

/*
	Destructor for brick manager
*/
BrickManager::~BrickManager()
{
}

/*
	Generate radom powerups. Each powerup square has it own color. The number of 
	powerups is limited to 100000000, but you have to play A LOT to reach this
	number.
*/
void BrickManager::GenerateRandomPowerUp(glm::vec2 position)
{
	int chance = rand() % procRandom;

	if (chance != 0 || meshes == NULL)
		return;

	char id[20];

	// Set the name
	do {
		memset(id, 0, sizeof(id));
		int rnd = rand() % 100000000;
		sprintf(id, "pw%d", rnd);
	} while ((*meshes)[id] != NULL);
	
	int pwID = rand() % ((int)PowerUpsEnum::Count - 1) + 1;
	glm::vec3 color;

	// Set powerup square color
	switch (pwID)
	{
		case PowerUpsEnum::WALL:
			color = glm::vec3(.5f, .5f, 0);
			break;
		case PowerUpsEnum::BIG_BALL:
			color = glm::vec3(.5f, 0, .5f);
			break;
		case PowerUpsEnum::STRONG_BALL:
			color = glm::vec3(0, .5f, .5f);
			break;
		default:
			break;
	}

	// Init powerup
	PowerUpsEnum pw = static_cast<PowerUpsEnum>(pwID);
	float randDuration = (float)(rand() % (maxDuration - minDuration)) +
		minDuration;
	PowerUp *p = new PowerUp(id, pwSize, pwSize, position.x, position.y, color, 
		pw, randDuration);

	// Put powerup in vector and in meshes map.
	powerUps.push_back(p);
	(*meshes)[id] = p->CreateMesh();
}

/*
	Add brick to manager
*/
void BrickManager::AddBrick(Brick * brick)
{
	bricks.push_back(brick);
}

/*
	Get all bricks from manager
*/
std::vector<Brick*> BrickManager::GetAllBricks()
{
	return this->bricks;
}

/*
	Gett all powerup on screen
*/
std::vector<PowerUp*> BrickManager::GetAllPowerUpsOnDisplay()
{
	return this->powerUps;
}

/*	
	Get all collidable squares that have numHits != 0
*/
std::vector<CollidableSquare*> BrickManager::GetAllCollidableSquares()
{
	std::vector<CollidableSquare*> vect = std::vector<CollidableSquare*>();

	for (Brick* b : bricks) {
		if (b->GetNumHits() != 0)
			vect.push_back(b);
	}

	return vect;
}

/*
	Setter for meshes
*/
void BrickManager::SetMeshes(std::unordered_map<std::string, Mesh*> &meshes)
{
	this->meshes = &meshes;
}

/*
	Setter for paddle position
*/
void BrickManager::SetPaddlePos(glm::vec2 paddlePos)
{
	this->paddlePos = paddlePos;
}

/*
	Setter for paddle size
*/
void BrickManager::SetPaddleSize(glm::vec2 paddleSize)
{
	this->paddleSize = paddleSize;
}

/*
	Setter for ballRef
*/
void BrickManager::SetBallRef(Ball * ball)
{
	this->ballRef = ball;
}

/*
	Reset (clear) vectors
*/
void BrickManager::Reset()
{
	this->bricks.clear();
	this->powerUps.clear();
}

/*
	Set the bricks on the board. 
*/
void BrickManager::SetBoard(int numHorizontal, int numVertical,
	int brickWidth, int brickHeight, int padding, glm::vec2 screenSize, 
	int weight)
{
	for (int i = 0; i < numVertical; i++) {
		for (int j = 0; j < numHorizontal; j++) {
			// Generate position for the brick
			int index = i * numHorizontal + j;
			float x = brickWidth / 2.0f +
				(screenSize.x - numHorizontal * brickWidth - (numHorizontal - 1) 
					* padding) / 2.0f + j * (brickWidth + padding);
			float y = brickHeight / 2.0f + 275 + i * (brickHeight + padding);

			// Generate name for the brick
			std::string name = "brick" + std::to_string(index);

			// Compute the new color
			float r = 1.0f / (float)weight;
			float g = r < 0.2f ? 1.0f : 1.0f / (float)weight;
			float b = g < 0.2f ? 1.0f : 1.0f - 1.0f / (float)weight;
			glm::vec3 color = glm::vec3(r, g, b);
			

			// From level 6, generate random colors
			if (r < 0.2f && b > 0.7f && g > 0.9f)
				color = glm::vec3((float)rand() / RAND_MAX, 
				(float)rand() / RAND_MAX, (float)rand() / RAND_MAX);

			// Create brick and add it to brick manager
			Brick *brick = new Brick(name, brickWidth, brickHeight, x, y,
				weight, color);
			this->AddBrick(brick);
		}
	}
}

/*
	Update the bricks vector (the brick with numHits == 0 will be destroyed and 
	removed form the vector) and powerups vector.
*/
void BrickManager::Update(float gameTime)
{
	// Update bricks vector
	std::vector<Brick*>::iterator it = bricks.begin();
	while (it != bricks.end()) {
		Brick* b = *it;
		if (b->GetNumHits() == 0) {
			// The brick is hit. Generate powerup
			if (b->GenerateRndPw())
				GenerateRandomPowerUp(b->GetPosition());
			if (b->GetSize().x <= 0.1f && b->GetSize().y <= 0.1f) {
				// The brick is too small. Remove it from vector
				it = bricks.erase(it);
			}
			else {
				// Go to next element
				it++;
			}
		}
		else {
			// Go to next element
			it++;
		}
	}

	// Update each brick
	for (Brick *b : bricks) {
		b->Update(gameTime);
	}

	// Update powerUps vector
	std::vector<PowerUp*>::iterator itP = powerUps.begin();
	while (itP != powerUps.end()) {
		PowerUp* p = *itP;

		// Update each powerUps
		p->Update(gameTime);
	
		// Check collision with the paddle
		glm::vec2 start = paddlePos + glm::vec2(-paddleSize.x / 2, paddleSize.y / 2);
		glm::vec2 end = paddlePos + glm::vec2(paddleSize.x / 2, paddleSize.y / 2);
		float radius = 10;
		
		if (CollisionDetection::CollisionWithSegment(start, end, radius,
			p->GetPosition(), p->GetPosition(), NULL, NULL))
		{
			itP = powerUps.erase(itP);
			this->ballRef->SetPowerUp(p->GetPowerUp(), p->GetDuration());
		}
		else {
			itP++;
		}
	}
}
