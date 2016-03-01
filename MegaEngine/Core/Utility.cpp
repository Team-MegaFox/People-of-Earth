#include "Utility.h"
#include <SDL2\SDL.h>

void Utility::sleep(int milliseconds)
{
	SDL_Delay(milliseconds);
}

std::vector<std::string> Utility::split(const std::string& s, char delim)
{
	std::vector<std::string> elems;

	const char* cstr = s.c_str();
	unsigned int strLength = (unsigned int)s.length();
	unsigned int start = 0;
	unsigned int end = 0;

	while (end <= strLength)
	{
		while (end <= strLength)
		{
			if (cstr[end] == delim)
				break;
			end++;
		}

		elems.push_back(s.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return elems;
}

const glm::vec3 Utility::rotateQuatByVec(const glm::quat& quat, const glm::vec3& v)
{
	const glm::f32 vx = 2.0f*v.x;
	const glm::f32 vy = 2.0f*v.y;
	const glm::f32 vz = 2.0f*v.z;
	const glm::f32 w2 = quat.w*quat.w - 0.5f;
	const glm::f32 dot2 = (quat.x*vx + quat.y*vy + quat.z*vz);
	return glm::vec3
		(
		(vx*w2 + (quat.y * vz - quat.z * vy)*quat.w + quat.x*dot2),
		(vy*w2 + (quat.z * vx - quat.x * vz)*quat.w + quat.y*dot2),
		(vz*w2 + (quat.x * vy - quat.y * vx)*quat.w + quat.z*dot2)
		);
}

float Utility::maxVec3(const glm::vec3 & vec)
{
	float Max = vec[0];

	for (int i = 0; i < 3; i++)
		if (vec[i] > Max)
			Max = vec[i];

	return Max;
}

float Utility::maxVec4(const glm::vec4 & vec)
{
	float Max = vec[0];

	for (int i = 0; i < 4; i++)
		if (vec[i] > Max)
			Max = vec[i];

	return Max;
}

glm::vec3 Utility::getForward(const glm::quat& quat)
{
	return Utility::rotateQuatByVec(quat, glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::vec3 Utility::getBack(const glm::quat& quat)
{
	return Utility::rotateQuatByVec(quat, glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 Utility::getUp(const glm::quat& quat)
{
	return Utility::rotateQuatByVec(quat, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 Utility::getDown(const glm::quat& quat)
{
	return Utility::rotateQuatByVec(quat, glm::vec3(0.0f, -1.0f, 0.0f));
}

glm::vec3 Utility::getRight(const glm::quat& quat)
{
	return Utility::rotateQuatByVec(quat, glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::vec3 Utility::getLeft(const glm::quat& quat)
{
	return Utility::rotateQuatByVec(quat, glm::vec3(-1.0f, 0.0f, 0.0f));
}

glm::mat4 Utility::initTranslation(glm::vec3 translation)
{
	return glm::mat4(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(translation, 1.0f)
		);
}

glm::mat4 Utility::initScale(glm::vec3 scale)
{
	return glm::mat4(
		glm::vec4(scale.x, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, scale.y, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, scale.z, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		);
}

glm::mat4 Utility::initRotationFromDirection(const glm::vec3 & target, const glm::vec3 & up)
{
	glm::vec3 n = target;
	glm::normalize(n);

	glm::vec3 u = up;
	glm::normalize(u);
	glm::cross(u, n);

	glm::vec3 v = glm::cross(n, u);

	glm::mat4 m;
	m[0][0] = u.x;   m[1][0] = u.y;   m[2][0] = u.z;   m[3][0] = 0.0f;
	m[0][1] = v.x;   m[1][1] = v.y;   m[2][1] = v.z;   m[3][1] = 0.0f;
	m[0][2] = n.x;   m[1][2] = n.y;   m[2][2] = n.z;   m[3][2] = 0.0f;
	m[0][3] = 0.0f;  m[1][3] = 0.0f;  m[2][3] = 0.0f;  m[3][3] = 1.0f;
	return m;
}