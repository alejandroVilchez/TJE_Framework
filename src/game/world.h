#pragma once
#include "framework/entities/entity.h"
#include "framework/entities/entity_player.h"
#include "framework/entities/entity_mesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "graphics/shader.h"
#include "game/scene.h"
#include <stdio.h>


//#endif /* world_h */

//Entity* root;
class Camera;

class World {
public:
    static World* world;

    static World* get_instance() {
        if (world != nullptr)
            return world;
        world = new World();
        return world;
    }

    World();
    Matrix44 model;
    Entity* root = nullptr;
    EntityPlayer* player = nullptr;

    Mesh* playerMesh = nullptr;
    Mesh* projectileMesh = nullptr;
    Mesh* powerUpMesh = nullptr;

    Texture* texture = nullptr; //loas textures
    Texture* playerTexture = nullptr;
    Shader* basicShader = nullptr;

    Mesh* playerMesh = nullptr; // Load a cube mesh
    Shader* basicShader = nullptr;
    Material playerMaterial;

    Scene* scene;

    EntityPlayer* playerEntity;

    Material cubemap;
    Material skyboxMaterial;
    EntityMesh* skybox;
    void render(Camera* camera);
    void update(float elapsed_time, Camera* camera);
    void cleanRoot();
};
