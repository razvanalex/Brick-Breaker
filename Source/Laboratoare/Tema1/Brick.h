#pragma once

#include "CollidableSquare.h" 

/*
	Brick is a collidable square that can be destroied by the ball. Hitting it 
	for an amount of times, the brick will be destroied. An animation will be 
	applied to the brick. When number of hits is 0, a random powerup will be 
	generated. The brick only has a variable to signal other classes that 
	a powerup should be generated.
*/
class Brick : public CollidableSquare {
public:
	Brick(std::string name, unsigned int width, unsigned int height, float x, 
		float y, int numHits, glm::vec3 color);

	~Brick();

private:
	int numHits;
	bool getRndPw;
	float scaleOffSpeed = 0.1f;
	void ScaleOff(float stepTime);

public:
	void Update(float gameTime) override;
	void Hit();
	int GetNumHits();
	bool GenerateRndPw();
	void Destroy(float gameTime);
};