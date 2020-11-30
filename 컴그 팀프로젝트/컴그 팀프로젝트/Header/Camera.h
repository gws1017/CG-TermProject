#pragma once
#include "Header/header.h"

class Camera {

public:
	float CamPosX = 0.0f;
	float CamPosY = 23.0f;
	float CamPosZ = 23.5f;

	float CamXAt = 0.0f;
	float CamYAt = 0.5f;
	float CamZAt = -1.0f;

	float cam_rotate = 0.0;
	float cam_revolve = 0.0;
	float cam_tvec = 0.05;

	

	glm::mat4 cameraRotate = glm::mat4(1.0f);
	glm::mat4 cameraRevolve = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);


	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraPos = glm::vec3(CamPosX, CamPosY, CamPosZ);
	glm::vec3 cameraDirection = glm::vec3(CamXAt, CamYAt, CamZAt);
	

	void Init();
	void Update(unsigned int viewLocation);
	void make_pot_cam();
	void make_Overview();
};
