#include "Ball.h"

#include <iostream>

/*
	Create a ball object with default values. 
*/
Ball::Ball(std::string name, unsigned int radius, float x, float y, 
	glm::vec3 color) : Circle(name, color, glm::mat3(1), true)
{
	this->radius = radius;
	this->position = glm::vec2(x, y);
	this->sticked = true;
	this->acceleration = 0;
	this->velocity = glm::vec3(0);
	this->collidableObjs = std::vector<CollidableSquare*>();

	// Set variables for powerups
	this->crtPowerUp = PowerUpsEnum::NO_POWERUP;
	this->powerUpTimer = 0;
	this->bottomWall = false;
	this->old_radius = radius;
	this->strongBall = false;

	// Init number of lifes
	InitBalls();

	// Init the model matrix
	UpdateModelMatrix();
}

/* 
	Default ball destructor 
*/
Ball::~Ball()
{
	// Destroy life balls from memory
	for (Circle *b : balls) {
		delete b;
	}
}

/*
	 Compute point position from parametrized equations
*/
glm::vec2 Ball::FromParamEqToCoord(glm::vec2 p1, glm::vec2 p2, float t)
{
	float x = p1.x + t * (p2.x - p1.x);
	float y = p1.y + t * (p2.y - p1.y);
	return glm::vec2(x, y);
}

/*
	Compute the distance between 2 points
*/
float Ball::DistanceTwoPoints(glm::vec2 p1, glm::vec2 p2)
{
	return glm::sqrt(glm::pow(p2.x - p1.x, 2) + glm::pow(p2.y - p1.y, 2));
}

/*
	Update the model matrix by setting the scale and the position matrix
	and multiplying them.
*/
void Ball::UpdateModelMatrix()
{
	glm::mat3 scaleMatrix = Transform2D::Scale((float)this->radius,
											   (float)this->radius);
	glm::mat3 positionMatrix = Transform2D::Translate((float)this->position.x,
													  (float)this->position.y);

	this->SetModelMatrix(positionMatrix * scaleMatrix);
}

/*
	Detect collision with collidable objects from schene. Each collidable 
	object is a square that has 4 sides described as for parametrized equation.
	For each side, the ball checks if there is a change of collision. 
	Also, when colliding with bricks, a "signal" is sent to that brick that
	it was hit by the ball.
*/
bool Ball::DetectCollision(float gameTime)
{
	bool collisionDetected = false;
	glm::vec2 start, end;

	// For each near brick, check collision
	for (CollidableSquare* o : collidableObjs) {
		bool hit = false;

		// Bottom segment
		start.x = o->GetPosition().x - o->GetWidth() / 2.0f;
		start.y = o->GetPosition().y - o->GetHeight() / 2.0f;
		end.x = o->GetPosition().x + o->GetWidth() / 2.0f;
		end.y = o->GetPosition().y - o->GetHeight() / 2.0f;
		if (ReflectBall(start, end, gameTime, dynamic_cast<Brick*>(o))) {
			collisionDetected = true;
			hit = true;
		}
		
		// Top segment
		start.x = o->GetPosition().x - o->GetWidth() / 2.0f;
		start.y = o->GetPosition().y + o->GetHeight() / 2.0f;
		end.x = o->GetPosition().x + o->GetWidth() / 2.0f;
		end.y = o->GetPosition().y + o->GetHeight() / 2.0f;
		if (ReflectBall(start, end, gameTime, dynamic_cast<Brick*>(o))) {
			collisionDetected = true;
			hit = true;
		}

		// Right segment
		start.x = o->GetPosition().x - o->GetWidth() / 2.0f;
		start.y = o->GetPosition().y + o->GetHeight() / 2.0f;
		end.x = o->GetPosition().x - o->GetWidth() / 2.0f;
		end.y = o->GetPosition().y - o->GetHeight() / 2.0f;
		if (ReflectBall(start, end, gameTime, dynamic_cast<Brick*>(o))) {
			collisionDetected = true;
			hit = true;
		}

		// Left segment
		start.x = o->GetPosition().x + o->GetWidth() / 2.0f;
		start.y = o->GetPosition().y + o->GetHeight() / 2.0f;
		end.x = o->GetPosition().x + o->GetWidth() / 2.0f;
		end.y = o->GetPosition().y - o->GetHeight() / 2.0f;
		if (ReflectBall(start, end, gameTime, dynamic_cast<Brick*>(o))) {
			collisionDetected = true;
			hit = true;
		}

		// Sent signal to brick: "I'm hit by the ball"
		if (hit) {
			if (Brick* b = dynamic_cast<Brick*>(o)) {
				b->Hit();
				if (strongBall)
					collisionDetected = false;
			}
		}
	}

	return collisionDetected;
}

/*
	Getter for radius
*/
unsigned int Ball::GetRadius()
{
	return this->radius;
}

/*	
	Setter for radius
*/
void Ball::SetRadius(unsigned int radius)
{
	this->radius = radius;
}

/*
	Getter for position
*/
glm::vec2 Ball::GetPosition()
{
	return this->position;
}

