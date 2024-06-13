//#include "entity_bomb.h"
//
//EntityBomb::EntityBomb(Vector3 position, Vector3 velocity) {
//    model.setTranslation(position);
//    this->velocity = velocity;
//    this->launched = false;
//    this->exploded = false;
//    this->explosionTime = 5.0f;
//}
//
//void EntityBomb::update(float seconds_elapsed) {
//    // Update position with basic physics: s = s0 + v0 * t + 0.5 * a * t^2
//    Vector3 gravity(0.0f, -9.81f, 0.0f); // Gravity acceleration
//    
//    model.translate(velocity * seconds_elapsed + 0.5f * gravity * seconds_elapsed * seconds_elapsed);
//    //position = position + velocity * seconds_elapsed + 0.5f * gravity * seconds_elapsed * seconds_elapsed;
//    velocity = velocity + gravity * seconds_elapsed;
//    
//    // Check if the bomb has hit the ground (assuming ground is at y = 0)
//    this->position = model.getTranslation();
//    if (position.y <= 0.0f) {
//        position.y = 0.0f;
//        exploded = true; // Mark the bomb as exploded
//        launched = false;
//    }
//
//    // Decrease explosion time
//    explosionTime -= seconds_elapsed;
//    if (explosionTime <= 0.0f) {
//        exploded = true;
//        launched = false;
//    }
//}
