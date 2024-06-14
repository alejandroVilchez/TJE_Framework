#include "entity_mesh.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "framework/camera.h"
#include "graphics/material.h"


EntityMesh::EntityMesh(Mesh* mesh, const Material& material, const std::string& name) {
	this->mesh = mesh;
	this->material = material;
	this->name = name;
};
void EntityMesh::render(Camera* camera) {

	// Get the last camera that was activated 
	camera = Camera::current;

	if (material.shader == nullptr) {
		material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	}

	// Enable shader and pass uniforms 
	material.shader->enable();
	material.shader->setUniform("u_model", model);
	material.shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
	material.shader->setUniform("u_color", Vector4(1, 1, 1, 1));

	if (material.diffuse) {
		material.shader->setTexture("u_texture", material.diffuse, 0);
	}


	material.shader->setUniform("u_model", getGlobalMatrix());

	// Render the mesh using the shader
	mesh->render(GL_TRIANGLES);

	// Disable shader after finishing rendering
	material.shader->disable();

	Entity::render(camera);
};

void EntityMesh::update(float delta_time) {
	for (size_t i = 0; i < children.size(); ++i) {
		children[i]->update(delta_time);
	}
}

bool EntityMesh::checkCollision(EntityMesh* a, EntityMesh* b) {
    if (!a || !b || !a->mesh || !b->mesh)
        return false;

    // Ensure collision models are initialized
    if (!a->mesh->collision_model) {
        if (!a->mesh->createCollisionModel())
            return false;
    }
    if (!b->mesh->collision_model) {
        if (!b->mesh->createCollisionModel())
            return false;
    }

    // Prepare the transformation matrices
    Matrix44 aModel = a->getGlobalMatrix();
    Vector3 aScale = aModel.getScaleVector(); // Get the scale components

    Matrix44 bModel = b->getGlobalMatrix();
    Vector3 bScale = bModel.getScaleVector(); // Get the scale components

    aModel.setScale(aScale.x, aScale.y, aScale.z); // Set the scale components
    bModel.setScale(bScale.x, bScale.y, bScale.z); // Set the scale components

    // Cast collision models to CollisionModel3D
    CollisionModel3D* aCollisionModel = static_cast<CollisionModel3D*>(a->mesh->collision_model);
    CollisionModel3D* bCollisionModel = static_cast<CollisionModel3D*>(b->mesh->collision_model);

    // Set the transformation matrices to the collision models
    aCollisionModel->setTransform(aModel.m);
    bCollisionModel->setTransform(bModel.m);

    // Check for collision
    bool collision = aCollisionModel->collision(bCollisionModel);
    return collision;
}