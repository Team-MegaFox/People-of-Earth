// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie and Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 03-17-2016
// ***********************************************************************
// <copyright file="Utility.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#define SNPRINTF snprintf

#define ToRadians(x) (float)(((x) * 3.1415926536f / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / 3.1415926536f))
#define ZERO_MEM(a) memset(a,0,sizeof(a))
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
#define INVALID_VALUE 0xFFFFFFFF

#include <vector>
#include <string>
#include <PhysX\PxPhysicsAPI.h>
using namespace physx;

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
	const PxVec3 rotateQuatByVec(const PxQuat& quat, const PxVec3& v);

	/// <summary>
	/// Gets the maximum value in a 3D vector.
	/// </summary>
	/// <param name="vec">The 3D vector.</param>
	/// <returns>The highest value in the 3D vector.</returns>
	float maxVec3(const PxVec3 & vec);

	/// <summary>
	/// Gets the maximum value in a 4D vector.
	/// </summary>
	/// <param name="vec">The 4D vector.</param>
	/// <returns>The highest value in the 4D vector.</returns>
	float maxVec4(const PxVec4 & vec);

	/// <summary>
	/// Gets the forward facing vector based on the quaternion rotation.
	/// </summary>
	/// <param name="quat">The quaternion.</param>
	/// <returns>The vector facing in the forward direction.</returns>
	PxVec3 getForward(const PxQuat& quat);

	/// <summary>
	/// Gets the backward facing vector based on the quaternion rotation.
	/// </summary>
	/// <param name="quat">The quaternion.</param>
	/// <returns>The vector facing in the backward direction.</returns>
	PxVec3 getBack(const PxQuat& quat);

	/// <summary>
	/// Gets the upward facing vector based on the quaternion rotation.
	/// </summary>
	/// <param name="quat">The quaternion.</param>
	/// <returns>The vector facing in the upward direction.</returns>
	PxVec3 getUp(const PxQuat& quat);

	/// <summary>
	/// Gets the downward facing vector based on the quaternion rotation.
	/// </summary>
	/// <param name="quat">The quaternion.</param>
	/// <returns>The vector facing in the downward direction.</returns>
	PxVec3 getDown(const PxQuat& quat);

	/// <summary>
	/// Gets the right facing vector based on the quaternion rotation.
	/// </summary>
	/// <param name="quat">The quaternion.</param>
	/// <returns>The vector facing in the right direction.</returns>
	PxVec3 getRight(const PxQuat& quat);

	/// <summary>
	/// Gets the left facing vector based on the quaternion rotation.
	/// </summary>
	/// <param name="quat">The quaternion.</param>
	/// <returns>The vector facing in the left direction.</returns>
	PxVec3 getLeft(const PxQuat& quat);

	/// <summary>
	/// Gets the distance between 2 vector points.
	/// </summary>
	/// <param name="quat">The first point.</param>
	/// <param name = "quat">The second point.< / param>
	/// <returns>The distance.</returns>
	PxF32 getDistance(const PxVec3& point1, const PxVec3& point2);

	/// <summary>
	/// Get a initialized matrix with translation properties.
	/// </summary>
	/// <param name="translation">The translation.</param>
	/// <returns>The translation matrix.</returns>
	PxMat44 initTranslation(PxVec3 translation);

	/// <summary>
	/// Get a initialized matrix with the scale properties.
	/// </summary>
	/// <param name="translation">The translation.</param>
	/// <returns>The scaled matrix.</returns>
	PxMat44 initScale(PxVec3 scale);

	/// <summary>
	/// Gets the rotation matrix based on a target position and up vector.
	/// </summary>
	/// <param name="target">The target position.</param>
	/// <param name="up">The upward facing vector.</param>
	/// <returns>The result rotation matrix.</returns>
	PxMat44 initRotationFromDirection(const PxVec3& target, const PxVec3& up);

	/// <summary>
	/// Creates a perspective matrix.
	/// </summary>
	/// <param name="fov">The field of view of the camera.</param>
	/// <param name="aspect">The aspect ratio of the texture or window.</param>
	/// <param name="zNear">The near plane distance to the camera.</param>
	/// <param name="zFar">The far plane distance to the camera.</param>
	/// <returns>The result perspective matrix.</returns>
	PxMat44 initPerspective(float fov, float aspect, float zNear, float zFar);

	/// <summary>
	/// Creates a orthographic matrix.
	/// </summary>
	/// <param name="left">The distance to the plane on the left.</param>
	/// <param name="right">The distance to the plane on the right.</param>
	/// <param name="bottom">The distance to the plane on the bottom.</param>
	/// <param name="top">The distance to the plane on the top.</param>
	/// <param name="near">The distance to the nearest plane.</param>
	/// <param name="far">The distance to the furthest plane.</param>
	/// <returns>The result perspective matrix.</returns>
	PxMat44 initOrthographic(float left, float right, float bottom, float top, float near, float far);

	/// <summary>
	/// Template class that clamps the value.
	/// </summary>
	/// <param name="a">The value needing to be clamped.</param>
	/// <param name="min">The minimum possible value.</param>
	/// <param name="max">The maximum possible value.</param>
	/// <returns>The clamped value.</returns>
	template<typename T> inline T clamp(const T &a, const T &min, const T &max)
	{
		if (a < min) return min;
		else if (a > max) return max;
		else return a;
	}

	unsigned int classifyPoint(PxPlane plane, PxVec3 point);

	PxQuat slerp(PxQuat q1, PxQuat q2, float t);

	float getRandomNumber(float timestep, float min = 0.0f, float max = 1.0f);
}