#include "stages.h"
#include "world.h" // Include the World class

World* world;

Stages::Stages() {
    currentStage = PLAY;
    introBackground = Texture::Get("data/textures/atom.tga");

    // Create a full-screen quad mesh
    fullScreenQuad = Mesh::Get("data/meshes/quad.obj");

    // Load a basic shader for rendering the texture
    shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

    world = new World();
}

Stages::~Stages() {
    delete introBackground;
}

void Stages::render() {
    switch (currentStage) {
    case INTRO:
        // Render the intro background
        shader->enable();
        shader->setUniform("u_texture", introBackground);
        fullScreenQuad->render(GL_TRIANGLES);
        shader->disable();
        break;
    case PLAY:
        // Render the game world
        World::instance->render();
        break;
    case END:
        // Render the end stage
        break;
    }
}

void Stages::update(float elapsed_time) {
    switch (currentStage) {
    case PLAY:
        // Update the game world
        World::instance->update(elapsed_time);
        break;
        // No update needed for INTRO and END stages
    }
}

void Stages::setStage(Stage stage) {
    currentStage = stage;
}