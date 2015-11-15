#include "Utility.h"
#include <SDL2/SDL.h>

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

// TODO : Quaterenion in GLM has no rotate that returns a vec3, also needs an angle. Also our Camera class doesn't use quaternions.

inline glm::vec3 getForward(const glm::quat & quat)
{
	//return quat.rotate(PxVec3(0, 0, 1));
}

inline glm::vec3 getBack(const glm::quat & quat)
{
	//return quat.rotate(PxVec3(0, 0, -1));
}

inline glm::vec3 getUp(const glm::quat & quat)
{
	//return quat.rotate(PxVec3(0, 1, 0));
}

inline glm::vec3 getDown(const glm::quat & quat)
{
	//return quat.rotate(PxVec3(0, -1, 0));
}

inline glm::vec3 getRight(const glm::quat & quat)
{
	//return quat.rotate(PxVec3(1, 0, 0));
}

inline glm::vec3 getLeft(const glm::quat & quat)
{
	//return quat.rotate(PxVec3(-1, 0, 0));
}
