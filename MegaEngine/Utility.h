#pragma once

#define SNPRINTF snprintf

#define ZERO_MEM(a) memset(a,0,sizeof(a))
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
#define INVALID_VALUE 0xFFFFFFFF



#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

namespace Utility
{
	void sleep(int milliseconds);
	std::vector<std::string> split(const std::string &s, char delim);
};

inline float max(const glm::vec3 & vec);
inline float max(const glm::vec4 & vec);
inline glm::vec3 getForward(const glm::quat & quat);
inline glm::vec3 getBack(const glm::quat & quat);
inline glm::vec3 getUp(const glm::quat & quat);
inline glm::vec3 getDown(const glm::quat & quat);
inline glm::vec3 getRight(const glm::quat & quat);
inline glm::vec3 getLeft(const glm::quat & quat);