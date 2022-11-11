#include "camera.h"
camera::camera()
{
	mSensitivity = 1.0;
	mYaw = 0.0;
	mPitch = 0.0;
	mOldMousePosition = glm::vec2(0, 0);
	mCamPos = glm::vec3(0, 0, 0);
	mWorldUp = glm::vec3(0,0,0);
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
	mWorldUp = worldUp;
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

void camera::point(glm::vec2 cursorPosition,glm::vec3 worldUp)
{
	glm::vec2 mousePosDelta = cursorPosition - mOldMousePosition;
	mOldMousePosition = cursorPosition;
	addYaw(-1 * mousePosDelta.x * mSensitivity);
	addPitch(mousePosDelta.y * mSensitivity);
	mCamForward = getForward(mYaw, mPitch);
	mCamRight = getRight(mCamForward, worldUp);
	mCamUp = getUp(mCamRight, mCamForward);
}

glm::vec3 camera::getCameraPosition()
{
	return mCamPos;
}

glm::vec3 camera::getTargetPosition()
{
	return mCamPos + mCamForward;
}

void camera::move(camDirection dir, float moveSpeed)
{
	glm::vec3 localForward = getForward(mYaw, mPitch);
	glm::vec3 localRight = getRight(localForward, mWorldUp);
	glm::vec3 localUp = getUp(localRight, localForward);

	switch (dir)
	{
	case camDirection::forward:
		mCamPos += localForward * moveSpeed;
		break;
	case camDirection::backwards:
		mCamPos -= localForward * moveSpeed;
		break;
	case camDirection::up:
		mCamPos += localUp * moveSpeed;
		break;
	case camDirection::down:
		mCamPos -= localUp * moveSpeed;
		break;
	case camDirection::left:
		mCamPos -= localRight * moveSpeed;
		break;
	case camDirection::right:
		mCamPos += localRight * moveSpeed;
		break;
	default:
		break;
	}
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


	localYaw = glm::radians(yaw);
	localPitch = clampValue(min, max, glm::radians(pitch));


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