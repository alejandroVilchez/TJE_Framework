#include "entity_collider.h"
#include "framework/camera.h"

#include <algorithm>

void EntityCollider::addEntity(EntityMesh* entity) {
    entities.push_back(entity);
}

void EntityCollider::removeEntity(EntityMesh* entity) {
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it);
    }
}

std::vector<EntityMesh*> EntityCollider::getEntitiesInScene() {
    return entities;
}
//bool EntityCollider::testCollisionWithScene(const Vector3& player_position) {
//    // Iterate through the entities in the scene and check for collisions
//    for (auto& entity : scene->root.children) {
//        if (entity->mesh) {  // Assuming entity has a mesh component
//            // Example collision check with a sphere around the player (adjust as per your game logic)
//            float sphereRadius = 0.5f;  // Example radius
//            if (entity->model.getTranslation().distance(player_position) < sphereRadius) {
//                // Collision detected
//                return true;
//            }
//        }
//    }
//
//    return false;  // No collision detected
//}