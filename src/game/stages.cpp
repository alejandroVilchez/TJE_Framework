#include "stages.h"

Stages::Stages() {
    camera2D = new Camera();
    camera2D->view_matrix.setIdentity();
    camera2D->setOrthographic(0, Game::instance->window_width, Game::instance->window_height, 0, -1, 1);

    // Load texture
    introBackground = Texture::Get("data/textures/atom7.tga");
    howtoBackground1 = Texture::Get("data/textures/howto.tga");
    howtoBackground2 = Texture::Get("data/textures/b2atom.tga");
    howtoBackground3 = Texture::Get("data/textures/How2Camera.tga");
    badEnd = Texture::Get("data/textures/GAME-OVER.tga");
    goodEnd = Texture::Get("data/textures/YOUWIN.tga");
    creditsBackground = Texture::Get("data/textures/atom7.tga");



    // Load shader
    shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

    width = Game::instance->window_width;
    height = Game::instance->window_height;

    model.setIdentity();
    model.translate(width / 2, height / 2, 0);
    model.scale(width, height, 1.f);
}

Stages::~Stages() {
    delete introStage;
    delete playStage;
    delete howToStage;
    //delete GoodEndStage;
    delete currentStage;
    delete camera2D;
}

void Stages::render() {
    //currentStage->render();
}

void Stages::update(float elapsed_time) {
    //currentStage->update(elapsed_time);
}


// ------ Play Stage ------


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


// ------ Credits Stage ------


CreditsStage::CreditsStage() {
    // Initialize any necessary resources for the credits stage
}

CreditsStage::~CreditsStage() {
    // Clean up resources
}

void CreditsStage::render() {

}

void CreditsStage::update(float elapsed_time) {
}


// ------ Good End Stage ------


GoodEndStage::GoodEndStage() {
    // Initialize any necessary resources for the end stage
        // Initialize other variables
    goodEndSlot = 0;
    credits = false;
    intro = false;
}

GoodEndStage::~GoodEndStage() {
    // Clean up resources
}

void GoodEndStage::render() {
    // Render the end stage
            // Set the clear color (the background color)
    glClearColor(0.f, 0.f, 0.f, 1.0f);

    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera2D->enable();

    // Set flags
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    shader->enable();
    shader->setUniform("u_color", Vector4(1, 1, 1, 1));
    shader->setUniform("u_viewprojection", camera2D->viewprojection_matrix);
    shader->setUniform("u_texture", goodEnd, 1);

    shader->setUniform("u_model", model);
    shader->setUniform("u_time", Game::instance->time);

    Game::instance->fullScreenQuad->render(GL_TRIANGLES);

    shader->disable();

    float blinkTime = sin(Game::instance->time * 5.0f); // Speed of blinking
    bool isLargeFont = blinkTime > 0;

    int creditsFontSize = isLargeFont ? 5 : 4; // Change font when blinking
    int introFontSize = isLargeFont ? 5 : 4;

    int creditsXOffset = isLargeFont ? 0 : 25;
    int introXOffset = isLargeFont ? 0 : 25;

    /*drawText(width / 2 - 120, height / 2 - 275, "A.T.O.M.", Vector3(1, 1, 1), 7);
    drawText(width / 2 - 330, height / 2 - 175, "Aeronautic Thermonuclear Ogives Maelstrom", Vector3(1, 1, 1), 3);*/

    if (goodEndSlot == 0) {
        drawText((width / 2 - 135) + creditsXOffset, height / 2 + 240, "See Credits", Vector3(1, 0, 0), creditsFontSize);
    }
    else {
        drawText(width / 2 - 135, height / 2 + 240, "See Credits", Vector3(1, 1, 1), 5);
    }

    if (goodEndSlot == 1) {
        drawText((width / 2 - 180) + introXOffset, height / 2 + 180, "Return to Menu", Vector3(1, 0, 0), introFontSize);
    }
    else {
        drawText(width / 2 - 180, height / 2 + 180, "Return to Menu", Vector3(1, 1, 1), 5);
    }

}

void GoodEndStage::update(float elapsed_time) {
    // No update needed for the end stage
    if (goodEndSlot > 1)
        goodEndSlot = 0;
    if (goodEndSlot < 0)
        goodEndSlot = 1;

    if (goodEndSlot == 0 && (Input::wasKeyPressed(SDL_SCANCODE_RETURN) || Input::wasButtonPressed(A_BUTTON))) {
        Game::instance->changeStage(StageType::CREDITS);
        Audio::Play("data/audio/select.wav");
        //Audio::Stop(channel1);
        //channel2 = Audio::Play("data/audio/bombersound.mp3", 1, BASS_SAMPLE_LOOP);
    }
    if (goodEndSlot == 1 && (Input::wasKeyPressed(SDL_SCANCODE_RETURN) || Input::wasButtonPressed(A_BUTTON))) {
        Game::instance->changeStage(StageType::INTRO);
        Audio::Play("data/audio/select.wav");
    }

    if (Input::wasKeyPressed(SDL_SCANCODE_DOWN) || Input::wasKeyPressed(SDL_SCANCODE_S) || Input::wasButtonPressed(PAD_DOWN)) {
        goodEndSlot = (goodEndSlot + 1) % 2;
        Audio::Play("data/audio/change.wav");
    }
    if (Input::wasKeyPressed(SDL_SCANCODE_UP) || Input::wasKeyPressed(SDL_SCANCODE_W) || Input::wasButtonPressed(PAD_UP)) {
        goodEndSlot = (goodEndSlot - 1) % 2;
        Audio::Play("data/audio/change.wav");
    }

}

