#pragma once

#include "Camera.h"
#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include <include/glm.h>

/*
	This namespace contains the ViewPortSpace structure and LogicSpace structure
	and also 2 functions used to set the viewport and to transform the logic 
	space to viewport space. Structures are from laborator 3.
*/
namespace Display
{
	struct ViewportSpace {
		ViewportSpace() : x(0), y(0), width(1), height(1) {}
		ViewportSpace(int x, int y, int width, int height)
			: x(x), y(y), width(width), height(height) {}
		unsigned int x = 0;
		unsigned int y = 0;
		unsigned int height = 1;
		unsigned int width = 1;
	};

	struct LogicSpace {
		LogicSpace() : x(0), y(0), width(1), height(1) {}
		LogicSpace(int x, int y, int width, int height)
			: x(x), y(y), width(width), height(height) {}
		unsigned int x = 0;
		unsigned int y = 0;
		unsigned int height = 1;
		unsigned int width = 1;
	};

	glm::mat3 LogicToViewportTransformation(LogicSpace *lSpace, 
		ViewportSpace *vSpace);
	void SetViewportArea(Camera &camera,
		ViewportSpace &vSpace, glm::vec3 colorColor, bool clear);
	void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix,
		Camera * camera);

}
