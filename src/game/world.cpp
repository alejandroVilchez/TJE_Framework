#include "world.h"

World* World::world;

World::World() {

    root = new Entity();


    basicShader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	playerMesh = Mesh::Get("data/meshes/B2-final.obj");
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
	
	scene = new Scene();
	scene->parseScene("data/myscene.scene");
}

void World::render(Camera* camera) {
    root->render(camera);
    if (player) {
        playerEntity->render(camera);

    }
}

void World::update(float elapsed_time, Camera* camera) {
	playerEntity->update(elapsed_time, skybox);
	playerEntity->playerPOV(camera, elapsed_time);
    root->update(elapsed_time);
}

void World::cleanRoot() {
    for (int i = root->children.size() - 1; i >= 0; i--) { //clean root
        root->removeChild(root->children[i]);
    }
}