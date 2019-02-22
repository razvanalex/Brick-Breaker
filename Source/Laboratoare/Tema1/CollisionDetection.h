#pragma once

#include <include/glm.h>

/*
	Namespace for Collision Detection. It is used to encapsulate the 
	CollisionWithSegment() method as a global function. The implementation of 
	this method is in CollsitionDetection.h
*/
namespace CollisionDetection
{
	bool CollisionWithSegment(
		glm::vec2 start, glm::vec2 end,
		float radius, glm::vec2 crtPosition, glm::vec2 nextPosition,
		glm::vec2 *point, glm::vec2 *normal);

}