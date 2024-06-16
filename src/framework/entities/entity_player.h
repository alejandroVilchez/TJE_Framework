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

const float dragCoefficient = 0.5f;
const float airDensity = 1.225f;  // kg/m^3
const float bombCrossSectionalArea = 0.1f;

class EntityPlayer : public EntityMesh {
public:
    float speed = 5.0f;
    Vector3 position;
    Vector3 velocity;

    float directionChangePoints = 0;
    bool detected = false;
    bool detectedonce = false;

    EntityPlayer(Vector3 position);
    void update(float seconds_elapsed, EntityPlayer* player, EntityMesh* skybox, EntityMesh* bomb, EntityCollider* collider, EntityMesh* explosion, float playerTimer);
    void handleInput(float seconds_elapsed, EntityMesh* skybox, EntityMesh* bomb, EntityMesh* player, float playerTimer);
    void playerPOV(Camera* camera, float seconds_elapsed);
    void dropBomb(EntityMesh* bomb, EntityMesh* player);
    void updateBomb(EntityMesh& bomb, float seconds_elapsed);
    Vector3 calculateDragForce(Vector3 velocity);
    int cameraViewMode = 0;
    float targetSpeed;
    float smoothingFactor = 0.001f;
    float randheight;

    void handleDodgeActions(float seconds_elapsed);
    void evaluateMovements();
    // Update bomb physics
    void updateBombPhysics(EntityMesh* bomb, float seconds_elapsed, const Vector3& gravity, EntityMesh* explosion, Vector3& velocity);


private:
    std::vector<EntityMesh> activeBombs;  // Track active bombs
    Vector3 smoothedTarget;
    EntityMesh* playerEntity;
    float rotation_speed = 0.7f;
    std::vector<HCHANNEL> activeChannels;  // Track active sound channels for bomb drops
};


