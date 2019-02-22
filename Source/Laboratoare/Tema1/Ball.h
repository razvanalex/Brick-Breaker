#pragma once
#include "Circle.h"
#include "CollidableSquare.h"
#include "Transform2D.h"
#include "CollisionDetection.h"
#include "Brick.h"
#include "PowerUp.h"

#include <string>

/*
	This class represents the ball that moves along the screen. The ball has 
	a velocity vector that represents the direction and the speed of the ball.
	(In physics, velocity is a vector, and speed is the magnitude of that 
	vector). The ball detects collision with walls, bricks and the paddle. 

	The collision with the paddle is described as being the relative position 
	on Ox of the ball w.r.t the position of the paddle, but applied to it 
	arccosinus. The value is limited to [-0.99, +0.99] to avoid 0 angle when
	the ball hits the corder of the paddle. 

	The collision with the walls and bricks are done the same. Each object, 
	which is a rectangle, has got each side segment parametrized. Therefore, 
	each segment has the following equation:
	x(t) = x0 + t * (x1 - x0) and y(t) = y0 + t * (y1 - y0), with t form 0 to 1.
	The collision with a segment is done by parametrizing the segment and the 
	direction. Considering the distance between the 2 segments (the minimum 
	distance between any point from each segment) less than the radius of the 
	circle will give a rought approximation of the collision. For high speeds,
	the ball will not leave the paddle, because it cannot go to the next 
	position (most probably, the there will be collision with a segment).

	The reflected vector is computed for each hit with the brick/wall. Thus,
	when colliding with 2 bricks at the same time, one will actually not be hit
	by the ball. 

	To win the game faster, there are some powerups. These will modify the 
	properties of the ball to make it much stronger. The available powerup are:
	Wall, Strong Ball and Big ball. These are described in Ball.cpp. You cannot 
	have multiple powerup on the same time. 
*/
class Ball : public Circle {
	public:
		Ball(std::string name, unsigned int radius, float x, float y,
			glm::vec3 color);
		~Ball();

	private:
		const float MAX_VELOCITY = 500;
		const int NUMBER_OF_BALLS = 3;

		unsigned int radius;
		glm::vec2 position;
		float acceleration;
		glm::vec2 velocity;
		bool sticked;
		std::vector<CollidableSquare*> collidableObjs;
		PowerUpsEnum crtPowerUp;
		float powerUpTimer;
		bool bottomWall;
		int crtNumBalls;
		std::vector<Circle*> balls;
		unsigned int old_radius;
		bool strongBall;


		glm::vec2 FromParamEqToCoord(glm::vec2 p1, glm::vec2 p2, float t);
		float DistanceTwoPoints(glm::vec2 p1, glm::vec2 p2);
		void UpdateModelMatrix();
		bool DetectCollision(float gameTime);
		bool ReflectPaddle(glm::vec2 paddlePos, glm::vec2 paddleSize, 
			float gameTime);
		bool ReflectBall(glm::vec2 start, glm::vec2 end, float gameTime, 
			bool brick);
		void PlayWithPowerUp(float gameTime);
		void InitBalls();

	public:
		unsigned int GetRadius();
		void SetRadius(unsigned int radius);
		glm::vec2 GetPosition();
		float GetAcceleration();
		void SetAcceleration(float acceleration);
		glm::vec2 GetVelocity();
		void SetVelocity(glm::vec2 velocity);
		bool IsSticked();
		void SetSticked(bool sticked);
		void AddNearCollidableObjs(std::vector<CollidableSquare*> objs);
		void ClearCollidableObjs();
		void DeployOnClick(glm::vec2 paddlePos, glm::vec2 paddleSize);
		void Update(float gameTime, glm::vec2 paddlePos, glm::vec2 paddleSize);
		void InitPosition(glm::vec2 paddlePos, glm::vec2 paddleSize);
		bool ResetOnOffScreen(glm::vec2 windowSize, glm::vec2 paddlePos,
			glm::vec2 paddleSize);
		void SetPowerUp(PowerUpsEnum pw, float duration);
		bool IsBottomWallActive();
		void ResetNumBalls();
		int GetNumBalls();
		std::vector<Circle*> GetBalls();
};
