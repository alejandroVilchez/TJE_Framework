#pragma once

#include "graphics/texture.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "game.h"
#include "framework/audio.h"

enum class StageTypes {
    INTRO,
    PLAY,
    HOWTO,
    END
};

class IntroStage;
class PlayStage;
class HowToStage;

class Stages {
public:
    Stages();
    ~Stages();

    virtual void render();
    virtual void update(float elapsed_time);
    Stages* currentStage;
    Matrix44 model;
    int width;
    int height;
    Camera* camera2D;
    Mesh* fullScreenQuad;
    Shader* shader;
    Texture* howtoBackground1;
    Texture* howtoBackground2;
    Texture* introBackground;
    HCHANNEL channel1;
    HCHANNEL channel2;

private:
    StageType currentStageType;

    IntroStage* introStage;
    PlayStage* playStage;
    HowToStage* howToStage;
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
    float th;
    int currentSlot;
    bool howto;
    bool start;
};

class PlayStage : public Stages {
public:
    PlayStage();
    ~PlayStage();

    void render() override;
    void update(float elapsed_time) override;
};

class HowToStage : public Stages {
public:
    HowToStage();
    ~HowToStage();

    void render() override;
    void update(float elapsed_time) override;

private:
    float blinkTime;
    bool firstTexture;
};

class EndStage : public Stages {
public:
    EndStage();
    ~EndStage();

    void render() override;
    void update(float elapsed_time) override;
};
