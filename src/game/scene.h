#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <string>
#include "sRenderData.h"
#include "framework/entities/entity.h"

class Scene {
public:
    Scene();
    Entity root;
    bool parseScene(const char* filename);
};

#endif // SCENE_H
