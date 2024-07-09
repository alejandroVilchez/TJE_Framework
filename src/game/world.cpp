#include "world.h"

float angles = 0;
float mouse_speeds = 100.0f;
bool engine = 0;
HCHANNEL channel2;
HCHANNEL radar;
bool damg = false;


World* World::instance;

World::World(int window_width, int window_height) {

	instance = this;

	this->world_window_width = window_width;
	this->world_window_height = window_height,
	
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

	loseText1 = "";
	loseText2 = "";
	loseText3 = "";

	//// Example of shader loading using the shaders manager
	//shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

	//------- Player --------
	playerTexture = Texture::Get("data/textures/texture.tga"); // Load a texture

	playerMaterial.shader = basicShader;
	playerMaterial.diffuse = playerTexture;

	Vector3 position = (-200.0f, 200.0f, 22.0f);
	playerEntity = new EntityPlayer(position);//EntityMesh(playerMesh, playerMaterial, "Player");

	playerEntity->mesh = playerMesh;
	playerEntity->material = playerMaterial;
	playerEntity->name = "Player";
	playerEntity->damaged = false;
	playerEntity->position.y = 22;

	gameTimer = 15;
	timerScene2 = 10;
	missilelost = false;
	radarTimer = 100;
	engine = 0;
	planecrashed = false;
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
	if (damg) {
		{
			failEntity->render(camera);
			loseText1 = "You die with the Wuhu island";
			Audio::Stop(channel2);
		}
	}
	if (gameTimer < 0) {
		failEntity->render(camera);
		//drawText(this->world_window_width / 2 - 130, this->world_window_height / 2, "Game Over", Vector3(1, 1, 1), 5);
		loseText2 = "You failed to destroy the island...";
		Audio::Stop(radar);
		Audio::Stop(channel2);
	}
	else if (playerPosition.y < 0) {
		failEntity->render(camera);
		loseText3 = "You die with the Wuhu island";

		Audio::Stop(channel2);
	}
	else {
		drawText(50, this->world_window_height - 50, messageText, Vector3(1, 1, 1), 2);
	}


	std::ostringstream stream1;
	stream1 << std::fixed << std::setprecision(2) << playerPosition.y * 20;
	playerHeight = "Height: " + stream1.str() + " m.";
	drawText(50, 50, playerHeight, Vector3(1, 1, 1), 2);
	drawText(this->world_window_width / 2 - 180, this->world_window_height / 2, loseText3, Vector3(1, 1, 1), 3);
	drawText(this->world_window_width / 2 - 250, this->world_window_height / 2, loseText2, Vector3(1, 1, 1), 3);
	drawText(this->world_window_width / 2 - 250, this->world_window_height / 2, loseText1, Vector3(1, 1, 1), 3);

	if (engine == 0) {
		channel2 = Audio::Play("data/audio/bombersound.mp3", 1, BASS_SAMPLE_LOOP);
		engine = 1;
	}

}

