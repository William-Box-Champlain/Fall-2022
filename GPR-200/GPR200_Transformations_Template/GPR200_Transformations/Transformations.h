#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "camera.h"

enum class direction
{
	forward,
	backwards,
	up,
	down,
	left,
	right,
};

enum rotation
{
	cwX,
	ccX,
	cwY,
	ccY,
	cwZ,
	ccZ
};

enum size
{
	grow,
	shrink
};


namespace wb
{
	glm::mat4 scale(float x, float y, float z)
	{
		glm::mat4 scaleMatrix(1);

		scaleMatrix[0][0] = x;
		scaleMatrix[1][1] = y;
		scaleMatrix[2][2] = z;

		return scaleMatrix;

	}

	glm::mat4 scale(glm::vec3 v)
	{
		glm::mat4 scaleMatrix(1);

		scaleMatrix[0][0] = v.x;
		scaleMatrix[1][1] = v.y;
		scaleMatrix[2][2] = v.z;

		return scaleMatrix;

	}

	glm::mat4 rotateX(float a)
	{
		glm::mat4 rotate(1);

		rotate[1][1] = glm::cos(a);
		rotate[1][2] = glm::sin(a);
		rotate[2][1] = -1 * glm::sin(a);
		rotate[2][2] = glm::cos(a);

		return rotate;
	}

	glm::mat4 rotateY(float a)
	{
		glm::mat4 rotate(1);

		rotate[0][0] = glm::cos(a);
		rotate[0][2] = -1 * glm::sin(a);
		rotate[2][0] = glm::sin(a);
		rotate[2][2] = glm::cos(a);

		return rotate;
	}

	glm::mat4 rotateZ(float a)
	{
		glm::mat4 rotate(1);

		rotate[0][0] = glm::cos(a);
		rotate[0][1] = glm::sin(a);
		rotate[1][0] = -1 * glm::sin(a);
		rotate[1][1] = glm::cos(a);

		return rotate;

	}

	glm::mat4 rotateXYZ(glm::vec3 a)
	{
		glm::mat4 rotate(1);
		rotate *= rotateX(a.x);
		rotate *= rotateY(a.y);
		rotate *= rotateZ(a.z);

		return rotate;
	}

	glm::mat4 translate(float x, float y, float z)
	{
		glm::mat4 translate(1);

		translate[3][0] = x;
		translate[3][1] = y;
		translate[3][2] = z;

		return translate;

	}

	glm::mat4 translate(glm::vec3 v)
	{
		glm::mat4 translate(1);

		translate[3][0] = v.x;
		translate[3][1] = v.y;
		translate[3][2] = v.z;

		return translate;

	}

	glm::mat4 lookAt(glm::vec3 eyePos, glm::vec3 targetPos, glm::vec3 up)
	{
		glm::vec3 f = glm::normalize(eyePos - targetPos);
		glm::vec3 r = glm::normalize(glm::cross(up, f));
		glm::vec3 u = glm::normalize(cross(f, r));

		glm::mat4 lookAt(1);
		lookAt[0][0] = r.x;
		lookAt[0][1] = r.y;
		lookAt[0][2] = r.z;
		lookAt[1][0] = u.x;
		lookAt[1][1] = u.y;
		lookAt[1][2] = u.z;
		lookAt[2][0] = f.x;
		lookAt[2][1] = f.y;
		lookAt[2][2] = f.z;

		glm::vec3 translationVector = eyePos;

		translationVector *= -1;

		lookAt *= translate(translationVector);

		return lookAt;
	}

	glm::mat4 ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane)
	{
		glm::mat4 orthoMatrix(1);
		orthoMatrix[0][0] = 2 / (right - left);
		orthoMatrix[1][1] = 2 / (top - bottom);
		orthoMatrix[2][2] = -2 / (farPlane - nearPlane);
		orthoMatrix[3][0] = -(right + left) / (right - left);
		orthoMatrix[3][1] = -(top + bottom) / (top - bottom);
		orthoMatrix[3][1] = -(farPlane + nearPlane) / (farPlane - nearPlane);

		return orthoMatrix;
	}

	glm::mat4 ortho(float height, float aspectRatio, float nearPlane, float farPlane)
	{
		float bottom = height / -2;
		float top = height / 2;

		float width = aspectRatio * height;

		float left = width / -2;
		float right = width / 2;

		return ortho(left, right, bottom, top, nearPlane, farPlane);
	}

	glm::mat4 perspective(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		float fovRad = glm::radians(fov);
		float c = glm::tan(fovRad / 2);
		glm::mat4 perspectiveMatrix(1);
		perspectiveMatrix[0][0] = 1 / (aspectRatio * c);
		perspectiveMatrix[1][1] = c;
		perspectiveMatrix[2][2] = -1 * ((farPlane + nearPlane) / (farPlane - nearPlane));
		perspectiveMatrix[3][2] = -1 * ((2 * farPlane * nearPlane) / (farPlane - nearPlane));
		perspectiveMatrix[2][3] = -1;

		return perspectiveMatrix;
	}
};

