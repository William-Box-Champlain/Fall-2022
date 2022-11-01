#pragma once
#include "Transformations.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class camera
{
public:

	camera();
	camera(float yaw, float pitch, glm::vec3 worldUp);

	void setForwardRightUp(float yaw, float pitch, glm::vec3 worldUp); //yaw and pitch are in radians
	
	float getYaw();
	float getPitch();

	void addYaw(float yaw);
	void addPitch(float pitch);

	void update(glm::vec2 cursorPosition);

private:

	transform mPosition;

	glm::vec3 mCamForward;
	glm::vec3 mCamRight;
	glm::vec3 mCamUp;

	float mYaw;
	float mPitch;

	float clampValue(float min, float max, float value);

	glm::vec3 getForward(float yaw, float pitch);
	glm::vec3 getRight(glm::vec3 camForward, glm::vec3 worldUp);
	glm::vec3 getUp(glm::vec3 camRight, glm::vec3 camForward);
};