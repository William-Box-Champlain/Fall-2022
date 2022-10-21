#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct transform {
	glm::mat4 mScale = glm::mat4(1);
	glm::mat4 mRotate = glm::mat4(1);
	glm::mat4 mTranslate = glm::mat4(1);
	glm::mat4 mTransform = mTranslate * mRotate * mScale;

	void reset()
	{
		mScale = glm::mat4(1);
		mRotate = glm::mat4(1);
		mTranslate = glm::mat4(1);
		mTransform = mScale * mRotate * mTranslate;
	}
};



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

	rotate[2][2] = glm::cos(a);
	rotate[2][3] = glm::sin(a);
	rotate[3][2] = -1 * glm::sin(a);
	rotate[3][3] = glm::cos(a);

	return rotate;
}

glm::mat4 rotateY(float a)
{
	glm::mat4 rotate(1);

	rotate[0][0] = glm::cos(a);
	rotate[0][3] = -1 * glm::sin(a);
	rotate[3][1] = glm::sin(a);
	rotate[3][3] = glm::cos(a);

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