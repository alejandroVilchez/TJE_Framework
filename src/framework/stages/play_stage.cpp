
#include "play_stage.h"


PlayStage::PlayStage(){
    //load map
    //load player
}

stage_ID PlayStage::getID(){
    return stage_ID::PLAY;
}

 void PlayStage::renderMinimap(){
//    glClear(GL_DEPTH_BUFFER_BIT);

//    int width = Game::instance->window_width;
//    int height = Game::instance->window_height;

//    int size = 250;
//    int margin = 40;

//    glViewport(width - size - margin, height - size - margin, size, size);

//    World* world = World::get_instance();

//    float camera_yaw = world->camera_yaw;

//    Camera cam;
//    cam.setPerspective (60.f, 1.f, 0.1f, 100.f);

//    //Matrix44 mYaw;
//    //mYaw.setRotation(camera_yaw, Vector3(0,1,0));
//    Entity* current_player = world->player;


//    Vector3 eye = current_player->model.getTranslation();
//    Vector3 eye.y = 0;
//    Vector3 center = yaw;
//    Vector3 up(0,0,1);

//    cam.lookAt(eye+Vector3(0,15,0), center, up);

//    cam.enable();

//    World::get_instance()->root.render(&cam);

//    glViewport(0,0,width,height);

}