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

	this->world_window_width = window_width;
	this->world_window_height = window_height,
	/*int window_width = Game::instance->window_width;
	int window_height = Game::instance->window_height;*/

    root = new Entity();

	camera = new Camera();
	camera->lookAt(Vector3(0.f, 100.f, 100.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f, window_width / (float)window_height, 0.1f, 10000.f); //set the projection, we want to be perspective

	camera2D = new Camera();
	camera2D->view_matrix.setIdentity();
	camera2D->setOrthographic(0, window_width, window_height, 0, -1, 1);



    basicShader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	//playerMesh = Mesh::Get("data/meshes/B2rotated.obj");
	playerMesh = Mesh::Get("data/meshes/B2_final_model.obj");
	
	//quad = createFullscreenQuad(window_width,window_height);
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

	//------- Player --------
	playerTexture = Texture::Get("data/textures/texture.tga"); // Load a texture

	playerMaterial.shader = basicShader;
	playerMaterial.diffuse = playerTexture;

	Vector3 position = (0.0f, 0.0f, 15.0f);
	playerEntity = new EntityPlayer(position);//EntityMesh(playerMesh, playerMaterial, "Player");

	playerEntity->mesh = playerMesh;
	playerEntity->material = playerMaterial;
	playerEntity->name = "Player";
	
	gameTimer = 35.0f;

	//------- Bomba --------
	bombMesh = Mesh::Get("data/meshes/missile1.obj");
	bombTexture = Texture::Get("data/missile/Missile-2K.png"); // load a texture

	bombMaterial.shader = basicShader;
	bombMaterial.diffuse = bombTexture;

	bombEntity = new EntityMesh(bombMesh, bombMaterial, "bomb");

	//----- Explosion Nuclear -----
	nuclearMesh = Mesh::Get("data/meshes/explosion4.obj");
	nuclearTexture = Texture::Get("data/meshes/explosion-diffuse.png"); // load a texture
	nuclearMaterial.shader = basicShader;
	nuclearMaterial.diffuse = nuclearTexture;

	nuclearEntity = new EntityMesh(nuclearMesh, nuclearMaterial, "nuclear");

	//----- Explosion Avion -----
	failMesh = Mesh::Get("data/meshes/fail.obj");
	//failTexture = Texture::Get("data/meshes/explosion-diffuse.png"); // load a texture
	//failMaterial.shader = basicShader;
	//failMaterial.diffuse = failTexture;

	failEntity = new EntityMesh(failMesh, nuclearMaterial, "fail");

	//----- Mapa -----
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
	if (gameTimer < 0) {
		failEntity->render(camera);
		//drawText(this->world_window_width / 2 - 130, this->world_window_height / 2, "Game Over", Vector3(1, 1, 1), 5);
		drawText(this->world_window_width / 2 - 250, this->world_window_height / 2, "You failed to destroy the island...", Vector3(1, 1, 1), 3);
	}
	else if (playerPosition.y < 0) {
		failEntity->render(camera);
		//drawText(this->world_window_width / 2 - 130, this->world_window_height / 2, "Game Over", Vector3(1, 1, 1), 5);
		drawText(this->world_window_width / 2 - 180, this->world_window_height / 2, "You destroyed yourself...", Vector3(1, 1, 1), 3);
	}
	else {
		drawText(50, this->world_window_height - 50, messageText, Vector3(1, 1, 1), 2);
	}
	std::ostringstream stream1;
	stream1 << std::fixed << std::setprecision(2) << playerPosition.y;
	playerHeight = "Height: " + stream1.str();
	drawText(50, 50, playerHeight, Vector3(1, 1, 1), 2);
	
}

void World::update(float elapsed_time) {

	//float speed = elapsed_time * mouse_speeds; //the speed is defined by the seconds_elapsed so it goes constant

	// Example
	//angles += (float)elapsed_time * 10.0f;
	gameTimer -= elapsed_time;

	playerEntity->update(elapsed_time, playerEntity, skybox, bombEntity, &collider, nuclearEntity, gameTimer);
	playerEntity->playerPOV(camera, elapsed_time);

	playerPosition = playerEntity->model.getTranslation();

	if (gameTimer > 30) {
		messageText = "You have been discovered by the enemy radar!";
	}
	else {
		std::ostringstream stream;
		stream << std::fixed << std::setprecision(2) << gameTimer;
		messageText = "Time remaining until impact: " + stream.str();
	}
	if (gameTimer < 0) {
		failEntity->model.setTranslation(playerEntity->model.getTranslation() - Vector3(0.0, 1.0, 0.1));
	}
	else if (playerPosition.y <= 0) {
		failEntity->model.setTranslation(playerEntity->model.getTranslation() - Vector3(0.0, 1.0, 0.1));
	}

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

Mesh* World::createFullscreenQuad(int windowWidth, int windowHeight) {


	Mesh* quadMesh = new Mesh();
	quadMesh->createQuad(0.0f, 0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight), false);

	// Create a material for the quad
	Material quadMaterial;
	quadMaterial.shader = basicShader;
	quadMaterial.diffuse = Texture::Get("data/textures/Solid_white.png");

	// Create an EntityMesh for the quad
	EntityMesh* quadEntity = new EntityMesh(quadMesh, quadMaterial, "FullscreenQuad");

	// Add the quad entity to the root entity
	root->addChild(quadEntity);

	return quadMesh;
}