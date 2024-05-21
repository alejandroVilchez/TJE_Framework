


// ...

/*
 else {
 	camera_yaw = Input::mouse_delta.x * 0.001;
 	camera_pitch = Input::mouse_delta.y * 0.001;
	camera_pitch = clamp(camera_pitch, -M_PI * 0.5f, M_PI * 0.5f);
 }
 Matrix44 mYaw;
 mYaw.setRotation(camera_yaw, Vector3(0,1,0));
 
 Matrix44 mPitch;
 mPitch.setRotation(camera_pitch, Vector3(-1,0,0));
 
 Matrix44 final_rotation = (mPitch * mYaw);
 Vector3 front = final_rotation.frontVector().normalize();
 Vector3 eye;
 Vector3 center;
 
 float orbit_dist = 0.6f;
 eye = player->model.getTranslation() - front * orbit_dist;
 center = player->model.getTranslation() + Vector3(0.0f, 0.1f, 0.0f);
 
 
 camera->lookAt(eye, center, Vector3(0, 1, 0);
 //update our scene:
 root.update(seconds_elapsed);
 
 player->update(seconds_elapsed);
*/