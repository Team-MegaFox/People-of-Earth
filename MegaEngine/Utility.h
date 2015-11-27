#pragma once

#define SNPRINTF snprintf

#define ZERO_MEM(a) memset(a,0,sizeof(a))
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
#define INVALID_VALUE 0xFFFFFFFF
#define ToRadians(x) (float)(((x) * 3.1415926536f / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / 3.1415926536f))


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
	glm::quat temp = glm::rotate(quat, (float)quat.w, glm::vec3(0.0f, 0.0f, 1.0f));
	return glm::vec3(temp.x, temp.y, temp.z);
}

inline glm::vec3 getBack(const glm::quat & quat)
{
	glm::quat temp = glm::rotate(quat, (float)quat.w, glm::vec3(0.0f, 0.0f, -1.0f));
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