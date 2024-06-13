#pragma once

#include "graphics/material.h"
#include "entity.h"
#include "framework/animation.h"



class EntityMesh : public Entity {

public:

	EntityMesh() {};
	EntityMesh(Mesh* mesh, const Material& material, const std::string& name = "");
	//~EntityMesh();

	// Attributes of the derived class  
	Mesh* mesh = nullptr;

	Material material;

	bool isInstanced = false;
	std::vector<Matrix44> models;

	bool isLaunched = false;
	bool isExploded = false;
	float bombSpeed = 5.0f; 
	Vector3 velocity;
	float explosionTime = 5.0f;

	// Methods overwritten from base class
	void render(Camera* camera) override;
	void update(float elapsed_time) override;
};
