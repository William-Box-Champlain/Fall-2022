#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

enum class camDirection
{
	forward,
	backwards,
	up,
	down,
	left,
	right,
};

class camera
{
public:

	camera();
	camera(glm::vec3 startingPosition, float sensitivity, float yaw, float pitch, glm::vec3 worldUp);
	
	float getYaw();
	float getPitch();

	void addYaw(float yaw);
	void addPitch(float pitch);

	glm::vec3 getCameraPosition();
	glm::vec3 getTargetPosition();

	void move(camDirection dir, float moveSpeed);
	void point(glm::vec2 cursorPosition, glm::vec3 worldUp);

private:

	glm::vec3 mCamPos;

	glm::vec2 mOldMousePosition;
	float mSensitivity;
	//yaw and pitch are in degrees
	float mYaw;
	float mPitch;

	glm::vec3 mCamForward;
	glm::vec3 mCamRight;
	glm::vec3 mCamUp;

	glm::vec3 mWorldUp;

	float clampValue(float min, float max, float value);

	void setForwardRightUp(float yaw, float pitch, glm::vec3 worldUp); //yaw and pitch are in radians
	glm::vec3 getForward(float yaw, float pitch);
	glm::vec3 getRight(glm::vec3 camForward, glm::vec3 worldUp);
	glm::vec3 getUp(glm::vec3 camRight, glm::vec3 camForward);
};