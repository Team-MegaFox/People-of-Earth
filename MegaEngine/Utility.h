#pragma once

#define SNPRINTF snprintf

#define ZERO_MEM(a) memset(a,0,sizeof(a))
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
#define INVALID_VALUE 0xFFFFFFFF
#define ToRadians(x) (float)(((x) * 3.1415926536f / 180.0f))
#define ToDegrees(x) (float)(((x) * 180.0f / 3.1415926536f))


#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm\gtc\quaternion.hpp>


namespace Utility
{
	void sleep(int milliseconds);
	std::vector<std::string> split(const std::string &s, char delim);
};

inline float max(const glm::vec3 & vec)
{
	float Max = vec[0];

	for (int i = 0; i < 3; i++)
		if (vec[i] > Max)
			Max = vec[i];

	return Max;
}

inline float max(const glm::vec4 & vec)
{
	float Max = vec[0];

	for (int i = 0; i < 4; i++)
		if (vec[i] > Max)
			Max = vec[i];

	return Max;
}

inline glm::vec3 getForward(const glm::quat & quat)
{
	glm::quat temp = glm::rotate(quat, (float)quat.w, glm::vec3(0.0f, 0.0f, -1.0f));
	return glm::vec3(temp.x, temp.y, temp.z);
}

inline glm::vec3 getBack(const glm::quat & quat)
{
	glm::quat temp = glm::rotate(quat, (float)quat.w, glm::vec3(0.0f, 0.0f, 1.0f));
	return glm::vec3(temp.x, temp.y, temp.z);
}

inline glm::vec3 getUp(const glm::quat & quat)
{
	glm::quat temp = glm::rotate(quat, (float)quat.w, glm::vec3(0.0f, 1.0f, 0.0f));
	return glm::vec3(temp.x, temp.y, temp.z);
}

inline glm::vec3 getDown(const glm::quat & quat)
{
	glm::quat temp = glm::rotate(quat, (float)quat.w, glm::vec3(0.0f, -1.0f, 0.0f));
	return glm::vec3(temp.x, temp.y, temp.z);
}

inline glm::vec3 getRight(const glm::quat & quat)
{
	glm::quat temp = glm::rotate(quat, (float)quat.w, glm::vec3(1.0f, 0.0f, 0.0f));
	return glm::vec3(temp.x, temp.y, temp.z);
}

inline glm::vec3 getLeft(const glm::quat & quat)
{
	glm::quat temp = glm::rotate(quat, (float)quat.w, glm::vec3(-1.0f, 0.0f, 0.0f));
	return glm::vec3(temp.x, temp.y, temp.z);
}


inline const glm::vec3 rotateQuatByVec(const glm::quat& quat, const glm::vec3& v)
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

inline glm::mat4 initTranslation(glm::vec3 translation)
{
	return glm::mat4(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(translation, 1.0f)
		);
}

inline glm::mat4 initScale(glm::vec3 scale)
{
	return glm::mat4(
		glm::vec4(scale.x, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, scale.y, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, scale.z, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		);
}

inline glm::mat4 initRotationFromDirection(const glm::vec3 & target, const glm::vec3 & up)
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