// ------ Bad End Stage ------


BadEndStage::BadEndStage() {
    // Initialize any necessary resources for the end stage
        // Initialize other variables
    badEndSlot = 0;
    credits = false;
    intro = false;
}

BadEndStage::~BadEndStage() {
    // Clean up resources
}

void BadEndStage::render() {
    // Render the end stage
            // Set the clear color (the background color)
    glClearColor(0.f, 0.f, 0.f, 1.0f);

    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera2D->enable();

    // Set flags
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    shader->enable();
    shader->setUniform("u_color", Vector4(1, 1, 1, 1));
    shader->setUniform("u_viewprojection", camera2D->viewprojection_matrix);
    shader->setUniform("u_texture", badEnd, 1);

    shader->setUniform("u_model", model);
    shader->setUniform("u_time", Game::instance->time);

    Game::instance->fullScreenQuad->render(GL_TRIANGLES);

    shader->disable();

    float blinkTime = sin(Game::instance->time * 5.0f); // Speed of blinking
    bool isLargeFont = blinkTime > 0;

    int creditsFontSize = isLargeFont ? 5 : 4; // Change font when blinking
    int introFontSize = isLargeFont ? 5 : 4;

    int creditsXOffset = isLargeFont ? 0 : 25;
    int introXOffset = isLargeFont ? 0 : 25;

    /*drawText(width / 2 - 120, height / 2 - 275, "A.T.O.M.", Vector3(1, 1, 1), 7);
    drawText(width / 2 - 330, height / 2 - 175, "Aeronautic Thermonuclear Ogives Maelstrom", Vector3(1, 1, 1), 3);*/

    if (badEndSlot == 0) {
        drawText((width / 2 - 135) + creditsXOffset, height / 2 + 240, "See Credits", Vector3(1, 0, 0), creditsFontSize);
    }
    else {
        drawText(width / 2 - 135, height / 2 + 240, "See Credits", Vector3(1, 1, 1), 5);
    }

    if (badEndSlot == 1) {
        drawText((width / 2 - 180) + introXOffset, height / 2 + 180, "Return to Menu", Vector3(1, 0, 0), introFontSize);
    }
    else {
        drawText(width / 2 - 180, height / 2 + 180, "Return to Menu", Vector3(1, 1, 1), 5);
    }

}

void BadEndStage::update(float elapsed_time) {
    // No update needed for the end stage
    if (badEndSlot > 1)
        badEndSlot = 0;
    if (badEndSlot < 0)
        badEndSlot = 1;

    if (badEndSlot == 0 && (Input::wasKeyPressed(SDL_SCANCODE_RETURN) || Input::wasButtonPressed(A_BUTTON))) {
        Game::instance->changeStage(StageType::CREDITS);
        Audio::Play("data/audio/select.wav");
        //Audio::Stop(channel1);
        //channel2 = Audio::Play("data/audio/bombersound.mp3", 1, BASS_SAMPLE_LOOP);
    }
    if (badEndSlot == 1 && (Input::wasKeyPressed(SDL_SCANCODE_RETURN) || Input::wasButtonPressed(A_BUTTON))) {
        Game::instance->changeStage(StageType::INTRO);
        Audio::Play("data/audio/select.wav");
    }

    if (Input::wasKeyPressed(SDL_SCANCODE_DOWN) || Input::wasKeyPressed(SDL_SCANCODE_S) || Input::wasButtonPressed(PAD_DOWN)) {
        badEndSlot = (badEndSlot + 1) % 2;
        Audio::Play("data/audio/change.wav");
    }
    if (Input::wasKeyPressed(SDL_SCANCODE_UP) || Input::wasKeyPressed(SDL_SCANCODE_W) || Input::wasButtonPressed(PAD_UP)) {
        badEndSlot = (badEndSlot - 1) % 2;
        Audio::Play("data/audio/change.wav");
    }

}


// ------ Intro Stage ------


IntroStage::IntroStage() {

    // Initialize other variables
    currentSlot = 0;
    th = 1.0f;
    start = false;
    end = false;
    channel1 = Audio::Play("data/audio/music.mp3",1, BASS_SAMPLE_LOOP);
}

