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
    camera2D = new Camera();
    camera2D->view_matrix.setIdentity();
    camera2D->setOrthographic(0, Game::instance->window_width, Game::instance->window_height, 0, -1, 1);

    // Load texture
    introBackground = Texture::Get("data/textures/atom7.tga");

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
    model.translate(width / 2, height / 2, 0);
    model.scale(width, height, 1.f);
}

IntroStage::~IntroStage() {
    delete camera2D;
    delete fullScreenQuad;
    delete introBackground;
    delete shader;
}

void IntroStage::render() {
    // Set the clear color (the background color)
    glClearColor(0.f, 0.f, 0.f, 1.0f);

    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera2D->enable();

    // Set flags
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    if (shader) {
        shader->enable();
        shader->setUniform("u_color", Vector4(1, 1, 1, 1));
        shader->setUniform("u_viewprojection", camera2D->viewprojection_matrix);
        shader->setUniform("u_texture", introBackground, 1);
        shader->setUniform("u_model", model);
        shader->setUniform("u_time", Game::instance->time);

        // Render the quad
        fullScreenQuad->render(GL_TRIANGLES);

        // Disable shader
        shader->disable();

        float blinkTime = sin(Game::instance->time * 5.0f); // Adjust the speed of blinking
        bool isLargeFont = blinkTime > 0;

        int startGameFontSize = isLargeFont ? 5 : 4; // Larger font when blinking
        int howToPlayFontSize = isLargeFont ? 5 : 4; // Larger font when blinking

        int startGameXOffset = isLargeFont ? 0 : 27; // Move text 10 units to the right when smaller
        int howToPlayXOffset = isLargeFont ? 0 : 25; // Move text 10 units to the right when smaller

        /*drawText(width / 2 - 120, height / 2 - 275, "A.T.O.M.", Vector3(1, 1, 1), 7);
        drawText(width / 2 - 330, height / 2 - 175, "Aeronautic Thermonuclear Ogives Maelstrom", Vector3(1, 1, 1), 3);*/

        if (currentSlot == 0) {
            drawText((width / 2 - 130) + startGameXOffset, height / 2 + 100, "Start Game", Vector3(1, 0, 0), startGameFontSize);
        }
        else {
            drawText(width / 2 - 130, height / 2 + 100, "Start Game", Vector3(1, 1, 1), 5);
        }

        if (currentSlot == 1) {
            drawText((width / 2 - 135) + howToPlayXOffset, height / 2 + 160, "How to Play", Vector3(1, 0, 0), howToPlayFontSize);
        }
        else {
            drawText(width / 2 - 135, height / 2 + 160, "How to Play", Vector3(1, 1, 1), 5);
        }
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
