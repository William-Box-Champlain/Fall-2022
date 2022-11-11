#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ewMath.h"

const glm::vec3 WORLD_UP = glm::vec3(0, 1, 0);

struct Camera {
	glm::vec3 position = glm::vec3(0, 0, 5);
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
	float fov = 45.0f;
	float nearPlane = 0.01f;
	float farPlane = 100.0f;
	float orthoSize = 7.5f;
	bool ortho = false;
	float moveSpeed = 5.0f;
	float zoomSpeed = 3.0f; //FovY degrees per scroll click
	float yaw = -90.0f;
	float pitch = 0.0f;
	float aspectRatio = 0.0f;

	Camera(float aspectRatio) : aspectRatio(aspectRatio) {
		updateVectors();
	}
	glm::mat4 getViewMatrix() {
		return ew::lookAt(position, position + forward, WORLD_UP);
	}
	glm::mat4 getProjectionMatrix() {
		if (ortho) {
			float halfSize = orthoSize * 0.5f;
			return ew::ortho(-halfSize * aspectRatio, halfSize * aspectRatio, -halfSize, halfSize, nearPlane, farPlane);
		}
		else {
			return ew::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
		}
	}
	void updateVectors() {
		float yawRad = glm::radians(yaw);
		float pitchRad = glm::radians(pitch);

		forward.x = cos(yawRad) * cos(pitchRad);
		forward.y = sin(pitchRad);
		forward.z = sin(yawRad) * cos(pitchRad);

		right = glm::normalize(glm::cross(forward, WORLD_UP));
		up = glm::normalize(glm::cross(forward, right));
	}
};