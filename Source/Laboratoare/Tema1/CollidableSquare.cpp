#include "CollidableSquare.h"

/*
	Constructor for a collidable square. 
*/
CollidableSquare::CollidableSquare(std::string name, unsigned int width, 
	unsigned int height, float x, float y, glm::vec3 color) 
	: Square(name, color, glm::mat3(1), true)
{
	this->width = width;
	this->height = height;
	this->position = glm::vec2(x, y);

	updateModelMatrix();
}

/* 
	Destructor for a collidable square
*/
CollidableSquare::~CollidableSquare()
{
}

/*
	Update the model matrix, by multiplying the position and the scale matrices.
*/
void CollidableSquare::updateModelMatrix()
{
	glm::mat3 scaleMatrix = Transform2D::Scale((float)this->width,
		(float)this->height);
	glm::mat3 positionMatrix = Transform2D::Translate((float)this->position.x,
		(float)this->position.y);

	this->SetModelMatrix(positionMatrix * scaleMatrix);
}

/*
	Getter for width
*/
unsigned int CollidableSquare::GetWidth()
{
	return this->width;
}

/*
	Getter for height
*/
unsigned int CollidableSquare::GetHeight()
{
	return this->height;
}

/*
	Setter for size
*/
void CollidableSquare::SetSize(glm::vec2 size)
{
	this->width = (int)size.x;
	this->height = (int)size.y;
}

/*
	Getter for size
*/
glm::vec2 CollidableSquare::GetSize()
{
	return glm::vec2(GetWidth(), GetHeight());
}

/*
	Getter for position
*/
glm::vec2 CollidableSquare::GetPosition()
{
	return this->position;
}

/*
	It's a virtual method. It should be overriden by deriving classes.
*/
void CollidableSquare::Update(float gameTime) 
{
}
