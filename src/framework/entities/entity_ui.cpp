// #include "entity_ui.h"

// EntityUI::EntityUI(){
//     //windowwidth
//     //windowheight = game::instance->windowheight;

//     //camera = new camera()
//     // camera->lookAt(Vector(0.f,1.f,1.f), Vector(0.f,0.f,0.f), Vector(1.f,0.f,1.f));


    
// };

// void EntityUI::render(Camera* camera2d){
//     if(!3d){
//         glDisable(GL_DEPTH_TEST);
//     }

//     glDisable(GL_CULL_FACE);

//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
//     //copiar y pegar render de entitymesh
//     // Enable shader and pass uniforms 
// 	material.shader->enable();

//     //World* world = World::get_instance();
     

// 	material.shader->setUniform("u_model", model);
// 	material.shader->setUniform("u_viewprojection", viewProj);
// 	material.shader->setUniform("u_color", material.color));
//  material.shader->setUniform("u_mask", mask));
    


// 	if (material.diffuse) {
// 		material.shader->setTexture("u_texture", material.diffuse, 0);
// 	}


// };