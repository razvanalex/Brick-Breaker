#pragma once

#include "CollidableSquare.h" 

/*
	This enumaration is used to identify each powerup. Also, there is 
	NO_POWERUP state when the ball does not have any powerup, and a counter 
	to make things easier.
*/
enum PowerUpsEnum {
	NO_POWERUP, WALL, BIG_BALL, STRONG_BALL, Count
};

/*
	The powerup class is a collidable square that, when caught by the paddle,
	it gives to the ball certain powers. 
*/
class PowerUp : public CollidableSquare {
public:
	PowerUp(std::string name, unsigned int width, unsigned int height, float x,
		float y, glm::vec3 color, PowerUpsEnum powerUp, float duration);

	~PowerUp();

private:
	float angularSpeed = 3.0f;
	float fallSpeed = -200.0f;
	void Animate(float angularSpeed, float fallSpeed);
	glm::vec2 position;
	float angle;
	PowerUpsEnum powerUp;
	float duration;

public:
	void Update(float gameTime) override;
	glm::vec2 GetPosition();
	PowerUpsEnum GetPowerUp();
	float GetDuration();
};