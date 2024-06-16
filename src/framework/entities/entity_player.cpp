#include "entity_player.h"


//float camera_yaw = 0.0f;
//float speed_mult = 1.0f; 
//Vector3 velocity = Vector3(0.0f, 0.0f, 0.0f); 
std::vector<int> activeChannels;

bool isTransitioning = false;
float transitionTimer = 0.0f;
float transitionDuration = 1.0f;

EntityPlayer::EntityPlayer(Vector3 position) {

    //playerEntity = new EntityMesh(nullptr, Material(), "Player");
    this->position = position;
    model.setTranslation(position);
    smoothedTarget = position;
    targetSpeed = 5.0f;
}

void EntityPlayer::update(float seconds_elapsed, EntityPlayer* player, EntityMesh* skybox, EntityMesh* bomb, EntityCollider* collider, EntityMesh* explosion, float playerTimer) {
    handleInput(seconds_elapsed, skybox, bomb, player, playerTimer);
    
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
    speed = speed * (1.0f - smoothingFactor) + targetSpeed * smoothingFactor;


    skybox->model.setTranslation(model.getTranslation());
 
    Vector3 gravity(0.0f, -9.81f, 0.0f);
    updateBombPhysics(bomb, seconds_elapsed, gravity, explosion, player->velocity);



}

void EntityPlayer::handleInput(float seconds_elapsed, EntityMesh* skybox, EntityMesh* bomb, EntityMesh* player, float playerTimer) {
    
    // Aqu� se manejar�an las entradas del usuario para mover el avi�n
    if (playerTimer <= 0){
        model.setTranslation(this->position);
    }
    else if (this->position.y <= 0) {
        model.setTranslation(this->position);
    }
    else {
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
            targetSpeed = 8.0;
            model.translate(0, 0, seconds_elapsed * speed);
        }

        if (Input::wasKeyPressed(SDL_SCANCODE_LSHIFT)) {
            Audio::Play("data/audio/accelerate.mp3", 0.7);
        }

        if (Input::wasKeyPressed(SDL_SCANCODE_Q)) {
            cameraViewMode = (cameraViewMode + 1) % 4;
        }

        if (Input::wasKeyPressed(SDL_SCANCODE_E)) {
            dropBomb(bomb, player);//, seconds_elapsed);
            int newChannel = Audio::Play("data/audio/bombdrop.mp3", 0.3);
            activeChannels.push_back(newChannel);
        }
        targetSpeed = 5.0;
        model.translate(0, 0, seconds_elapsed * speed);
        this->position = model.getTranslation();
    }
}

void EntityPlayer::playerPOV(Camera* camera, float seconds_elapsed) {
    Vector3 planePosition = model.getTranslation();
    Vector3 planeFront = model.frontVector();
    Vector3 planeRight = model.rightVector();
    planeFront.y = 0.0f;
    planeRight.y = 0.0f;
    planeFront.normalize();
    planeRight.normalize();

    if (cameraViewMode == 0) { // Third-person view
        // Smooth the transition to the new target position
        float smoothingFactor = 0.1f;
        smoothedTarget = smoothedTarget * (1.0f - smoothingFactor) + planePosition * smoothingFactor;

        // Determine the camera's position relative to the plane
        Vector3 cameraOffset = Vector3(0.0f, 0.1f, -0.3f);
        Vector3 eye = smoothedTarget + planeFront * cameraOffset.z + Vector3(0.0f, cameraOffset.y, 0.0f);
        Vector3 center = smoothedTarget;
        Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

        // Update the camera's view matrix
        camera->lookAt(eye, center, up);
    }
    else if (cameraViewMode == 1) {
        float smoothingFactor = 0.1f;
        smoothedTarget = smoothedTarget * (1.0f - smoothingFactor) + planePosition * smoothingFactor;

        // Determine the camera's position relative to the plane
        Vector3 cameraOffset = Vector3(0.0f, 1.0f, -0.7f);
        Vector3 eye = smoothedTarget + planeFront * cameraOffset.z + Vector3(0.0f, cameraOffset.y, 0.0f);
        Vector3 center = smoothedTarget;
        Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

        // Update the camera's view matrix
        camera->lookAt(eye, center, up);
    }
    else if (cameraViewMode == 2) {
        float smoothingFactor = 0.1f;
        smoothedTarget = smoothedTarget * (1.0f - smoothingFactor) + planePosition * smoothingFactor;

        // Determine the camera's position relative to the plane
        Vector3 cameraOffset = Vector3(0.0f, 1.0f, 0.7f);
        Vector3 eye = smoothedTarget + planeFront * cameraOffset.z + Vector3(0.0f, cameraOffset.y, 0.0f);
        Vector3 center = smoothedTarget;
        Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

        // Update the camera's view matrix
        camera->lookAt(eye, center, up);
    }
    else { // First-person view
        Vector3 front = model.frontVector(); //final_rotation.frontVector().normalize();  

        Vector3 eye;
        Vector3 center;

        float orbit_dist = 0.6f;
        eye = model.getTranslation() - front * orbit_dist;
        center = model * Vector3(0.0f, 0.1f, 0.0f);


        camera->lookAt(eye, center, model.rotateVector(Vector3(0.0f, 1.0f, 0.0f)));

    }

    // Update the rest of the scene
    Entity::update(seconds_elapsed);
}

void EntityPlayer::dropBomb(EntityMesh* bomb, EntityMesh* player) {

    bomb->model.setTranslation(model.getTranslation());
    bomb->mass = 1100;
    // Calculate the initial velocity based on the plane's speed and direction
    Vector3 planeForward = model.frontVector();
    Vector3 planeVelocity = planeForward * speed;

    // Set bomb's initial velocity
    bomb->velocity = planeVelocity;

    bomb->isLaunched = true;
}

Vector3 EntityPlayer::calculateDragForce(Vector3 velocity) {
    float speed = velocity.length();
    float dragMagnitude = 0.5f * airDensity * speed * speed * dragCoefficient * bombCrossSectionalArea;
    Vector3 dragForce = -velocity.normalize() * dragMagnitude;
    return dragForce;
}

// Update bomb physics
void EntityPlayer::updateBombPhysics(EntityMesh* bomb, float seconds_elapsed, const Vector3& gravity, EntityMesh* explosion, Vector3& velocity) {
    if (bomb->isLaunched) {
        Vector3 currentPos = bomb->model.getTranslation();
        Vector3 dragForce = calculateDragForce(bomb->velocity);
        Vector3 acceleration = gravity + (dragForce / bomb->mass);  // Assuming mass is a property of the bomb

        //Vector3 acceleration = gravity

        Vector3 newPos = currentPos + bomb->velocity * seconds_elapsed + 0.5f * acceleration * seconds_elapsed * seconds_elapsed;
        bomb->velocity += acceleration * seconds_elapsed;
        bomb->model.setTranslation(newPos);

        // Check if the bomb has hit the ground (assuming the ground is at y = 0)
        if (newPos.y <= 0.0f) {
            bomb->model.setTranslation(Vector3(newPos.x, 0.0f, newPos.z));
            bomb->velocity = Vector3(0.0f, 0.0f, 0.0f);
            bomb->isLaunched = false;  // Mark bomb as no longer active
            bomb->isExploded = true;
            explosion->model.setTranslation(newPos);
            Audio::Play("data/audio/nuclearexp.mp3", 1);
        }
    }
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
