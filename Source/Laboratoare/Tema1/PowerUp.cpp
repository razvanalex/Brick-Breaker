#include "PowerUp.h"

/*
	Constructor for powerups. It sets the porperties of a collidable square and 
	set the powerup and the duration of it.
*/
PowerUp::PowerUp(std::string name, unsigned int width, unsigned int height, 
	float x, float y, glm::vec3 color, PowerUpsEnum powerUp, float duration)
	: CollidableSquare(name, width, height, x, y, color)
{
	this->position = glm::vec2(x, y);
	this->angle = 0;
	this->powerUp = powerUp;
	this->duration = duration;
}

/*
	Destructor for powerup
*/
PowerUp::~PowerUp()
{
}

/*
	Animate the powerup square. The square falls and rotates at the same time.
*/
void PowerUp::Animate(float angularSpeed, float fallSpeed)
{	
	this->position += glm::vec2(0, fallSpeed);
	this->angle += angularSpeed;

	this->SetModelMatrix(
		Transform2D::Translate(this->position.x, this->position.y) *
		Transform2D::Scale((float)this->GetWidth(), (float)this->GetHeight()) *
		Transform2D::Rotate(angle));
} 

/*
	Update the powerup square. Animate it.
*/
void PowerUp::Update(float gameTime)
{
	Animate(angularSpeed * gameTime, fallSpeed * gameTime);
}

/*
	Getter for position
*/
glm::vec2 PowerUp::GetPosition()
{
	return this->position;
}

/* 
	Getter for powerup
*/
PowerUpsEnum PowerUp::GetPowerUp()
{
	return this->powerUp;
}

/*
	Getter for duration
*/
float PowerUp::GetDuration()
{
	return this->duration;
}
