#pragma once

#include "entity.h"
#include "entity_mesh.h"
#include "entity_bomb.h"
#include <vector>
#include "framework/input.h"
#include <cmath>
#include "framework/includes.h"
#include "framework/camera.h"
#include "framework/audio.h"
#include "entity_collider.h"

//class Bomb : public Entity {
//public:
//    Bomb(Vector3 position, Vector3 velocity);
//    void update(float deltaTime);
//    // Otras funciones necesarias para la clase Bomb
//};

class EntityPlayer : public EntityMesh {
public:
    float speed = 5.0f;
    Vector3 position;

    EntityPlayer(Vector3 position);
    void update(float seconds_elapsed, EntityPlayer* player, EntityMesh* skybox, EntityMesh* bomb, EntityCollider* collider);
    void handleInput(float seconds_elapsed, EntityMesh* skybox, EntityMesh* bomb);
    void playerPOV(Camera* camera, float seconds_elapsed);
    void dropBomb(EntityMesh* bomb);
    void updateBomb(EntityMesh& bomb, float seconds_elapsed);


private:
    std::vector<EntityMesh> activeBombs;  // Track active bombs
    EntityMesh* playerEntity;
    float rotation_speed = 2.0f;
    std::vector<HCHANNEL> activeChannels;  // Track active sound channels for bomb drops
};


