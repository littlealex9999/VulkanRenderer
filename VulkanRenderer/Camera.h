#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

class Camera
{
private:
	float theta;
	float phi;

public:
	//Camera();
	//Camera(glm::vec3 position, glm::vec2 rotation);
	Camera()
	{
		position = { 0, 0, 0 };
		theta = 0;
		phi = 0;
	}

	Camera(glm::vec3 position, glm::vec2 rotation)
	{
		this->position = position;
		theta = rotation.x;
		phi = rotation.y;
	}

	glm::vec3 position { 0, 0, 0 };

	//glm::mat4 GetViewMatrix();
	//glm::mat4 GetProjectionMatrix(float w, float h);
	glm::mat4 GetViewMatrix()
	{
		float thetaR = glm::radians(theta);
		float phiR = glm::radians(phi);
		glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
		return glm::lookAt(position, position + forward, glm::vec3(0, 1, 0));
	}

	glm::mat4 GetProjectionMatrix(float w, float h)
	{
		return glm::perspective(glm::pi<float>() * 0.25f, w / h, 0.1f, 1000.0f);
	}

	//void Move(glm::vec3 movement);
	void Move(glm::vec3 movement)
	{
		float thetaR = glm::radians(theta);
		float phiR = glm::radians(phi);

		glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
		glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
		glm::vec3 up(0, 1, 0);

		position += forward * movement.z + up * movement.y + right * movement.x;
	}

	//void Rotate(glm::vec2 rotate);
	void Rotate(glm::vec2 rotate)
	{
		theta += rotate.x;
		phi -= rotate.y;
	}
};