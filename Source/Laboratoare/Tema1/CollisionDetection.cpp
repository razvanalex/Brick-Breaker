#pragma once

#include "CollisionDetection.h"

namespace CollisionDetection 
{
	/*
		This function is used to detect if a circle of a given radius and a 
		current position, that wants to go to nextPosition, will intersect 
		the segment [start, end]. This function returns by side effect the 
		point of intersection and the normal. 

		To solve de collision problem, we consider the distance between 
		the circle and the segment as a function. If this distance is less 
		than the radius, then we've got collision. The algorithm is as follows:
			- parametrize both segments
			- compute the shortest path to the segment of the object
			- compute if the ball will collide with this segment on the next 
			  position

		Both computations are similar. A more complete approach would be to 
		determine that position by solving the system of ecuations of both
		segments. This is a more simple approach and gives good results 
		for low speeds.
	*/
	bool CollisionDetection::CollisionWithSegment(glm::vec2 start,
		glm::vec2 end, float radius, glm::vec2 crtPosition, glm::vec2 nextPosition,
		glm::vec2 *point, glm::vec2 *normal)
	{
		// Compute the minimum distance between the segment and the ball
		// First of all, compute the coefficients of distance function:
		// f : [0,1] -> R, f(s) = A * s^2 + B * s + C
		float A = glm::pow(end.x - start.x, 2) + glm::pow(end.y - start.y, 2);
		float B = 2 * ((end.x - start.x) * (start.x - crtPosition.x) +
			(end.y - start.y) * (start.y - crtPosition.y));
		float C = glm::pow(start.x - crtPosition.x, 2) +
			glm::pow(start.y - crtPosition.y, 2);

		// Compute delta for function of s
		float delta_s = B * B - 4 * A * C;

		// Compute the minimum point (s, f_s)
		float s = -B / (2 * A);
		float f_s = -delta_s / (4 * A);

		// Compute the normal vector
		// dx = x2-x1 and dy = y2-y1 => N = (-dy, dx)
		if (normal != NULL) {
			normal->x = -(end.y - start.y);
			normal->y = end.x - start.x;
			*normal = glm::normalize(*normal);
		}

		// Check for collision
		if (0 <= s && s <= 1) {
			if (f_s <= radius * radius)
				return true;
		}
		else {
			if (glm::min(C, A + B + C) <= radius * radius)
				return true;
			return false;
		}
		
		// Compute the (x0, y0) point w.r.t s
		float x0 = start.x + s * (end.x - start.x);
		float y0 = start.y + s * (end.y - start.y);

		if (point != NULL) {
			point->x = x0;
			point->y = y0;
		}

		// Compute the minimum distance between the segment and the ball
		// First of all, compute the coefficients of distance function:
		// f : [0,1] -> R, f(s) = A * s^2 + B * s + C
		A = glm::pow(nextPosition.x - crtPosition.x, 2) +
			glm::pow(nextPosition.y - crtPosition.y, 2);
		B = 2 * ((nextPosition.x - crtPosition.x) * (crtPosition.x - x0) +
			(nextPosition.y - crtPosition.y) * (crtPosition.y - y0));
		C = glm::pow(crtPosition.x - x0, 2) +
			glm::pow(crtPosition.y - y0, 2);

		// Compute delta for function of t
		float delta_t = B * B - 4 * A * C;

		// Compute the minimum point (f, f_f)
		float t = -B / (2 * A);
		float f_t = -delta_t / (4 * A);

		// Check for collision
		if (0 <= t && t <= 1) {
			if (f_t <= radius * radius)
				return true;
		}
		else {
			if (glm::min(C, A + B + C) <= radius * radius)
				return true;
		}

		// Here we don't have any collision.
		return false;
	}


}