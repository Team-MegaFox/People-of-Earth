// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="Utility.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#define SNPRINTF snprintf

#define ZERO_MEM(a) memset(a,0,sizeof(a))
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
#define INVALID_VALUE 0xFFFFFFFF

#include <vector>
#include <string>
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>

/// <summary>
/// The Utility namespace.
/// </summary>
namespace Utility
{
	/// <summary>
	/// Sleeps the specified milliseconds.
	/// </summary>
	/// <param name="milliseconds">The milliseconds.</param>
	void sleep(int milliseconds);

	/// <summary>
	/// Splits the specified string by a delimiter..
	/// </summary>
	/// <param name="s">The string.</param>
	/// <param name="delim">The delimiter.</param>
	/// <returns>The sperated string in a vector.</returns>
	std::vector<std::string> split(const std::string& s, char delim);

	/// <summary>
	/// Rotates the quaternion by vector.
	/// </summary>
	/// <param name="quat">The quaternion.</param>
	/// <param name="v">The vector.</param>
	/// <returns>The rotated vector.</returns>
	const glm::vec3 rotateQuatByVec(const glm::quat& quat, const glm::vec3& v);

	/// <summary>
	/// Gets the maximum value in a 3D vector.
	/// </summary>
	/// <param name="vec">The 3D vector.</param>
	/// <returns>The highest value in the 3D vector.</returns>
	float maxVec3(const glm::vec3 & vec);

	/// <summary>
	/// Gets the maximum value in a 4D vector.
	/// </summary>
	/// <param name="vec">The 4D vector.</param>
	/// <returns>The highest value in the 4D vector.</returns>
	float maxVec4(const glm::vec4 & vec);

	/// <summary>
	/// Gets the forward facing vector based on the quaternion rotation.
	/// </summary>
	/// <param name="quat">The quaternion.</param>
	/// <returns>The vector facing in the forward direction.</returns>
	glm::vec3 getForward(const glm::quat quat);

	/// <summary>
	/// Gets the backward facing vector based on the quaternion rotation.
	/// </summary>
	/// <param name="quat">The quaternion.</param>
	/// <returns>The vector facing in the backward direction.</returns>
	glm::vec3 getBack(const glm::quat quat);

	/// <summary>
	/// Gets the upward facing vector based on the quaternion rotation.
	/// </summary>
	/// <param name="quat">The quaternion.</param>
	/// <returns>The vector facing in the upward direction.</returns>
	glm::vec3 getUp(const glm::quat quat);

	/// <summary>
	/// Gets the downward facing vector based on the quaternion rotation.
	/// </summary>
	/// <param name="quat">The quaternion.</param>
	/// <returns>The vector facing in the downward direction.</returns>
	glm::vec3 getDown(const glm::quat quat);

	/// <summary>
	/// Gets the right facing vector based on the quaternion rotation.
	/// </summary>
	/// <param name="quat">The quaternion.</param>
	/// <returns>The vector facing in the right direction.</returns>
	glm::vec3 getRight(const glm::quat quat);

	/// <summary>
	/// Gets the left facing vector based on the quaternion rotation.
	/// </summary>
	/// <param name="quat">The quaternion.</param>
	/// <returns>The vector facing in the left direction.</returns>
	glm::vec3 getLeft(const glm::quat quat);

	/// <summary>
	/// Get a initialized matrix with translation properties.
	/// </summary>
	/// <param name="translation">The translation.</param>
	/// <returns>The translation matrix.</returns>
	glm::mat4 initTranslation(glm::vec3 translation);

	/// <summary>
	/// Get a initialized matrix with the scale properties.
	/// </summary>
	/// <param name="translation">The translation.</param>
	/// <returns>The scaled matrix.</returns>
	glm::mat4 initScale(glm::vec3 scale);

	/// <summary>
	/// Gets the rotation matrix based on a target position and up vector.
	/// </summary>
	/// <param name="target">The target position.</param>
	/// <param name="up">The upward facing vector.</param>
	/// <returns>The result rotation matrix.</returns>
	glm::mat4 initRotationFromDirection(const glm::vec3 & target, const glm::vec3 & up);

}