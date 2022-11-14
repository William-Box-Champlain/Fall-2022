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

struct cameraTwo
{
	glm::vec3 mPosition = glm::vec3(0, 0, 0);
	glm::vec3 mForward;
	glm::vec3 mRight;
	glm::vec3 mUp;

	//mYaw and mPitch are in degrees
	float mYaw = 0;
	float mPitch = 0;

	glm::vec2 mPreviousMousePosition = glm::vec2(0.0f, 0.0f);

	float mSensitivity;

	bool firstInput = true;

	glm::vec3 getForward(float yaw, float pitch) //yaw and pitch are in degrees
	{
		glm::vec3 forward;
		float localYaw;
		float localPitch;

		localPitch = clamp(-89, 89, pitch);
		localPitch = glm::radians(localPitch);
		localYaw = glm::radians(yaw);

		forward.x = glm::cos(localYaw) * glm::cos(localPitch);
		forward.y = glm::sin(localPitch);
		forward.z = glm::sin(localYaw) * glm::cos(localPitch);

		return forward;
	}

	glm::vec3 getRight(glm::vec3 forward, glm::vec3 worldUp)
	{
		return glm::normalize(glm::cross(forward, worldUp));
	}

	glm::vec3 getUp(glm::vec3 right, glm::vec3 forward)
	{
		return glm::normalize(glm::cross(right, forward));
	}

	void getForwardRightUp(float yaw, float pitch, glm::vec3 worldUp)
	{
		mForward = getForward(yaw, pitch);
		mRight = getRight(mForward, worldUp);
		mUp = getUp(mRight, mForward);
	}

	void update(float yaw, float pitch, glm::vec3 worldUp)
	{

		std::cout << "yaw: " << yaw << " pitch: " << pitch << " mYaw: " << mYaw << " mPitch: " << mPitch << std::endl;

		float localYaw = yaw * mSensitivity;
		float localPitch = pitch * mSensitivity;

		mYaw = localYaw;
		mPitch = localPitch;

		getForwardRightUp(localYaw, localPitch, worldUp);
	}

	void update(glm::vec2 yawPitch, glm::vec3 worldUp)
	{
		update(yawPitch.x, yawPitch.y, worldUp);
	}

	void move(camDirection dir, float moveSpeed, float deltaTime, glm::vec3 worldUp)
	{
		mForward = getForward(mYaw, mPitch);
		mRight = getRight(mForward, worldUp);
		mUp = getUp(mRight, mForward);

		std::cout << "forward.x: " << mForward.x << " forward.y: " << mForward.y << " forward.z: " << mForward.z << std::endl;
		std::cout << "right.x: " << mRight.x << " right.y: " << mRight.y << " right.z: " << mRight.z << std::endl;
		std::cout << "up.x: " << mUp.x << " up.y: " << mUp.y << " up.z: " << mUp.z << std::endl;

		switch (dir)
		{
		case camDirection::forward:
			mPosition += mForward * moveSpeed * deltaTime;
			break;
		case camDirection::backwards:
			mPosition -= mForward * moveSpeed * deltaTime;
			break;
		case camDirection::up:
			mPosition += mUp * moveSpeed * deltaTime;
			break;
		case camDirection::down:
			mPosition -= mUp * moveSpeed * deltaTime;
			break;
		case camDirection::left:
			mPosition -= mRight * moveSpeed * deltaTime;
			break;
		case camDirection::right:
			mPosition += mRight * moveSpeed * deltaTime;
			break;
		default:
			break;
		}
	}

private:

	float clamp(float min, float max, float input)
	{
		if (input < min)return min;
		else if (input > max)return max;
		else return input;
	}

};