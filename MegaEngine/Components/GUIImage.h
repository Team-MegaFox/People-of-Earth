// ***********************************************************************
// Author           : Pavan Jakhu
// Created          : 02-02-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="GUIProgressBar.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "GUIComponent.h"

/// <summary>
/// TThe GUIProgressBar class displays a progress bar on the screen.
/// </summary>
/// <seealso cref="GUIComponent" />
class GUIImage : public GUIComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GUIProgressBar"/> class.
	/// </summary>
	/// <param name="destRectPerc">The size of the widget relative the parent widget.</param>
	/// <param name="destRectPix">The size of the widget in pixels.</param>
	/// <param name="startPerc">The start percentage. Defaults to 1.0f (100%).</param>
	/// <param name="stepPerc">The step percentage. Defaults to 0.1f (1%).(</param>
	GUIImage(const physx::PxVec4& destRectPerc, const physx::PxVec4& destRectPix, const std::string& imageFile) :
		GUIComponent(destRectPerc, destRectPix), m_imageFile(imageFile) 
	{ 
		s_numImages++; 
		m_numImage = s_numImages; 
	}
	/// <summary>
	/// Finalizes an instance of the <see cref="GUIProgressBar"/> class.
	/// </summary>
	~GUIImage() 
	{ 
		//Might need to delete the image from CEGUI's ImageManager.
	}

	/// <summary>
	/// Adds to the Core Engine.
	/// </summary>
	/// <param name="engine">A pointer to the Core Engine.</param>
	virtual void addToEngine(CoreEngine* engine)
	{
		GUIComponent::addToEngine(engine);
		m_image = static_cast<CEGUI::DefaultWindow*>(createWidget(engine->getGUIEngine()->getSchemeStyle() + "/StaticImage"));
		CEGUI::ImageManager::getSingleton().addFromImageFile(m_imageFile + "__" + std::to_string(m_numImage), "../../" + m_imageFile);
		m_image->setProperty("Image", m_imageFile + "__" + std::to_string(m_numImage));
		m_image->setProperty("BackgroundEnabled", "False");
		m_image->setProperty("FrameEnabled", "False");
	}

private:
	/// <summary>
	/// The total number of GUIImage objects.
	/// </summary>
	static Uint16 s_numImages;

	/// <summary>
	/// The progress bar widget.
	/// </summary>
	CEGUI::DefaultWindow* m_image;

	/// <summary>
	/// The image file.
	/// </summary>
	std::string m_imageFile;

	/// <summary>
	/// The image number based on s_numImages;
	/// </summary>
	Uint16 m_numImage;

};