void World::update(float elapsed_time) {

	//float speed = elapsed_time * mouse_speeds; //the speed is defined by the seconds_elapsed so it goes constant

	// Example
	//angles += (float)elapsed_time * 10.0f;
	if (playerEntity->detected and radarTimer <= 0) {
		radar = Audio::Play("data/audio/radar.wav", 1);
		gameTimer -= elapsed_time;
		messageText = "You have been discovered by the enemy radar! Missile coming";
		//messageText = std::to_string(playerEntity->directionChangePoints);
	}
	if (missilelost) {
		radarTimer -= elapsed_time;
	}
	if (playerEntity->detectedonce) {
		missileTimer -= elapsed_time;
	}
	playerEntity->update(elapsed_time, playerEntity, skybox, bombEntity, &collider, nuclearEntity, gameTimer);
	playerEntity->playerPOV(camera, elapsed_time);

	playerPosition = playerEntity->model.getTranslation();
	if (gameTimer < 5) {
		alarm = Audio::Play("data/audio/alarm.wav", 0.5);
	}
	if (playerEntity->directionChangePoints > 10) {
		playerEntity->detected = false;
		gameTimer = 15;
		Audio::Stop(alarm);
		missilelost = true;
		radarTimer = rand() % 5;
	}
	//else {
	//	std::ostringstream stream;
	//	stream << std::fixed << std::setprecision(2) << gameTimer;
	//	messageText = "Time remaining until impact: " + stream.str();
	//}
	if (gameTimer < 0) {
		failEntity->model.setTranslation(playerEntity->model.getTranslation() - Vector3(0.0, 1.0, 0.1));
		Audio::Stop(alarm);
		Audio::Stop(radar);
		if (planecrashed == false) {
			planeexp = Audio::Play("data/audio/planeexp.mp3", 0.5);
			planecrashed = true;
		}
	}
	if (radarTimer == 0) {
		missilelost = false;
		Audio::Stop(radar);
		Audio::Stop(alarm);
		planeexp = Audio::Play("data/audio/planeexp.mp3", 0.25);
		messageText = "missile dodged, but you have been detected, be fast";
		playerEntity->detectedonce = true;
		missileTimer = rand() % 50 + 10;
		radarTimer = 100;

	}

	if (playerEntity->damaged == true) {
		failEntity->model.setTranslation(playerEntity->model.getTranslation() - Vector3(0.0, 1.0, 0.1));
		timerScene -= elapsed_time;
		if (timerScene < 1.0) {
			//playerEntity.setTranslation(position);
			if (planecrashed == false) {
				failEntity->model.setTranslation(playerEntity->model.getTranslation() - Vector3(0.0, 1.0, 0.1));
				playerEntity->dmg = true;
				damg = true;
				planeexp = Audio::Play("data/audio/planeexp.mp3, ", 0.5);
				planecrashed = true;
			}
		}
		if (timerScene < 0.0) {
			this->badEnding = true;
		}
	}

	else if (playerPosition.y <= 0) {
		failEntity->model.setTranslation(playerEntity->model.getTranslation() - Vector3(0.0, 1.0, 0.1));
		if (planecrashed == false) {
			planeexp = Audio::Play("data/audio/planeexp.mp3", 0.5);
			planecrashed = true;
		}
		timerScene -= elapsed_time;
		if (timerScene < 0.0) {
			this->badEnding = true;
		}
	}
	if (playerEntity->bombin) {
		messageText = "Good job, those Chanin communists did not expect that!";
		timerScene2 -= elapsed_time;
		if (timerScene2 < 0.0) {
			this->goodEnding = true;
			Audio::Stop(radar);
			Audio::Stop(planeexp);
			Audio::Stop(alarm);
		}
	}
	if (playerEntity->bombout) {
		if (playerEntity->damaged) {
			messageText = "You were flying too close to the explosion, good bye soldier...";
		}
		else {
			messageText = "Idiot, we were supposed to bomb them, not the ocean!";
		}
		timerScene2 -= elapsed_time;
		if (timerScene2 < 0.0) {
			this->badEnding = true;
			Audio::Stop(radar);
			Audio::Stop(planeexp);
			Audio::Stop(alarm);
		}
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

void World::resetGame() {
	this->goodEnding = false;
	this->badEnding = false;
	
	gameTimer = 15.f;

	messageText = "";
	loseText1 = "";
	loseText2 = "";
	loseText3 = "";
	
	missilelost = false;
	timerScene2 = 10.0f;
	radarTimer = 100.0f;
	missileTimer = 0.0f;
	engine = 0;
	damg = false;
	
	playerPosition = Vector3(-200.0f, 22.0f, 200.0f);
	playerEntity->model.setTranslation(playerPosition);
	
	playerEntity->resetPlayer();

	Audio::Destroy();
	Audio::Init();
	//cleanRoot();

	//root->addChild(playerEntity);
	//root->addChild(bombEntity);
	//root->addChild(nuclearEntity);
	//root->addChild(failEntity);
	//root->addChild(skybox);

	bombEntity->isLaunched = false;
	bombEntity->isExploded = false;

	/*nuclearEntity->model.setTranslation(Vector3(0.0f, 0.0f, 0.0f));
	failEntity->model.setTranslation(Vector3(0.0f, 0.0f, 0.0f));*/


	planecrashed = false;
	detected = false; 
}