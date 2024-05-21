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

	// Methods overwritten from base class
	void render(Camera* camera) override;
	void update(float elapsed_time) override;
};
