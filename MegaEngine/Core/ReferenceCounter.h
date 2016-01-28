// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="ReferenceCounter.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

/// <summary>
/// Stores a reference counter. May be used to count how many times an object is copied by reference.
/// </summary>
class ReferenceCounter
{
public:
	/// <summary>
	/// Contructs ReferenceCounter and sets the reference counter to 1.
	/// </summary>
	ReferenceCounter() :
		m_refCount(1) {}

	/// <summary>
	/// Gets the counter value.
	/// </summary>
	/// <returns>The reference coutner.</returns>
	inline int getReferenceCount() { return m_refCount; }

	/// <summary>
	/// Adds 1 to the reference counter.
	/// </summary>
	inline void addReference() { m_refCount++; }
	/// <summary>
	/// Removes 1 from the reference counter.
	/// </summary>
	/// <returns>If the reference counter is equal to 0.</returns>
	inline bool removeReference() { m_refCount--; return m_refCount == 0; }
protected:
private:
	/// <summary>
	/// Reference counter.
	/// </summary>
	int m_refCount;
};