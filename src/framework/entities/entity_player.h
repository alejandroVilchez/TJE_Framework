#include "entity.h"
#include "entity_mesh.h"
#include <vector>
#include "framework/input.h"
#include <cmath>
#include "framework/includes.h"
#include "framework/camera.h"

//class Bomb : public Entity {
//public:
//    Bomb(Vector3 position, Vector3 velocity);
//    void update(float deltaTime);
//    // Otras funciones necesarias para la clase Bomb
//};

class EntityPlayer : public EntityMesh {
public:
    Vector3 position;
    EntityPlayer(Vector3 position);
    void update(float seconds_elapsed, EntityMesh* skybox);
    void handleInput(float seconds_elapsed, EntityMesh* skybox);
    void playerPOV(Camera* camera, float seconds_elapsed);
    void dropBomb();

private:
    //std::vector<Bomb> bombs;
    float speed = 5.0f;
    float rotation_speed = 2.0f;
    /*float camera_yaw = 0.0f;
    float camera_pitch = 0.0f;*/
};

