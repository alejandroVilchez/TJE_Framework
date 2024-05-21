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

