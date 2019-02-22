#include "Wall.h"

/*
	Constructor for the walls. It instantiates 3 main walls (top, right and 
	bottom) and a wall for powerup.
*/
Wall::Wall(unsigned int screenWidth, unsigned int screenHeight,
	unsigned int wallWidth, unsigned int bottomPadding, glm::vec3 color)
{
	this->left = new CollidableSquare("leftWall",
		wallWidth, screenHeight - bottomPadding, wallWidth / 2.0f, 
		(screenHeight + bottomPadding - wallWidth) / 2.0f, color);

	this->top = new CollidableSquare("topWall", screenWidth, wallWidth,
		screenWidth / 2.0f, screenHeight - wallWidth / 2.0f, color);

	this->right = new CollidableSquare("rightWall", wallWidth,
		screenHeight - bottomPadding, screenWidth - wallWidth / 2.0f, 
		(screenHeight + bottomPadding - wallWidth) / 2.0f, color);

	this->bottom = new CollidableSquare("topWall", screenWidth, wallWidth,
		screenWidth / 2.0f,  wallWidth / 2.0f, color);

	this->bottomWall = false;
}

/*
	The destructor for walls
*/
Wall::~Wall()
{
	delete left;
	delete top;
	delete right;
	delete bottom;
}

/*
	Get all squares from walls. This method is used when drawing the walls, or 
	to set the collidable object for the ball.
*/
std::vector<CollidableSquare*> Wall::GetAllCollidableSquares()
{
	std::vector<CollidableSquare*> vect = std::vector<CollidableSquare*>();
	vect.push_back(left);
	vect.push_back(top);
	vect.push_back(right);

	if (bottomWall)
		vect.push_back(bottom);

	return vect;
}

/*
	Setter for bottomWall. Is used together with Wall powerup.
*/
void Wall::SetBottomWall(bool val)
{
	this->bottomWall = val;
}
