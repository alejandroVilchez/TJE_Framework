#pragma once

#include "framework/entities/entity.h"
#include "framework/entities/entity_player.h"
#include "framework/entities/entity_mesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "graphics/shader.h"
#include "game/scene.h"
#include "game/game.h"
#include <stdio.h>


//#endif /* world_h */

//Entity* root;

class World {
public:
    static World* instance;

    World();
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

    Material cubemap;
    Material skyboxMaterial;
    EntityMesh* skybox;
    void render();
    void update(float elapsed_time);
    void cleanRoot();
    void onKeyDown(SDL_KeyboardEvent event);
};
