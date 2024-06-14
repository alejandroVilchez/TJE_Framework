#pragma once

#include "framework/includes.h"
#include "framework/framework.h"
#include "entity_mesh.h"

class EntityCollider {
private:
    std::vector<EntityMesh*> entities;  // Store all entities for collision detection

public:
    void addEntity(EntityMesh* entity);
    void removeEntity(EntityMesh* entity);
    std::vector<EntityMesh*> getEntitiesInScene();  // Function to retrieve all entities

    // Other methods for collision detection and management
};