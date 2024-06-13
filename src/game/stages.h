#pragma once

#include "graphics/texture.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "game.h"

enum class StageType {
    INTRO,
    PLAY,
    END
};

class IntroStage;
class PlayStage;

class Stages {
public:
    Stages();
    ~Stages();

    virtual void render();
    virtual void update(float elapsed_time);
    void setStage(StageType stage);
    Stages* currentStage;

private:
    StageType currentStageType;

    IntroStage* introStage;
    PlayStage* playStage;
    //EndStage* endStage;
    bool end;

};

class IntroStage : public Stages {
public:
    IntroStage();
    ~IntroStage();

    void render() override;
    void update(float elapsed_time) override;

private:
    Texture* introBackground;
    Mesh* fullScreenQuad;
    Shader* shader;
};

class PlayStage : public Stages {
public:
    PlayStage();
    ~PlayStage();

    void render() override;
    void update(float elapsed_time) override;
};

class EndStage : public Stages {
public:
    EndStage();
    ~EndStage();

    void render() override;
    void update(float elapsed_time) override;
};
