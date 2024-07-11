#pragma once

#include "framework/entities/entity.h"
#include "framework/entities/entity_player.h"
#include "framework/entities/entity_mesh.h"
#include "framework/entities/entity_bomb.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "graphics/shader.h"
#include "scene.h"
#include <string>
#include <stdio.h>
#include <iomanip>  // Para std::setprecision
#include <sstream>  // Para std::ostringstream


//#endif /* world_h */

//Entity* root;

class World {
public:
    static World* instance;

    World(int window_width, int window_height);
    int world_window_width;
    int world_window_height;


    Matrix44 model;
    Entity* root = nullptr;

    Mesh* playerMesh;
    Mesh* projectileMesh = nullptr;
    Mesh* powerUpMesh = nullptr;

    Texture* texture = nullptr; //loas textures
    Texture* playerTexture = nullptr;
    Shader* basicShader;
    Material playerMaterial;

    Scene* scene;
    Camera* camera;

    bool badEnding = false;
    bool goodEnding = false;
    float timerScene = 2.0f;

    EntityPlayer* playerEntity;
    Vector3 playerPosition;
    std::string playerHeight;
    float gameTimer;
    float timerScene2;
    float missileTimer = 100.;
    int radarTimer;
    bool missilelost;

    bool detected = false;
    bool planecrashed = false;

    EntityMesh* bombEntity;
    Mesh* bombMesh;
    Material bombMaterial;
    Texture* bombTexture;

    EntityMesh* nuclearEntity;
    Mesh* nuclearMesh;
    Material nuclearMaterial;
    Texture* nuclearTexture;

    EntityMesh* failEntity;
    Mesh* failMesh;
    Material failMaterial;
    Texture* failTexture;

    HCHANNEL alarm;
    HCHANNEL planeexp;

    std::string messageText;
    std::string radarInfo2;
    std::string loseText2;
    std::string loseText3;
    std::string radarInfo;

    Camera* camera2D;
    Camera camera2D2;

    //Mesh* quad;

    Material cubemap;
    Material skyboxMaterial;
    EntityMesh* skybox;
    void render();
    void update(float elapsed_time);
    void cleanRoot();
    void onKeyDown(SDL_KeyboardEvent event);
    Mesh* createFullscreenQuad(int window_width, int window_height);
    void startTransition();
    void renderTransition();
    void resetGame();
    Vector2 worldToScreen(const Vector3& worldPos, Camera* cam);
    void drawHUDMarker(const Vector2& screenPos);


    EntityCollider collider;
};
