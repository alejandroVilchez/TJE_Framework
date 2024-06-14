#include "entity_player.h"


//float camera_yaw = 0.0f;
//float speed_mult = 1.0f; 
//Vector3 velocity = Vector3(0.0f, 0.0f, 0.0f); 
std::vector<int> activeChannels;

EntityPlayer::EntityPlayer(Vector3 position) {

    //playerEntity = new EntityMesh(nullptr, Material(), "Player");
    this->position = position;
    model.setTranslation(position);
}

void EntityPlayer::update(float seconds_elapsed, EntityPlayer* player, EntityMesh* skybox, EntityMesh* bomb, EntityCollider* collider) {
    handleInput(seconds_elapsed, skybox, bomb);
    
    std::vector<EntityMesh*> sceneEntities = collider->getEntitiesInScene();
    for (auto& entity : sceneEntities) {
        if (entity == player || entity == skybox || entity == bomb)
            continue;  // Skip self and special entities like skybox and bomb

        // Perform collision detection
        if (EntityMesh::checkCollision(player, entity)) {
            // Collision detected, handle it (e.g., play sound)
            Audio::Play("data/audio/select.wav", 1.0);
            // Example: Adjust game state or response to collision
            // velocity = Vector3(0.0f, 0.0f, 0.0f);
        }
}

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
            Audio::Play("data/audio/nuclearexp.mp3");
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

    if (Input::wasKeyPressed(SDL_SCANCODE_LSHIFT)) {
        Audio::Play("data/audio/accelerate.mp3", 0.7);
    }

    if (Input::wasKeyPressed(SDL_SCANCODE_E)) {
        dropBomb(bomb);//, seconds_elapsed);
        int newChannel = Audio::Play("data/audio/bombdrop.mp3", 0.3);
        activeChannels.push_back(newChannel);
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
//////void entityplayer::dropbomb(entitymesh* bomb, float seconds_elapsed) {
//    bomb->islaunched = true;
//    vector3 gravity(0.0f, -9.81f, 0.0f); // gravity acceleration
//
//    bomb->model.translate(model.gettranslation() - bomb->bombspeed * seconds_elapsed + 0.5f * gravity * seconds_elapsed * seconds_elapsed);
//    //position = position + velocity * seconds_elapsed + 0.5f * gravity * seconds_elapsed * seconds_elapsed;
//    bomb->bombspeed = bomb->bombspeed + -9.81f * seconds_elapsed;
//
//    // check if the bomb has hit the ground (assuming ground is at y = 0)
//    this->position = bomb->model.gettranslation();
//    if (position.y <= 0.0f) {
//        position.y = 0.0f;
//        isexploded = true; // mark the bomb as exploded
//        islaunched = false;
//    }
//
//    // decrease explosion time
//    bomb->explosiontime -= seconds_elapsed;
//    if (bomb->explosiontime <= 0.0f) {
//        isexploded = true; // mark the bomb as exploded
//        islaunched = false;
//    }
//    
//}
