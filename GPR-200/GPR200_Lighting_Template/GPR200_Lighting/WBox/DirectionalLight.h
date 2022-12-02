#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct DirectionalLight
{
	glm::vec3 mDirection;

	glm::vec3 mLightColor;

	float ambientK;
	float diffuseK;
	float specularK;
};