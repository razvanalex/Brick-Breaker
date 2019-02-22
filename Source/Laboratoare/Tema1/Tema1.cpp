#include "Tema1.h"

#include <iostream>
using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
	delete paddle;
	delete ball;
	delete wall;
	delete brickManager;
}

void Tema1::Init()
{
	// Initialize camera
	camera = new Camera(glm::vec3(0, 0, 40), glm::vec3(0, 0, 0), 
		glm::vec3(0, 1, 0));

	// Set logic space
	lSpace.x = 0;
	lSpace.y = 0;
	lSpace.width = window->GetResolution().x;
	lSpace.height = window->GetResolution().y;

	// Init the paddle
	paddle = new Paddle("paddle", 300, 25, lSpace.width / 2.0f, 30.0f, 
		glm::vec3(1, 0, 0));
	AddMeshToList(paddle->CreateMesh());

	// Init the ball
	ball = new Ball("ball", 20, lSpace.width / 2.0f, 80, glm::vec3(0, 1, 0));
	ball->InitPosition(paddle->GetPosition(), paddle->GetSize());
	AddMeshToList(ball->CreateMesh());

	// Add lifes to be rendered
	for (Circle *c : ball->GetBalls()) {
		AddMeshToList(c->CreateMesh());
	}

	// Init the wall
	wall = new Wall(lSpace.width, lSpace.height, 30, 150, glm::vec3(1, 0, 1));
	for (CollidableSquare *c : wall->GetAllCollidableSquares())
		AddMeshToList(c->CreateMesh());

	// Init the Brick Manager
	brickManager = new BrickManager(3);
	brickManager->SetBoard(10, 7, 80, 30, 20, 
		glm::vec2(lSpace.width, lSpace.height), level);
	brickManager->SetBallRef(ball);
	brickManager->SetMeshes(meshes);

	for (CollidableSquare *c : brickManager->GetAllBricks())
		AddMeshToList(c->CreateMesh());
}

void Tema1::FrameStart()
{

}

void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	// Sets the screen area where to draw - the left half of the window
	vSpace = Display::ViewportSpace(0, 0, resolution.x, resolution.y);
	Display::SetViewportArea(*camera, vSpace, glm::vec3(0), true);

	// Compute uniform 2D visualization matrix
	glm::mat3 visMatrix = Display::LogicToViewportTransformation(&lSpace, &vSpace);

	// Reset game when no more lives left
	if (ball->GetNumBalls() == 0) {
		level = 1;
		ResetScene();
	}

	// Go to next level
	if (brickManager->GetAllBricks().size() == 0) {
		level++;
		ResetScene();
	}

	// Update brick manager
	brickManager->SetPaddlePos(paddle->GetPosition());
	brickManager->SetPaddleSize(paddle->GetSize());
	brickManager->Update(deltaTimeSeconds);

	// Set Wall powerup if needed
	wall->SetBottomWall(ball->IsBottomWallActive());

	// Add collidable objects
	ball->AddNearCollidableObjs(brickManager->GetAllCollidableSquares());
	ball->AddNearCollidableObjs(wall->GetAllCollidableSquares());
	ball->Update(deltaTimeSeconds, paddle->GetPosition(), paddle->GetSize());
	ball->ResetOnOffScreen(window->GetResolution(), paddle->GetPosition(), paddle->GetSize());
	ball->ClearCollidableObjs();

	// Draw the entire scene
	DrawScene(visMatrix);
}

void Tema1::DrawScene(glm::mat3 visMatrix)
{
	// Draw the paddle
	Display::RenderMesh(meshes["paddle"], shaders["VertexColor"],
		visMatrix * paddle->GetModelMatrix(), camera);

	// Draw the ball
	Display::RenderMesh(meshes["ball"], shaders["VertexColor"],
		visMatrix * ball->GetModelMatrix(), camera);

	// Draw lifes
	for (int i = 0; i < ball->GetNumBalls(); i++) {
		Circle *c = ball->GetBalls()[i];
		Display::RenderMesh(meshes[c->GetName()], shaders["VertexColor"],
			visMatrix * c->GetModelMatrix(), camera);
	}

	// Draw the wall
	for (CollidableSquare *c : wall->GetAllCollidableSquares())
	{
		Display::RenderMesh(meshes[c->GetName()], shaders["VertexColor"],
			visMatrix * c->GetModelMatrix(), camera);
	}

	// Draw bricks
	for (CollidableSquare *c : brickManager->GetAllBricks())
	{
		Display::RenderMesh(meshes[c->GetName()], shaders["VertexColor"],
			visMatrix * c->GetModelMatrix(), camera);
	}

	// Draw the powerUps
	for (PowerUp *p : brickManager->GetAllPowerUpsOnDisplay()) {
		Display::RenderMesh(meshes[p->GetName()], shaders["VertexColor"],
			visMatrix * p->GetModelMatrix(), camera);
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
};

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
};

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{ 
	paddle->Update(glm::vec2(mouseX, mouseY));
};

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Deploy the ball on mouse click 
	ball->DeployOnClick(paddle->GetPosition(), paddle->GetSize());
	ball->SetSticked(false);
};

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Tema1::OnWindowResize(int width, int height)
{
	// treat window resize event
}

void Tema1::ResetScene()
{
	// Reset paddle
	paddle->Update(glm::vec2(lSpace.width / 2.0f, 30.0f));

	// Reset ball
	ball->SetSticked(true);
	ball->ResetNumBalls();
	ball->ClearCollidableObjs();
	ball->SetVelocity(glm::vec2(0));
	ball->SetAcceleration(0);
	ball->SetPowerUp(PowerUpsEnum::NO_POWERUP, 0);
	ball->InitPosition(paddle->GetPosition(), paddle->GetSize());

	// Reset Brick Manager
	brickManager->Reset();
	brickManager->SetBoard(10, 7, 80, 30, 20,
		glm::vec2(lSpace.width, lSpace.height), level);

	for (CollidableSquare *c : brickManager->GetAllBricks())
		AddMeshToList(c->CreateMesh());
}
