#pragma once

#include "Display.h"

#include "Camera.h"
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"
#include "BrickManager.h"
#include "Brick.h"

#include <Component/SimpleScene.h>
#include <Core/Engine.h>

/*
	This class represents the main scene drawn on the screen. It instatiates 
	all the objects, updates them and draws them on the screen. It's actually
	the framework from Laborator 3.
*/
class Tema1 : public SimpleScene
{
public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void DrawScene(glm::mat3 visMatrix);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;


	private:
		Display::LogicSpace lSpace;
		Display::ViewportSpace vSpace;

		Camera* camera;
		Paddle* paddle;
		Ball* ball;
		Wall* wall;
		BrickManager *brickManager;
		int level = 1;
		
		void ResetScene();
};