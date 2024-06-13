#include "entity_player.h"


//float camera_yaw = 0.0f;
//float speed_mult = 1.0f; 
//Vector3 velocity = Vector3(0.0f, 0.0f, 0.0f); 

EntityPlayer::EntityPlayer(Vector3 position) {

    this->position = position;
    model.setTranslation(position);
}

void EntityPlayer::update(float seconds_elapsed, EntityMesh* skybox, EntityMesh* bomb) {
    handleInput(seconds_elapsed, skybox, bomb);
    

    skybox->model.setTranslation(model.getTranslation());
 
    Vector3 gravity(0.0f, -9.81f, 0.0f);
    if (bomb->isLaunched) {
        Vector3 currentPos = bomb->model.getTranslation();
        Vector3 newPos = currentPos + bomb->velocity * seconds_elapsed + 0.5f * gravity * seconds_elapsed * seconds_elapsed;
        bomb->velocity = bomb->velocity + gravity * seconds_elapsed;
        bomb->model.setTranslation(newPos);

        // Chequear si la bomba ha tocado el suelo (suponiendo que el suelo está en y = 0)
        if (newPos.y <= 0.0f) {
            bomb->model.setTranslation(Vector3(newPos.x, 0.0f, newPos.z));
            bomb->velocity = Vector3(0.0f, 0.0f, 0.0f);
            bomb->isLaunched = false; // Mark bomb as no longer active
        }
    }
}

void EntityPlayer::handleInput(float seconds_elapsed, EntityMesh* skybox, EntityMesh* bomb) {

    
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
    if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) {
        model.translate(0, 0, seconds_elapsed * speed * 1.5);
    }
    if (Input::isKeyPressed(SDL_SCANCODE_E)) {
        dropBomb(bomb);//, seconds_elapsed);
    }
    model.translate(0, 0, seconds_elapsed * speed);

}

void EntityPlayer::playerPOV(Camera* camera, float seconds_elapsed) {
    
    //if(Input::isMousePressed(SDL_BUTTON_LEFT) || Input::isMousePressed(SDL_BUTTON_MIDDLE)){
    //    camera_yaw += Input::mouse_delta.x * 0.005f;
    //    camera_pitch += Input::mouse_delta.y * 0.005f;
    //    camera_pitch = clamp(camera_pitch, -M_PI * 0.5f, M_PI * 0.5f);
    //}
    //else {
    //    // Slowly return to the plane's forward direction when the mouse is not pressed
    //    camera_yaw *= 0.95f;
    //    camera_pitch *= 0.95f;
    //}

    //Matrix44 mYaw;
    //mYaw.setRotation(camera_yaw, Vector3(0, 1, 0));

    //Matrix44 mPitch;
    //mPitch.setRotation(camera_pitch, Vector3(-1, 0, 0));

    //Matrix44 final_rotation = mPitch * mYaw;
    Vector3 front = model.frontVector(); //final_rotation.frontVector().normalize();  
    
    Vector3 eye;
    Vector3 center;

    float orbit_dist = 0.6f;
    eye = model.getTranslation() - front * orbit_dist;
    center = model * Vector3(0.0f, 0.1f, 0.0f);


    camera->lookAt(eye, center, model.rotateVector(Vector3(0.0f, 1.0f, 0.0f)));
    
    //update our scene:
    Entity::update(seconds_elapsed);

}

void EntityPlayer::dropBomb(EntityMesh* bomb) {

    bomb->model.setTranslation(model.getTranslation()); 
    bomb->velocity = model.frontVector() * bombSpeed; 
    bomb->isLaunched = true;
}
//void EntityPlayer::dropBomb(EntityMesh* bomb, float seconds_elapsed) {
//    bomb->isLaunched = true;
//    Vector3 gravity(0.0f, -9.81f, 0.0f); // Gravity acceleration
//
//    bomb->model.translate(model.getTranslation() - bomb->bombSpeed * seconds_elapsed + 0.5f * gravity * seconds_elapsed * seconds_elapsed);
//    //position = position + velocity * seconds_elapsed + 0.5f * gravity * seconds_elapsed * seconds_elapsed;
//    bomb->bombSpeed = bomb->bombSpeed + -9.81f * seconds_elapsed;
//
//    // Check if the bomb has hit the ground (assuming ground is at y = 0)
//    this->position = bomb->model.getTranslation();
//    if (position.y <= 0.0f) {
//        position.y = 0.0f;
//        isExploded = true; // Mark the bomb as exploded
//        isLaunched = false;
//    }
//
//    // Decrease explosion time
//    bomb->explosionTime -= seconds_elapsed;
//    if (bomb->explosionTime <= 0.0f) {
//        isExploded = true; // Mark the bomb as exploded
//        isLaunched = false;
//    }
//    
//}