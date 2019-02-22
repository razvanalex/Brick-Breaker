#pragma once
#include "CollidableSquare.h"
#include <vector>

/*
	Wall is a container of collidable squares. It is used to delimitate the 
	game space.
*/
class Wall {
	public:
		Wall(unsigned int screenWidth, unsigned int screenHeight, 
			unsigned int wallWidth, unsigned int bottomPadding,  
			glm::vec3 color);
		~Wall();

	private: 
		CollidableSquare *left, *top, *right, *bottom;
		bool bottomWall;

	public:
		std::vector<CollidableSquare*> GetAllCollidableSquares();
		void SetBottomWall(bool val);
};