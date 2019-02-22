#include "Paddle.h"

/*
	Constructor for the paddle. Initialize all parameters and update 
	the model matrix
*/
Paddle::Paddle(std::string name, unsigned int width, unsigned int height, 
	float x, float y, glm::vec3 color) : Square(name, color, glm::mat3(1), true)
{
	this->width = width;
	this->height = height;
	this->position = glm::vec2(x, y);

	updateModelMatrix();
}

/*
	Destructor for the paddle
*/
Paddle::~Paddle()
{
}

/*
	Update the model matrix. Multiply the position and the scale matrix.
*/
void Paddle::updateModelMatrix()
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
unsigned int Paddle::GetWidth()
{
	return this->width;
}

/*
	Getter for height
*/
unsigned int Paddle::GetHeight()
{
	return this->height;
}

/*
	Getter for size
*/
glm::vec2 Paddle::GetSize()
{
	return glm::vec2(GetWidth(), GetHeight());
}

/*
	Getter for position
*/
glm::vec2 Paddle::GetPosition()
{
	return this->position;
}

/*
	Update the position of the paddle. The x coordinate is given by the position
	of the mouse on the screen.
*/
void Paddle::Update(glm::vec2 mousePosition)
{
	position.x = mousePosition.x;

	updateModelMatrix();
}