/*
	Getter for acceleration
*/
float Ball::GetAcceleration()
{
	return this->acceleration;
}

/*
	Setter for acceleration
*/
void Ball::SetAcceleration(float acceleration)
{
	this->acceleration = acceleration;
}

/*
	Getter for velocity
*/
glm::vec2 Ball::GetVelocity()
{
	return this->velocity;
}


/*
	Setter for velocity
*/
void Ball::SetVelocity(glm::vec2 velocity)
{
	this->velocity = velocity;
}

/*
	Getter for sticked
*/
bool Ball::IsSticked()
{
	return this->sticked;
}

/*
	Setter for sticked
*/
void Ball::SetSticked(bool sticked)
{
	this->sticked = sticked;
}

/*
	Add objects that are near the ball. This will reduce the complexity of 
	checking for collisions, for lots of bricks
*/
void Ball::AddNearCollidableObjs(std::vector<CollidableSquare*> objs)
{
	unsigned int maxDimension;
	for (CollidableSquare *o : objs) {
		maxDimension = glm::max(o->GetHeight(), o->GetWidth());

		if (DistanceTwoPoints(position, o->GetPosition()) <= 5 * maxDimension) {
			collidableObjs.push_back(o);
		}
	}
}

/*
	Reset the vector of collidable objects
*/
void Ball::ClearCollidableObjs()
{
	this->collidableObjs.clear();
}

/*
	Deploy the ball from the paddle, if the ball was sticked. The angle 
	is arccos of the position w.r.t paddle.
*/
void Ball::DeployOnClick(glm::vec2 paddlePos, glm::vec2 paddleSize)
{
	if (IsSticked()) {
		float angle = glm::acos((position.x - paddlePos.x) / paddleSize.x);
		float x = MAX_VELOCITY * cos(angle);
		float y = MAX_VELOCITY * sin(angle);
		velocity = glm::vec2(x, y);
	}
}

/*
	Check for collision with paddle
*/
bool Ball::ReflectPaddle(glm::vec2 paddlePos, glm::vec2 paddleSize, 
	float gameTime)
{
	glm::vec2 p1, p2, p3, p4, nextPosition;

	// Compute the corners of the paddle
	p1.x = paddlePos.x - paddleSize.x / 2.0f;
	p1.y = paddlePos.y - paddleSize.y / 2.0f;

	p2.x = paddlePos.x - paddleSize.x / 2.0f;
	p2.y = paddlePos.y + paddleSize.y / 2.0f;

	p3.x = paddlePos.x + paddleSize.x / 2.0f;
	p3.y = paddlePos.y + paddleSize.y / 2.0f;

	p4.x = paddlePos.x + paddleSize.x / 2.0f;
	p4.y = paddlePos.y - paddleSize.y / 2.0f;

	// Predict the next position
	nextPosition = position + gameTime * velocity;

	// Check collision with the paddle
	if (CollisionDetection::CollisionWithSegment(p1, p2, (float)this->radius,
			this->position, nextPosition, NULL, NULL) ||
		CollisionDetection::CollisionWithSegment(p2, p3, (float)this->radius,
			this->position, nextPosition, NULL, NULL) ||
		CollisionDetection::CollisionWithSegment(p3, p4, (float)this->radius,
			this->position, nextPosition, NULL, NULL))
	{
		float cosVal = (2.0f * (position.x - paddlePos.x)) / paddleSize.x;
		// Limit cosVal between -0.99 and 0.99
		cosVal = glm::clamp(cosVal, -0.99f, 0.99f);
		float angle = glm::acos(cosVal);

		// Compute the velocity vector. It's arccos of ball's position w.r.t
		// the possition of the paddle
		float x = MAX_VELOCITY * cos(angle);
		float y = MAX_VELOCITY * sin(angle);
		velocity = glm::vec2(x, y);
		position += gameTime * velocity;

		return true;
	}

	return false;
}

/*
	Reflect the ball if there is a collision with a given segment.
	The brick parameter is used when the "Strong ball" powerup is active.
	In that case, the velocity will not be reflected.
*/
bool Ball::ReflectBall(glm::vec2 start, glm::vec2 end, float gameTime, 
	bool brick)
{
	glm::vec2 normal, point;
	glm::vec2 nextPosition = position + gameTime * velocity;

	// Check the collision
	if (CollisionDetection::CollisionWithSegment(start,
		end, (float)this->radius, this->position, nextPosition, &point, 
		&normal)) 
	{
		// If the "Strong ball" powerup is not active, compute the 
		// new velocity vector
		if ((!strongBall && brick) || !brick) 
			velocity = glm::reflect(velocity, normal);

		// Compute the next position
		position += velocity * gameTime;

		return true;
	}

	return false;
}

