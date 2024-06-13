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
    camera = new Camera();
    camera->setOrthographic(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, 0.1f, 100.f);
    camera->lookAt(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));


    // Load texture
    introBackground = Texture::Get("data/textures/atom.tga");

    // Load mesh
    fullScreenQuad = Mesh::Get("data/meshes/quad.obj");

    // Load shader
    shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

    // Initialize other variables
    currentSlot = 0;
    th = 1.0f;
    start = false;
    width = Game::instance->window_width;
    height = Game::instance->window_height;
    howto = false;

    model.setIdentity();
    model.scale(width, height, 1.0f);
}

IntroStage::~IntroStage() {
    delete camera;
    delete fullScreenQuad;
    delete introBackground;
    delete shader;
}

void IntroStage::render() {
    // Set the clear color (the background color)
    glClearColor(0.f, 0.f, 0.f, 1.0f);

    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set flags
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    if (shader) {
        shader->enable();
        shader->setUniform("u_color", Vector4(1, 1, 1, 1));
        shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
        shader->setUniform("u_texture", introBackground, 0);
        shader->setUniform("u_model", model);
        shader->setUniform("u_time", Game::instance->time);

        // Render the quad
        fullScreenQuad->render(GL_TRIANGLES);

        // Disable shader
        shader->disable();

        drawText(width / 2 - 120, height / 2 - 275, "A.T.O.M.", Vector3(1, 1, 1), 7);
        drawText(width / 2 - 330, height / 2 - 175, "Aeronautic Thermonuclear Ogives Maelstrom", Vector3(1, 1, 1), 3);
        if (currentSlot == 0)
            drawText(width / 2 - 115, height / 2, "Start Game", Vector3(1, 0, 0), 4);
        else
            drawText(width / 2 - 115, height / 2, "Start Game", Vector3(1, 1, 1), 4);
        if (currentSlot == 1)
            drawText(width / 2 - 120, height / 2 + 50, "How to Play", Vector3(1, 0, 0), 4);
        else
            drawText(width / 2 - 120, height / 2 + 50, "How to Play", Vector3(1, 1, 1), 4);

    }
}

void IntroStage::update(float elapsed_time) {
    if (currentSlot > 1)
        currentSlot = 0;
    if (currentSlot < 0)
        currentSlot = 1;

    if (currentSlot == 0 && (Input::wasKeyPressed(SDL_SCANCODE_RETURN) || Input::wasButtonPressed(A_BUTTON))) {
        start = true;
    }
    if (currentSlot == 1 && (Input::wasKeyPressed(SDL_SCANCODE_RETURN) || Input::wasButtonPressed(A_BUTTON))) {
        howto = true;
    }

    if (Input::wasKeyPressed(SDL_SCANCODE_DOWN) || Input::wasKeyPressed(SDL_SCANCODE_S) || Input::wasButtonPressed(PAD_DOWN)) {
        currentSlot = (currentSlot + 1) % 2;
    }
    if (Input::wasKeyPressed(SDL_SCANCODE_UP) || Input::wasKeyPressed(SDL_SCANCODE_W) || Input::wasButtonPressed(PAD_UP)) {
        currentSlot = (currentSlot + 1) % 2;
    }
}