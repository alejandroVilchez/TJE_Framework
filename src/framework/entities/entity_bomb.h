#include <vector>
#include "framework/input.h"
#include <cmath>
#include "framework/includes.h"
#include "framework/camera.h"
#include "framework/entities/entity_mesh.h"


class EntityBomb : public EntityMesh {
public:
    Vector3 position;
    Vector3 velocity;
    float explosionTime;
    bool exploded;

    EntityBomb(Vector3 initialPosition, Vector3 initialVelocity);
    void update(float deltaTime);
};