/*
	Set powerup of the ball. Available powerups are:
		Wall -> set a wall on the bottom of the screen to avoid loosing the 
		        ball
		Big Ball -> the size of the ball is increased. 
		Strong Ball -> the ball will not reflect the direction, when colliding 
					   with a brick (but not for a wall or paddle)
*/
void Ball::PlayWithPowerUp(float gameTime)
{
	// If timeout, reset any powerup.
	if (this->powerUpTimer <= 0) {
		this->crtPowerUp = PowerUpsEnum::NO_POWERUP;
		this->powerUpTimer = 0;
		this->bottomWall = false;
		this->radius = old_radius;
		this->strongBall = false;
	}

	// Set a custom powerup
	switch (this->crtPowerUp)
	{
		case PowerUpsEnum::NO_POWERUP:
			std::cout << "No powerup... " << powerUpTimer  << std::endl;
			return;
		case PowerUpsEnum::WALL:
			std::cout << "Wall... " << powerUpTimer  << std::endl;
			this->bottomWall = true;
			this->powerUpTimer -= gameTime;
			break;
		case PowerUpsEnum::BIG_BALL:
			std::cout << "BIG Ball... " << powerUpTimer << std::endl;
			this->SetRadius(40);
			this->powerUpTimer -= gameTime;
			break;
		case PowerUpsEnum::STRONG_BALL:
			std::cout << "Strong Ball... " << powerUpTimer << std::endl;
			this->strongBall = true;
			this->powerUpTimer -= gameTime;
			break;
		default:
			break;
	}
}

/*
	Initialize circles that are shown on the bottom left of the screen, 
	that shows the number of lifes remaining.
*/
void Ball::InitBalls()
{
	char name[10];
	int radius = 15;

	this->crtNumBalls = NUMBER_OF_BALLS;
	this->balls = std::vector<Circle*>();

	for (int i = 0; i < this->crtNumBalls; i++) {
		// Translate each circle
		float x = (2.0f * (float)radius + 10.0f) * (i + 1);
		float y = (float)radius + 10.0f;
		glm::mat3 modelMatrix = Transform2D::Translate(x, y) * 
							Transform2D::Scale((float)radius, (float)radius);

		// Set z-depth in front of objects
		modelMatrix += glm::transpose(glm::mat3(
			0, 0, 0,
			0, 0, 0,
			0, 0, 2
		));

		// Set the name
		memset(name, 0, 10 * sizeof(char));
		sprintf(name, "ball%d", i);

		// Create the circle and put it in the vector of balls
		Circle *c = new Circle(name, glm::vec3(1, 1, 1), modelMatrix, true);
		balls.push_back(c);
	}
}

/*
	Reset the position of the ball when it leaves the screen, and also the 
	powerups and decrease the number of lifes left.
*/
bool Ball::ResetOnOffScreen(glm::vec2 windowSize, glm::vec2 paddlePos, 
	glm::vec2 paddleSize)
{
	if ((this->position.y + this->radius < 0)
		|| (this->position.x + this->radius < 0)
		|| (this->position.x - this->radius > windowSize.x))
	{
		this->crtNumBalls--;
		this->InitPosition(paddlePos, paddleSize);
		this->SetSticked(true);
		this->powerUpTimer = 0;
		return true;
	}

	// The ball is still on the screen
	return false;
}

/*
	Set a powerup. If the current powerup is NO_POWERUP or the new powerup is 
	NO_POWERUP, then set the new powerup. You cannot have 2 powerup on the 
	same time. After the current powerup times out, you can have a new powerup.
*/
void Ball::SetPowerUp(PowerUpsEnum pw, float duration)
{
	if (pw != PowerUpsEnum::NO_POWERUP
		&& this->crtPowerUp != PowerUpsEnum::NO_POWERUP)
	{
		return;
	}

	// Set the powerup
	this->crtPowerUp = pw;
	this->powerUpTimer = duration;
}

/*
	Getter for bottomWall
*/
bool Ball::IsBottomWallActive()
{
	return this->bottomWall;
}

/*
	Reset the number of remaining balls to NUMBER_OF_BALLS
*/
void Ball::ResetNumBalls()
{
	this->crtNumBalls = NUMBER_OF_BALLS;
}

/*
	Getter for the number of lifes (balls).
*/
int Ball::GetNumBalls()
{
	return this->crtNumBalls;
}

/*
	Getter for balls vector.
*/
std::vector<Circle*> Ball::GetBalls()
{
	return this->balls;
}

/*
	Update the ball position and the powerups.
*/
void Ball::Update(float gameTime, glm::vec2 paddlePos, glm::vec2 paddleSize)
{
	if (IsSticked()) {
		// The ball is sticked, so the position on oX is the same as of the 
		// paddle
		position.x = paddlePos.x;
	}
	else {
		glm::vec2 nextPosition = position + gameTime * velocity;

		// Check for collision
		if (!ReflectPaddle(paddlePos, paddleSize, gameTime) 
				&& !DetectCollision(gameTime)) {
			position = nextPosition;
		}
	}
	
	// Use powerups and update the model matrix
	PlayWithPowerUp(gameTime);
	UpdateModelMatrix();
}


/*
	Init the position of the ball in the middle of the paddle, but a some 
	distance on height.
*/
void Ball::InitPosition(glm::vec2 paddlePos, glm::vec2 paddleSize)
{
	this->position.x = paddlePos.x;
	this->position.y = paddlePos.y + 1.1f * paddleSize.y + this->radius;

	UpdateModelMatrix();
}