struct transform {

	float mScaleRate;
	glm::vec3 mRotationRate;
	glm::vec3 mTranslationRate;

	glm::mat4 mScale = glm::mat4(1);
	glm::mat4 mRotate = glm::mat4(1);
	glm::mat4 mTranslate = glm::mat4(1);

	glm::mat4 mTransform = mTranslate * mRotate * mScale;

	void reset()
	{
		mScale = glm::mat4(1);
		mRotate = glm::mat4(1);
		mTranslate = glm::mat4(1);
		mTransform = mTranslate * mRotate * mScale;
	}
	void coutTransform()
	{
		std::cout << mTransform[0][0];
		for (int i = 0; i < mTransform.length(); i++)
		{
			for (int j = 0; j < mTransform.length(); j++)
			{
				std::cout << mTransform[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	void update()
	{
		mTransform = mTranslate * mRotate * mScale;
	}
	glm::mat4 getTransform(float deltaTime)
	{
		update();
		return mTransform * deltaTime;
	}
	void setRotation(glm::vec3 rotation)
	{
		mRotationRate = rotation;
	}
	void setTranslation(glm::vec3 translation)
	{
		mTranslationRate = translation;
	}
	void setScale(float scale) //scale is a percentage. I.E. .1 = 10% growth/shrink
	{
		mScaleRate = scale;
	}
	void translate(direction d)
	{
		switch (d)
		{
		case direction::up:
			mTranslate *= wb::translate(0, mTranslationRate.y, 0);
			break;
		case direction::down:
			mTranslate *= wb::translate(0, -1*mTranslationRate.y, 0);
			break;
		case direction::left:
			mTranslate *= wb::translate(-1*mTranslationRate.x, 0, 0);
			break;
		case direction::right:
			mTranslate *= wb::translate(mTranslationRate.x, 0, 0);
			break;
		default:
			break;
		}
	}
	void rotate(rotation r)
	{
		switch (r)
		{
		case cwX:
			mRotate *= wb::rotateX(mRotationRate.x);
			break;
		case ccX:
			mRotate *= wb::rotateX(-1*mRotationRate.x);
			break;
		case cwY:
			mRotate *= wb::rotateY(mRotationRate.y);
			break;
		case ccY:
			mRotate *= wb::rotateY(-1*mRotationRate.y);
			break;
		case cwZ:
			mRotate *= wb::rotateZ(mRotationRate.z);
			break;
		case ccZ:
			mRotate *= wb::rotateZ(-1*mRotationRate.z);
			break;
		default:
			break;
		}
	}
	void scale(size s)
	{
		glm::vec3 bigger = glm::vec3(1 + mScaleRate);
		glm::vec3 smaller = glm::vec3(1 - mScaleRate);
		switch (s)
		{
		case grow:
			mScale *= wb::scale(bigger);
			break;
		case shrink:
			mScale *= wb::scale(smaller);
			break;
		default:
			break;
		}
	}
	
};

struct projectionMatrix
{
	float mFov;
	float mNearPlane;
	float mFarPlane;
	float mAspectRatio;
	int mHeight;
	int mWidth;
	
	glm::mat4 perspectiveMatrix;
	glm::mat4 orthoMatrix;

	projectionMatrix(float fov, float nearPlane, float farPlane, int width, int height)
	{
		mFov = fov;
		mNearPlane = nearPlane;
		mFarPlane = farPlane;
		mHeight = height;
		mWidth = width;
		mAspectRatio = width / height;

		perspectiveMatrix = wb::perspective(mFov, mAspectRatio, mNearPlane, mFarPlane);
		orthoMatrix = wb::ortho(mHeight, mAspectRatio, mNearPlane, mFarPlane);
	}

	void updateFov(float fovDelta)
	{
		mFov += fovDelta;

		perspectiveMatrix = wb::perspective(mFov, mAspectRatio, mNearPlane, mFarPlane);
	}
};