#include "camera.h"
camera::camera()
{
	mSensitivity = 1.0;
	mYaw = 0.0;
	mPitch = 0.0;
	mOldMousePosition = glm::vec2(0, 0);
	mCamPos = glm::vec3(0, 0, 0);
	mCamForward = glm::vec3(0.0);
	mCamRight = glm::vec3(0.0);
	mCamUp = glm::vec3(0.0);
}

camera::camera(glm::vec3 startingPosition, float sensitivity, float yaw, float pitch, glm::vec3 worldUp) //yaw and pitch are in radians
{
	mSensitivity = sensitivity;
	mYaw = yaw;
	mPitch = pitch;
	mOldMousePosition = glm::vec2(0, 0);
	mCamPos = startingPosition;
	setForwardRightUp(yaw, pitch, worldUp);
}

void camera::setForwardRightUp(float yaw, float pitch, glm::vec3 worldUp) //yaw and pitch are in radians
{
	mCamForward = getForward(yaw, pitch);
	mCamRight = getRight(mCamForward, worldUp);
	mCamUp = getUp(mCamRight, mCamForward);
}

float camera::getYaw()
{
	return mYaw;
}

float camera::getPitch()
{
	return mPitch;
}

void camera::addYaw(float yaw)
{
	mYaw += yaw;
}

void camera::addPitch(float pitch)
{
	mPitch += pitch;
}

void camera::update(glm::vec2 cursorPosition)
{
	glm::vec2 mousePosDelta = cursorPosition - mOldMousePosition;
	addYaw(mousePosDelta.x);
	addPitch(-1 * mousePosDelta.y);
	getForward(mYaw, mPitch);
}

glm::vec3 camera::getCameraPosition()
{
	return mCamPos;
}

glm::vec3 camera::getTargetPosition()
{
	return mCamPos + mCamForward;
}

float camera::clampValue(float min, float max, float value)
{
	if (value < min)return min;
	else if (value > max)return max;
	else return value;
}

glm::vec3 camera::getForward(float yaw, float pitch) //yaw and pitch are in radians
{
	glm::vec3 camForward;
	float localYaw;
	float localPitch;

	float min = -glm::pi<float>() / 2;
	float max = glm::pi<float>() / 2;


	localYaw = yaw;
	localPitch = clampValue(min, max, pitch);


	camForward.x = glm::cos(localYaw) * glm::cos(localPitch);
	camForward.y = glm::sin(localPitch);
	camForward.z = glm::sin(localYaw) * glm::cos(localPitch);

	camForward = glm::normalize(camForward);

	return camForward;
}

glm::vec3 camera::getRight(glm::vec3 camForward, glm::vec3 worldUp)
{
	return glm::normalize(glm::cross(camForward, worldUp));
}

glm::vec3 camera::getUp(glm::vec3 camRight, glm::vec3 camForward)
{
	return glm::normalize(glm::cross(camRight, camForward));
}