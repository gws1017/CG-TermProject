#include "Header/Camera.h"

void Camera::Init()
{
	cameraRotate = glm::rotate(cameraRotate, (float)glm::radians(cam_rotate), glm::vec3(0.0f, 1.0f, 0.0f));
	cameraRevolve = glm::rotate(cameraRevolve, (float)glm::radians(cam_revolve), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::Update(unsigned int viewLocation)
{
	cameraRotate = glm::mat4(1.0f);
	cameraRevolve = glm::mat4(1.0f);
	cameraRotate = glm::rotate(cameraRotate, (float)glm::radians(cam_rotate), glm::vec3(0.0f, 1.0f, 0.0f));
	cameraRevolve = glm::rotate(cameraRevolve, (float)glm::radians(cam_revolve), glm::vec3(0.0f, 1.0f, 0.0f));
	cameraPos = glm::vec3(CamPosX, CamPosY, CamPosZ);
	cameraDirection = glm::vec3(CamXAt, CamYAt, CamZAt);
	view = cameraRotate * lookAt(cameraPos, cameraDirection, cameraUp) * cameraRevolve;
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
}

void Camera::make_pot_cam()
{
	if (CamYAt < 0)
	{
		CamYAt += cam_tvec;
		if (CamYAt >= -3.0f)
		{
			CamYAt = -3.0f;
		}
	}
	if (CamYAt >= 0)
	{
		CamYAt -= cam_tvec;
		if (CamYAt <= -3.0f)
		{
			CamYAt = -3.0f;
		}
	}

	if (CamZAt < 0)
	{
		CamZAt += cam_tvec;
		if (CamZAt >= -3.0f)
		{
			CamZAt = -3.0f;
		}
	}
	if (CamZAt >= 0)
	{
		CamZAt -= cam_tvec;
		if (CamZAt <= -3.0f)
		{
			CamZAt = -3.0f;
		}
	}

	if (CamPosY < 0)
	{
		CamPosY += cam_tvec;
		if (CamPosY >= 9.0f)
		{
			CamPosY = 9.0f;
		}
	}
	if (CamPosY >= 0)
	{
		CamPosY -= cam_tvec;
		if (CamPosY <= 9.0f)
		{
			CamPosY = 9.0f;
		}
	}
	if (CamPosZ < 0)
	{
		CamPosZ += cam_tvec;
		if (CamPosZ >= 6.0f)
		{
			CamPosZ = 6.0f;
		}
	}
	if (CamPosZ >= 0)
	{
		CamPosZ -= cam_tvec;
		if (CamPosZ <= 6.0f)
		{
			CamPosZ = 6.0f;
		}
	}
}