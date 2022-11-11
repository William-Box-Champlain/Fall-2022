#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

struct cameraTwo
{
	glm::vec3 mPosition = glm::vec3(0, 0, 0);
	glm::vec3 mForward;
	glm::vec3 mRight;
	glm::vec3 mUp;

	//mYaw and mPitch are in degrees
	float mYaw;
	float mPitch;


};