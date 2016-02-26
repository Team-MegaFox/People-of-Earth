// ***********************************************************************
// Author           : Pavan Jakhu
// Created          : 02-03-2016
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 02-03-2016
// ***********************************************************************
// <copyright file="GUIContainer.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "GUIComponent.h"

/// <summary>
/// The GUIContainer class is a GUI widget that has a background to it and
/// can have children that are only inside this widget.
/// </summary>
/// <seealso cref="GUIComponent" />
class GUIContainer : public GUIComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GUIContainer"/> class.
	/// </summary>
	/// <param name="destRectPerc">The dest rect perc.</param>
	/// <param name="destRectPix">The dest rect pix.</param>
	GUIContainer(const glm::vec4& destRectPerc, const glm::vec4& destRectPix) :
		GUIComponent(destRectPerc, destRectPix) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="GUIContainer"/> class.
	/// </summary>
	~GUIContainer() { }

	/// <summary>
	/// Adds to the Core Engine.
	/// </summary>
	/// <param name="engine">The Core Engine.</param>
	virtual void addToEngine(CoreEngine* engine)
	{
		GUIComponent::addToEngine(engine);
		CEGUI::FrameWindow* wi = static_cast<CEGUI::FrameWindow*>(createWidget(engine->getGUIEngine()->getSchemeStyle() + "/FrameWindow"));
		wi->setTitleBarEnabled(true);
		wi->getTitlebar()->disable();
		wi->setCloseButtonEnabled(false);
		wi->setSizingEnabled(false);
	}
};