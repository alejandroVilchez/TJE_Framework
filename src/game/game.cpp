#include "game.h"
#include "stages.h"

#include "framework/utils.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "graphics/fbo.h"
#include "graphics/shader.h"
#include "framework/input.h"

#include "framework/entities/entity.h"
#include "scene.h"
#include "framework/entities/entity_player.h"
#include <cmath>

//some globals
Mesh* mesh = NULL;
Texture* texture = NULL;
Shader* shader = NULL;
float angle = 0;
float mouse_speed = 100.0f;

Mesh* playerMesh = nullptr; // Load a cube mesh
Texture* playerTexture = nullptr;
Shader* basicShader = nullptr;
Material playerMaterial;

Scene* scene;

Stages* stages;
//World* world;

EntityPlayer* playerEntity;

Material cubemap;
Material skyboxMaterial;
EntityMesh* skybox;

IntroStage* introStage;
PlayStage* playStage;
BadEndStage* badEndStage;
GoodEndStage* goodEndStage;
CreditsStage* creditsStage;
HowToStage* howToStage;
Stages* currentStage;

//Entity* root;
//Scene* scene;
//EntityPlayer* player;

Game* Game::instance = NULL;

Game::Game(int window_width, int window_height, SDL_Window* window)
{
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;

	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;
	mouse_locked = false;

	// OpenGL flags
	glEnable( GL_CULL_FACE ); //render both sides of every triangle
	glEnable( GL_DEPTH_TEST ); //check the occlusions using the Z buffer

	fullScreenQuad = Mesh::Get("data/meshes/quad.obj");
	introStage = new IntroStage();
	playStage = new PlayStage();
	howToStage = new HowToStage();
	badEndStage = new BadEndStage();
	goodEndStage = new GoodEndStage();
	creditsStage = new CreditsStage();

	currentStage = introStage;
	currentStageType = StageType::INTRO;

	world = new World(window_width, window_height);
	// Hide the cursor
	SDL_ShowCursor(!mouse_locked); //hide or show the mouse

	

}

//what to do when the image has to be draw
void Game::render(void)
{
	// Set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
   
	currentStage->render();

	

	

	// Swap between front buffer and back buffer
	SDL_GL_SwapWindow(this->window);
}

void Game::update(double seconds_elapsed)
{
	float speed = seconds_elapsed * mouse_speed; //the speed is defined by the seconds_elapsed so it goes constant

	// Example
	angle += (float)seconds_elapsed * 10.0f;

	// Mouse input to rotate the cam
	//if (input::ismousepressed(sdl_button_left) || mouse_locked) //is left button pressed?
	//{
	//	camera->rotate(input::mouse_delta.x * 0.005f, vector3(0.0f,-1.0f,0.0f));
	//	camera->rotate(input::mouse_delta.y * 0.005f, camera->getlocalvector( vector3(-1.0f,0.0f,0.0f)));
	//}
	currentStage->update(seconds_elapsed);


}

//Keyboard event handler (sync input)
void Game::onKeyDown( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
		case SDLK_F1: Shader::ReloadAll(); break; 
		case SDLK_SPACE:
			if (currentStageType == StageType::INTRO)
				changeStage(StageType::PLAY);
			else if (currentStageType == StageType::PLAY)
				changeStage(StageType::BADEND);
			else if (currentStageType == StageType::BADEND)
				changeStage(StageType::GOODEND);
			else if (currentStageType == StageType::GOODEND)
				changeStage(StageType::CREDITS);
			else if (currentStageType == StageType::CREDITS)
				changeStage(StageType::INTRO);
			break;
	}
}

void Game::onKeyUp(SDL_KeyboardEvent event)
{

}

void Game::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_MIDDLE) //middle mouse
	{
		mouse_locked = !mouse_locked;
		SDL_ShowCursor(!mouse_locked);
		SDL_SetRelativeMouseMode((SDL_bool)(mouse_locked));
	}
}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{

}

void Game::onMouseWheel(SDL_MouseWheelEvent event)
{
	mouse_speed *= event.y > 0 ? 1.1f : 0.9f;
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{

}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{

}

void Game::onResize(int width, int height)
{
    std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport( 0,0, width, height );
	camera->aspect =  width / (float)height;
	window_width = width;
	window_height = height;
}

void Game::changeStage(StageType newStage)
{
	currentStageType = newStage;
	switch (newStage)
	{
	case StageType::INTRO:
		currentStage = introStage;
		break;
	case StageType::PLAY:
		currentStage = playStage;
		break;
	case StageType::HOWTO:
		currentStage = howToStage;
		break;
	case StageType::BADEND:
		currentStage = badEndStage;
		break;
	case StageType::GOODEND:
		currentStage = goodEndStage;
		break;
	case StageType::CREDITS:
		currentStage = creditsStage;
		break;
	}
}
