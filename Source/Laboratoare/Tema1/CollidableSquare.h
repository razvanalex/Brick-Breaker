#pragma once

#include "Square.h"
#include "Transform2D.h"

#include <string>

/*
	A collidable square is a square that can be "seen" by the ball. 
	Any object that is an instance of CollidableSquare may reflect the ball.
	Such objects are walls and bricks.
*/
class CollidableSquare : public Square {
	public:
		CollidableSquare(std::string name, unsigned int width,
			unsigned int height, float x, float y,
			glm::vec3 color);
		~CollidableSquare();

	private:
		unsigned int width;
		unsigned int height;
		glm::vec2 position;
		void updateModelMatrix();

	public:
		unsigned int GetWidth();
		unsigned int GetHeight();
		void SetSize(glm::vec2 size);

		glm::vec2 GetSize();
		glm::vec2 GetPosition();
		
		virtual void Update(float gameTime);
};