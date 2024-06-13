#include "stages.h"

//IntroStage* introStage;
//PlayStage* playStage;
//EndStage* endStage;


Stages::Stages() {
    //introStage = new IntroStage();
    //playStage = new PlayStage();
    ////endStage = new EndStage();
    //setStage(StageType::PLAY);
    end = false;
}

Stages::~Stages() {
    //delete introStage;
    //delete playStage;
    ////delete endStage;
    //delete currentStage;
}

void Stages::render() {
    //currentStage->render();
}

void Stages::update(float elapsed_time) {
    //currentStage->update(elapsed_time);
}

void Stages::setStage(StageType stage) {
    currentStageType = stage;

    switch (stage) {
    case StageType::INTRO:
        currentStage = introStage;
        break;
    case StageType::PLAY:
        currentStage = playStage;
        break;
    /*case StageType::END:
        currentStage = endStage;
        break;*/
    }
}

PlayStage::PlayStage() {
    // Initialize any necessary resources for the play stage
}

PlayStage::~PlayStage() {
    // Clean up resources
}

void PlayStage::render() {
    Game::instance->world->render();
    drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);
}

void PlayStage::update(float elapsed_time) {
    Game::instance->world->update(elapsed_time);
}

EndStage::EndStage() {
    // Initialize any necessary resources for the end stage
}

EndStage::~EndStage() {
    // Clean up resources
}

void EndStage::render() {
    // Render the end stage
}

void EndStage::update(float elapsed_time) {
    // No update needed for the end stage
}

IntroStage::IntroStage() {
    introBackground = Texture::Get("data/textures/a.t.o.m.3.tga");
    fullScreenQuad = Mesh::Get("data/meshes/quad.obj");
    shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
}

IntroStage::~IntroStage() {
    delete introBackground;
}

void IntroStage::render() {
    introBackground = Texture::Get("data/textures/a.t.o.m.2.tga");
    fullScreenQuad = Mesh::Get("data/meshes/quad.obj");
    shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
    shader->enable();
    shader->setUniform("u_texture", introBackground, 0);
    fullScreenQuad->render(GL_TRIANGLES);
    shader->disable();
    drawText(2, 2, "press SPACE to continue", Vector3(1, 1, 1), 2);
}

void IntroStage::update(float elapsed_time) {
    // No update needed for the intro stage
}