#include "camera.h"
camera::camera()
{
	mPosition = transform();
	mCamForward = glm::vec3(0.0);
	mCamRight = glm::vec3(0.0);
	mCamUp = glm::vec3(0.0);
}

camera::camera(float yaw, float pitch, glm::vec3 worldUp) //yaw and pitch are in radians
{
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

float camera::addYaw(float yaw)
{
	mYaw += yaw;
}

void camera::addPitch(float pitch)
{
	mPitch += pitch
}

void camera::update(glm::vec2 cursorPosition)
{

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


	localYaw = clampValue(min, max, yaw);
	localPitch = clampValue(min, max, pitch);


	camForward.x = glm::cos(localYaw) * glm::sin(localPitch);
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