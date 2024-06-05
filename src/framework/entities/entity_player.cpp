#include "entity_player.h"
#include "framework/input.h"
#include <cmath>
#include "framework/includes.h"
#include "framework/camera.h"

//float camera_yaw = 0.0f;
//float speed_mult = 1.0f; 
//Vector3 velocity = Vector3(0.0f, 0.0f, 0.0f); 

EntityPlayer::EntityPlayer(Vector3 position) /*: EntityMesh(position), speed(10.0f)*/ {
    // Inicializaci�n adicional si es necesaria
    this->position = position;
    model.setTranslation(position);
}

void EntityPlayer::update(float seconds_elapsed, EntityMesh* skybox) {
    handleInput(seconds_elapsed, skybox);
    
    
    model.translate(this->position);
    skybox->model.translate(this->position);
    //// Actualiza las bombas
    //for (Bomb& bomb : bombs) {
    //    bomb.update(deltaTime);
    //}

    //// Elimina las bombas que hayan explotado o salido del �rea de juego
    //bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](Bomb& bomb) {
    //    return bomb.hasExploded() || bomb.isOutOfBounds();
    //    }), bombs.end());
}

void EntityPlayer::handleInput(float seconds_elapsed, EntityMesh* skybox) {

    
    // Aqu� se manejar�an las entradas del usuario para mover el avi�n
    
    if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) {
        this->model.rotate(seconds_elapsed * rotation_speed, Vector3(-1.0f, 0.0f, 0.0f));

    }
    if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) {
        this->model.rotate(seconds_elapsed * rotation_speed, Vector3(1.0f, 0.0f, 0.0f));

    }
    if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) {
        this->model.rotate(seconds_elapsed * rotation_speed, Vector3(0.0f, 0.0f, 1.0f));

    }
    if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) {
        this->model.rotate(seconds_elapsed * rotation_speed, Vector3(0.0f, 0.0f, -1.0f));

    }
    if (Input::isKeyPressed(SDL_SCANCODE_SPACE)) {
        //dropBomb();
    }
    this->position += model.frontVector() * seconds_elapsed * speed;
    
    //model.setTranslation(this->position);

}

void EntityPlayer::playerPOV(Camera* camera, float seconds_elapsed) {
    
    if(Input::isMousePressed(SDL_BUTTON_LEFT) || Input::isMousePressed(SDL_BUTTON_MIDDLE)){
        camera_yaw += Input::mouse_delta.x * 0.005f;
        camera_pitch += Input::mouse_delta.y * 0.005f;
        camera_pitch = clamp(camera_pitch, -M_PI * 0.5f, M_PI * 0.5f);
    }
    else {
        // Slowly return to the plane's forward direction when the mouse is not pressed
        camera_yaw *= 0.95f;
        camera_pitch *= 0.95f;
    }

    Matrix44 mYaw;
    mYaw.setRotation(camera_yaw, Vector3(0, 1, 0));

    Matrix44 mPitch;
    mPitch.setRotation(camera_pitch, Vector3(-1, 0, 0));

    Matrix44 planeRotation = model.getRotationOnly();
    //Vector3 planeFront = model.frontVector();
    Matrix44 final_rotation = mPitch * mYaw; //* planeRotation;
    Vector3 front = final_rotation.frontVector().normalize();  //* planeFront;
    
    Vector3 eye;
    Vector3 center;

    float orbit_dist = 0.6f;
    eye = model.getTranslation() - front * orbit_dist;
    center = model.getTranslation() + Vector3(0.0f, 0.1f, 0.0f);


    camera->lookAt(eye, center, Vector3(0.0f, 1.0f, 0.0f));
    
    //update our scene:
    Entity::update(seconds_elapsed);

    //EntityPlayer::update(seconds_elapsed);
}

//void EntityPlayer::dropBomb() {
//    Vector3 bombPosition = this->position; // La posici�n inicial de la bomba es la del avi�n
//    Vector3 bombVelocity = Vector3(0, -10, 0); // La bomba cae hacia abajo
//    bombs.push_back(Bomb(bombPosition, bombVelocity));
//}



//void EntityPlayer::update(float seconds_elapsed) {
//    // Apply rotation based on input
//    Matrix44 mYaw;
//    mYaw.setRotation(camera_yaw, Vector3(0, 1, 0));
//
//    Vector3 front = mYaw.frontVector();
//    Vector3 right = mYaw.rightVector();
//
//    Vector3 position = model.getTranslation();
//
//    Vector3 move_dir;
//
//    // Update movement direction based on input
//    if (Input::isKeyPressed(SDL_SCANCODE_W)) {
//        move_dir += front;
//    }
//    if (Input::isKeyPressed(SDL_SCANCODE_S)) {
//        move_dir -= front;
//    }
//    if (Input::isKeyPressed(SDL_SCANCODE_A)) {
//        move_dir -= right;
//    }
//    if (Input::isKeyPressed(SDL_SCANCODE_D)) {
//        move_dir += right;
//    }
//
//    move_dir.normalize();
//    move_dir *= speed_mult;
//    velocity += move_dir;
//
//    position += velocity * seconds_elapsed;
//
//    // Decrease velocity when not moving
//    velocity.x *= 0.5f;
//    velocity.z *= 0.5f;
//
//    model.setTranslation(position);
//
//    EntityMesh::update(seconds_elapsed);
//}