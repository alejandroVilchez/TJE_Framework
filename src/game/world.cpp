#include "world.h"

float angles = 0;
float mouse_speeds = 100.0f;
//
//Mesh* mesh = NULL;
//Texture* texture = NULL;
//Shader* shader = NULL;

//Mesh* playerMesh = nullptr; // Load a cube mesh
//Texture* playerTexture = nullptr;
//Shader* basicShader = nullptr;
//Material playerMaterial;

//Scene* scene;
//
//EntityPlayer* playerEntity;
//
//Material cubemap;
//Material skyboxMaterial;
//EntityMesh* skybox;

World* World::instance;

World::World(int window_width, int window_height) {

	instance = this;

	/*int window_width = Game::instance->window_width;
	int window_height = Game::instance->window_height;*/

    root = new Entity();

	camera = new Camera();
	camera->lookAt(Vector3(0.f, 100.f, 100.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f, window_width / (float)window_height, 0.1f, 10000.f); //set the projection, we want to be perspective


    basicShader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	playerMesh = Mesh::Get("data/meshes/B2rotated.obj");
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

	playerTexture = Texture::Get("data/textures/texture.tga"); // Load a texture


	playerMaterial.shader = basicShader;
	playerMaterial.diffuse = playerTexture;

	Vector3 position = (0.0f, 0.0f, 15.0f);
	playerEntity = new EntityPlayer(position);//EntityMesh(playerMesh, playerMaterial, "Player");

	playerEntity->mesh = playerMesh;
	playerEntity->material = playerMaterial;
	playerEntity->name = "Player";
	float angle_in_rad = 1.5707963268f; //90 degrees

	//------- Bomba --------
	bombMesh = Mesh::Get("data/meshes/missile1.obj");
	bombTexture = Texture::Get("data/missile/Missile-2K.png"); // load a texture

	bombMaterial.shader = basicShader;
	bombMaterial.diffuse = bombTexture;

	bombEntity = new EntityMesh(bombMesh, bombMaterial, "bomb");

	//Explosion Nuclear

	nuclearMesh = Mesh::Get("data/meshes/explosion4.obj");
	nuclearTexture = Texture::Get("data/meshes/explosion-diffuse.png"); // load a texture
	nuclearMaterial.shader = basicShader;
	nuclearMaterial.diffuse = nuclearTexture;

	nuclearEntity = new EntityMesh(nuclearMesh, nuclearMaterial, "nuclear");

	scene = new Scene();
	scene->parseScene("data/myscene.scene");

	collider = scene->collider;
}

void World::render() {

	camera->enable();
	scene->root.render(camera);
    root->render(camera);
    if (playerEntity) {
        playerEntity->render(camera);
    }
	skybox->render(camera);

	if (bombEntity->isLaunched) {
		bombEntity->render(camera);
	}
	if (bombEntity->isExploded) {
		nuclearEntity->render(camera);
	}
}

void World::update(float elapsed_time) {

	float speed = elapsed_time * mouse_speeds; //the speed is defined by the seconds_elapsed so it goes constant

	// Example
	angles += (float)elapsed_time * 10.0f;

	playerEntity->update(elapsed_time, playerEntity, skybox, bombEntity, &collider, nuclearEntity);

	//if(bombEntity->launched == true){
	//	bombEntity->update(elapsed_time);
	//}
	
	playerEntity->playerPOV(camera, elapsed_time);
    root->update(elapsed_time);
}

void World::cleanRoot() {
    for (size_t i = root->children.size() - 1; i >= 0; i--) { //clean root
        root->removeChild(root->children[i]);
    }
}

void World::onKeyDown(SDL_KeyboardEvent event) {
	switch (event.keysym.sym) {
	//case SDLK_ESCAPE: Game::instance->must_exit = true; break; //ESC key, kill the app
	case SDLK_F1: Shader::ReloadAll(); break;
	}
}