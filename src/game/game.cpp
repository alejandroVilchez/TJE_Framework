#include "game.h"

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

EntityPlayer* playerEntity;

Material cubemap;
Material skyboxMaterial;
EntityMesh* skybox;

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

	// Create our camera
	camera = new Camera();
	camera->lookAt(Vector3(0.f,100.f, 100.f),Vector3(0.f,0.f,0.f), Vector3(0.f,1.f,0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f,window_width/(float)window_height,0.1f,10000.f); //set the projection, we want to be perspective


	basicShader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs"); // Load a basic shader
	//Load one texture using the Texture Manager
	//texture = Texture::Get("data/textures/texture.tga");
	cubemap.diffuse = new Texture();
	//// Example of loading Mesh from Mesh Manager
	
	cubemap.diffuse->loadCubemap("landscape", {
	"data/textures/skybox/right.tga",
	"data/textures/skybox/left.tga",
	"data/textures/skybox/top.tga",
	"data/textures/skybox/bottom.tga",
	"data/textures/skybox/front.tga",
	"data/textures/skybox/back.tga"
		});

	
	cubemap.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/cubemap.fs");;

	skybox = new EntityMesh(Mesh::Get("data/meshes/skybox.obj"), cubemap, "skybox");

	//// Example of shader loading using the shaders manager
	//shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

	playerMesh = Mesh::Get("data/meshes/B2_final_model.obj");
	playerTexture = Texture::Get("data/textures/texture.tga"); // Load a texture
	

	playerMaterial.shader = basicShader;
	playerMaterial.diffuse = playerTexture;
	
	Vector3 position = (0.0f, 0.0f, 15.0f);
	playerEntity = new EntityPlayer(position);//EntityMesh(playerMesh, playerMaterial, "Player");

	playerEntity->mesh = playerMesh;
	playerEntity->material = playerMaterial;
	playerEntity->name = "Player";
	//float angle_in_rad = 1.5707963268f; //90 degrees
	//playerEntity->model.setRotation(angle_in_rad, Vector3(0.0f, 1.0f, 0.0f)); // No se aplica

	// Hide the cursor
	SDL_ShowCursor(!mouse_locked); //hide or show the mouse

	//Entity* root = new Entity();
	
	scene = new Scene();
	scene->parseScene("data/myscene.scene");

}

//what to do when the image has to be draw
void Game::render(void)
{
	// Set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the camera as default
	camera->enable();
	// Set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
   
	scene->root.render(camera);
	
	skybox->render(camera);
	
	//// Create model matrix for cube
	//Matrix44 m;
	//m.rotate(angle*DEG2RAD, Vector3(0.0f, 1.0f, 0.0f));

	//if(shader)
	//{
	//	// Enable shader
	//	shader->enable();

	//	// Upload uniforms
	//	shader->setUniform("u_color", Vector4(1,1,1,1));
	//	shader->setUniform("u_viewprojection", camera->viewprojection_matrix );
	//	shader->setUniform("u_texture", texture, 0);
	//	shader->setUniform("u_model", m);
	//	shader->setUniform("u_time", time);

	//	// Do the draw call
	//	mesh->render( GL_TRIANGLES );

	//	// Disable shader
	//	shader->disable();
	//}
	//// Create model matrix for cube
	//Matrix44 m;
	//m.rotate(angle*DEG2RAD, Vector3(0.0f, 1.0f, 0.0f));

	//if(shader)
	//{
	//	// Enable shader
	//	shader->enable();

	//	// Upload uniforms
	//	shader->setUniform("u_color", Vector4(1,1,1,1));
	//	shader->setUniform("u_viewprojection", camera->viewprojection_matrix );
	//	shader->setUniform("u_texture", texture, 0);
	//	shader->setUniform("u_model", m);
	//	shader->setUniform("u_time", time);

	//	// Do the draw call
	//	mesh->render( GL_TRIANGLES );

	//	// Disable shader
	//	shader->disable();
	//}

	// Draw the floor grid
	drawGrid();
	
	playerEntity->render(camera);
	
	
	

	// Render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	

	

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
	playerEntity->update(seconds_elapsed, skybox);
	playerEntity->playerPOV(camera, seconds_elapsed);

	//// Async input to move the camera around
	//if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT) ) speed *= 10; //move faster with left shift
	//if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) camera->move(Vector3(0.0f, 0.0f, 1.0f) * speed);
	//if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) camera->move(Vector3(0.0f, 0.0f,-1.0f) * speed);
	//if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) camera->move(Vector3(1.0f, 0.0f, 0.0f) * speed);
	//if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) camera->move(Vector3(-1.0f,0.0f, 0.0f) * speed);
}

//Keyboard event handler (sync input)
void Game::onKeyDown( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
		case SDLK_F1: Shader::ReloadAll(); break; 
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

