//#include "Camera.h"
//#include <glm/ext/matrix_transform.hpp>
//#include <glm/ext/matrix_clip_space.hpp>
//
//Camera::Camera()
//{
//	position = { 0, 0, 0 };
//	theta = 0;
//	phi = 0;
//}
//
//Camera::Camera(glm::vec3 position, glm::vec2 rotation)
//{
//	this->position = position;
//	theta = rotation.x;
//	phi = rotation.y;
//}

//glm::mat4 Camera::GetViewMatrix()
//{
//	float thetaR = glm::radians(theta);
//	float phiR = glm::radians(phi);
//	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
//	return glm::lookAt(position, position + forward, glm::vec3(0, 1, 0));
//}
//
//glm::mat4 Camera::GetProjectionMatrix(float w, float h)
//{
//	return glm::perspective(glm::pi<float>() * 0.25f, w / h, 0.1f, 1000.0f);
//}

//void Camera::Move(glm::vec3 movement)
//{
//	float thetaR = glm::radians(theta);
//	float phiR = glm::radians(phi);
//
//	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
//	glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
//	glm::vec3 up(0, 1, 0);
//
//	position += forward * movement.z + up * movement.y + right * movement.x;
//}

//void Camera::Rotate(glm::vec2 rotate)
//{
//	theta += rotate.x;
//	phi -= rotate.y;
//}