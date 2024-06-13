#pragma once

#include "graphics/texture.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"

class Stages {
public:
    enum Stage { INTRO, PLAY, END };

    Stages();
    ~Stages();

    void render();
    void update(float elapsed_time);
    void setStage(Stage stage);

private:
    Stage currentStage;
    Texture* introBackground;
    Mesh* fullScreenQuad;
    Shader* shader;
};