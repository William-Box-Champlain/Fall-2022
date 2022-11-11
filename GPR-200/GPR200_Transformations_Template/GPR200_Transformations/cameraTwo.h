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
	float mYaw;
	float mPitch;

	glm::vec3 getForward(float yaw, float pitch) //yaw and pitch are in degrees
	{
		glm::vec3 forward;
		float localYaw;
		float localPitch;

		localPitch = clamp(-90, 90, pitch);
		localPitch = glm::radians(localPitch);
		localYaw = glm::radians(yaw);

		forward.x = glm::cos(localYaw) * glm::cos(localPitch);
		forward.y = glm::sin(localPitch);
		forward.z = glm::sin(localYaw) * glm::cos(localPitch);

		forward = glm::normalize(forward);

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

	void move(camDirection dir, float moveSpeed, float deltaTime, glm::vec3 worldUp)
	{
		mForward = getForward(mYaw, mPitch);
		mRight = getRight(mForward, worldUp);
		mUp = getUp(mRight, mForward);

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