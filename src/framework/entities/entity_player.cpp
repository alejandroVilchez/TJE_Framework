#include "entity_player.h"
#include "framework/input.h"
#include <cmath>
#include "framework/includes.h"
#include "framework/camera.h"

float camera_yaw = 0.0f;
float speed_mult = 1.0f; 
Vector3 velocity = Vector3(0.0f, 0.0f, 0.0f); 

EntityPlayer::EntityPlayer() {

}

EntityPlayer::~EntityPlayer() {
    // Destructor implementation (if needed)
}

void EntityPlayer::update(float seconds_elapsed) {
    // Apply rotation based on input
    Matrix44 mYaw;
    mYaw.setRotation(camera_yaw, Vector3(0, 1, 0));

    Vector3 front = mYaw.frontVector();
    Vector3 right = mYaw.rightVector();

    Vector3 position = model.getTranslation();

    Vector3 move_dir;

    // Update movement direction based on input
    if (Input::isKeyPressed(SDL_SCANCODE_W)) {
        move_dir += front;
    }
    if (Input::isKeyPressed(SDL_SCANCODE_S)) {
        move_dir -= front;
    }
    if (Input::isKeyPressed(SDL_SCANCODE_A)) {
        move_dir -= right;
    }
    if (Input::isKeyPressed(SDL_SCANCODE_D)) {
        move_dir += right;
    }

    move_dir.normalize();
    move_dir *= speed_mult; 
    velocity += move_dir;

    position += velocity * seconds_elapsed;

    // Decrease velocity when not moving
    velocity.x *= 0.5f;
    velocity.z *= 0.5f;

    model.setTranslation(position);

    EntityMesh::update(seconds_elapsed);
}
