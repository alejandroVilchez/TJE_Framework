#pragma once

#include "graphics/texture.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"

class Stages {
public:
    enum Stage { INTRO, PLAY, END };

    Stages();
    ~Stages();

    Stage currentStage;

    void render();
    void update(float elapsed_time);
    void setStage(Stage stage);

private:
    Texture* introBackground;
    Mesh* fullScreenQuad;
    Shader* shader;
};