IntroStage::~IntroStage() {
    delete camera2D;
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

        shader->enable();
        shader->setUniform("u_color", Vector4(1, 1, 1, 1));
        shader->setUniform("u_viewprojection", camera2D->viewprojection_matrix);
        shader->setUniform("u_texture", introBackground, 1);
        shader->setUniform("u_model", model);
        shader->setUniform("u_time", Game::instance->time);

        Game::instance->fullScreenQuad->render(GL_TRIANGLES);

        shader->disable();

        float blinkTime = sin(Game::instance->time * 5.0f); // Speed of blinking
        bool isLargeFont = blinkTime > 0;

        int startGameFontSize = isLargeFont ? 5 : 4; // Change font when blinking
        int howToPlayFontSize = isLargeFont ? 5 : 4; 
        int endScreenFontSize = isLargeFont ? 5 : 4;

        int startGameXOffset = isLargeFont ? 0 : 27; 
        int howToPlayXOffset = isLargeFont ? 0 : 25; 
        int endScreenXOffset = isLargeFont ? 0 : 10;

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
        if (currentSlot == 2) {
            drawText((width / 2 - 40) + endScreenXOffset, height / 2 + 220, "Exit", Vector3(1, 0, 0), endScreenFontSize);
        }
        else {
            drawText(width / 2 - 40, height / 2 + 220, "Exit", Vector3(1, 1, 1), 5);
        }

}


void IntroStage::update(float elapsed_time) {
    if (currentSlot > 2)
        currentSlot = 0;
    if (currentSlot < 0)
        currentSlot = 2;

    if (currentSlot == 0 && (Input::wasKeyPressed(SDL_SCANCODE_RETURN) || Input::wasButtonPressed(A_BUTTON))) {
        Game::instance->changeStage(StageType::PLAY);
        Audio::Play("data/audio/select.wav");
        Audio::Stop(channel1);
    }
    if (currentSlot == 1 && (Input::wasKeyPressed(SDL_SCANCODE_RETURN) || Input::wasButtonPressed(A_BUTTON))) {
        Game::instance->changeStage(StageType::HOWTO);
        Audio::Play("data/audio/select.wav");
    }    
    if (currentSlot == 2 && (Input::wasKeyPressed(SDL_SCANCODE_RETURN) || Input::wasButtonPressed(A_BUTTON))) {
        Game::instance->changeStage(StageType::BADEND);
        Audio::Play("data/audio/select.wav");
    }

    if (Input::wasKeyPressed(SDL_SCANCODE_DOWN) || Input::wasKeyPressed(SDL_SCANCODE_S) || Input::wasButtonPressed(PAD_DOWN)) {
        currentSlot = (currentSlot + 1) % 3;
        Audio::Play("data/audio/change.wav");
    }
    if (Input::wasKeyPressed(SDL_SCANCODE_UP) || Input::wasKeyPressed(SDL_SCANCODE_W) || Input::wasButtonPressed(PAD_UP)) {
        currentSlot = (currentSlot - 1) % 3;
        Audio::Play("data/audio/change.wav");
    }
}


// ------ HowTo Stage ------


HowToStage::HowToStage() {
    blinkTime = 0.0f;
}

HowToStage::~HowToStage() {
}

void HowToStage::render() {
    // Set the clear color (the background color)
    glClearColor(0.f, 0.f, 0.f, 1.0f);

    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera2D->enable();

    // Set flags
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    shader->enable();
    shader->setUniform("u_color", Vector4(1, 1, 1, 1));
    if (howTo == 0) {
        shader->setUniform("u_texture", howtoBackground1, 1);
    }
    else if(howTo == 1) {
        shader->setUniform("u_texture", howtoBackground2, 1);
    }
    else {
        shader->setUniform("u_texture", howtoBackground3, 1);
    }
    shader->setUniform("u_model", model);
    shader->setUniform("u_time", Game::instance->time);

    Game::instance->fullScreenQuad->render(GL_TRIANGLES);

    shader->disable();

    float blink = sin(blinkTime * 5.0f); // Speed of blinking
    bool isLargeFont = blink > 0;
    int fontSize = isLargeFont ? 5 : 4;
    int continueXOffset = isLargeFont ? 0 : 50;

    drawText((width / 2 - 300) + continueXOffset, height / 2 - 250, "Press SPACE to Continue", Vector3(1, 1, 1), fontSize);
}

void HowToStage::update(float elapsed_time) {
    blinkTime += elapsed_time;

    if (Input::wasKeyPressed(SDL_SCANCODE_SPACE)) {
        howTo += 1;
        if (howTo >= 3){ 
            Game::instance->changeStage(StageType::INTRO);  // Go back to the intro stage
            Audio::Play("data/audio/change.wav");
            howTo = 0;
        }
    }
}
