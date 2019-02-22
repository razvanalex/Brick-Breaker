#include "Brick.h"

/*
	Constructor for the brick. Initialize the width, height, the position, 
	maximum number of hits and the color.
*/
Brick::Brick(std::string name, unsigned int width, unsigned int height, float x,
	float y, int numHits, glm::vec3 color)
	: CollidableSquare(name, width, height, x, y, color)
{
	this->numHits = numHits;
	getRndPw = false;
}

/* 
	Desructor for the brick 
*/
Brick::~Brick()
{
}

/*
	Scale the brick. Used in animation of destroing the brick.
*/
void Brick::ScaleOff(float stepTime)
{
	this->ApplyTranformation(Transform2D::Scale(stepTime, stepTime));
}

/*
	Update the state of the brick. If number of hits is less than 0, generate 
	a random powerup and then destroy the brick.
*/
void Brick::Update(float gameTime)
{
	if (this->numHits <= 0) {
		if (getRndPw)
			getRndPw = false;
		this->Destroy(gameTime);
	}
}

/*
	Hit the brick. Reduce the number of hits.
*/
void Brick::Hit()
{
	this->numHits--;
	if (this->numHits == 0) {
		getRndPw = true;
	}
}

/*
	Getter for number of remaining hits
*/
int Brick::GetNumHits()
{
	return this->numHits;
}

/*
	Getter for getRndPw;
*/
bool Brick::GenerateRndPw()
{
	return this->getRndPw;
}

/*
	Destroy the brick. Apply the animation.
*/
void Brick::Destroy(float gameTime)
{
	scaleOffSpeed -= scaleOffSpeed * gameTime;
	this->SetSize(this->GetSize() * glm::pow(scaleOffSpeed, gameTime));
	ScaleOff(glm::pow(scaleOffSpeed, gameTime));
}
