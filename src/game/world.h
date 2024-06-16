#pragma once

#include "framework/entities/entity.h"
#include "framework/entities/entity_player.h"
#include "framework/entities/entity_mesh.h"
#include "framework/entities/entity_bomb.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "graphics/shader.h"
#include "scene.h"
#include <stdio.h>


//#endif /* world_h */

//Entity* root;

class World {
public:
    static World* instance;

    World(int window_width, int window_height);
    Matrix44 model;
    Entity* root = nullptr;

    Mesh* playerMesh;
    Mesh* projectileMesh = nullptr;
    Mesh* powerUpMesh = nullptr;

    Texture* texture = nullptr; //loas textures
    Texture* playerTexture = nullptr;
    Shader* basicShader;
    Material playerMaterial;

    Scene* scene;
    Camera* camera;

    EntityPlayer* playerEntity;

    EntityMesh* bombEntity;
    Mesh* bombMesh;
    Material bombMaterial;
    Texture* bombTexture;

    EntityMesh* nuclearEntity;
    Mesh* nuclearMesh;
    Material nuclearMaterial;
    Texture* nuclearTexture;

    Camera* camera2D;

    //Mesh* quad;

    Material cubemap;
    Material skyboxMaterial;
    EntityMesh* skybox;
    void render();
    void update(float elapsed_time);
    void cleanRoot();
    void onKeyDown(SDL_KeyboardEvent event);
    Mesh* createFullscreenQuad(int window_width, int window_height);
    void startTransition();
    void renderTransition();



    EntityCollider collider;
};
