// ***********************************************************************
// Author           : Pavan Jakhu
// Created          : 01-28-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="GUIComponent.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include <CEGUI\CEGUI.h>
#include "../Core/CoreEngine.h"
#include "../Core/GameObject.h"
#include "../GUI/GUIEngine.h"

/// <summary>
/// A GUI Component class that attaches to GameObjects to have GUI funcationality.
/// </summary>
/// <example>
///   <code>
/// class MeshRenderer : public GUIComponent { ... }
/// </code>
/// </example>
class GUIComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GUIComponent"/> class.
	/// </summary>
	/// <param name="destRectPerc">The size of the widget relative the parent widget.</param>
	/// <param name="destRectPix">The size of the widget in pixels.</param>
	GUIComponent(const PxVec4& destRectPerc, const PxVec4& destRectPix) :
		m_parent(nullptr), m_widget(nullptr), m_destRectPerc(destRectPerc), m_destRectPix(destRectPix) { }

	/// <summary>
	/// Finalizes an instance of the <see cref="GUIComponent"/> class.
	/// </summary>
	virtual ~GUIComponent() 
	{
		//m_widget->removeAllEvents();
		CEGUI::WindowManager::getSingleton().destroyWindow(m_widget);
	}
	/// <summary>
	/// Virtual function for custom input processing.
	/// </summary>
	/// <param name="input">The input manager.</param>
	/// <param name="delta">The frame time delta.</param>
	virtual void processInput(const InputManager& input, float delta) { }

	/// <summary>
	/// Virtual function for custom update functionality.
	/// </summary>
	/// <param name="delta">The frame time delta.</param>
	virtual void update(float delta) { }

	/// <summary>
	/// Adds to Core Engine.
	/// </summary>
	/// <param name="engine">The Core Engine.</param>
	virtual void addToEngine(CoreEngine* engine) 
	{
		GameObject* parentGO = m_parent->getTransform()->getParent()->getAttachedGameObject();
		if (parentGO != nullptr)
		{
			m_parentWidget = parentGO->getGUIComponent<GUIComponent>();
		}
		else
		{
			m_parentWidget = nullptr;
		}
	}

	/// <summary>
	/// Gets the parented gameobject.
	/// </summary>
	/// <returns>A pointer to the parented gameobject.</returns>
	GameObject* getParent() { return m_parent; }

	/// <summary>
	/// Gets the relative position to the window.
	/// </summary>
	/// <returns>A vector 2D of the relative position.</returns>
	PxVec2 getPercentPosition() { return PxVec2(m_widget->getPosition().d_x.d_scale, m_widget->getPosition().d_y.d_scale); }

	/// <summary>
	/// Gets the absolute pixel position to the window.
	/// </summary>
	/// <returns>A vector 2D of the absolute pixel position.</returns>
	PxVec2 getPixelPosition() { return PxVec2(m_widget->getPosition().d_x.d_offset, m_widget->getPosition().d_y.d_offset); }

	/// <summary>
	/// Sets the parent GameObject.
	/// </summary>
	/// <param name="parent">The GameObject to be attached to.</param>
	virtual void setParent(GameObject* parent) { m_parent = parent; }

	/// <summary>
	/// Sets the relative position.
	/// </summary>
	/// <param name="pos">The position in percentage relative to the window.</param>
	void setPercentPosition(const PxVec2& pos) { m_widget->setPosition(CEGUI::UVector2(CEGUI::UDim(pos.x, 0.0f), CEGUI::UDim(pos.y, 0.0f))); }
	
	/// <summary>
	/// Sets the absolute pixel position.
	/// </summary>
	/// <param name="pos">The position in pixels to the window.</param>
	void setPixelPosition(const PxVec2& pos) { m_widget->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, pos.x), CEGUI::UDim(0.0f, pos.y))); }

	/// <summary>
	/// Activates the widget so it accepts input.
	/// </summary>
	void activate() { m_widget->enable(); }

	/// <summary>
	/// Deactivates the widget so it doesn't accept input.
	/// </summary>
	void deactivate() { m_widget->disable(); }

	/// <summary>
	/// Renders the widget.
	/// </summary>
	void enable() { m_widget->show(); }

	/// <summary>
	/// Stops rendering the widget.
	/// </summary>
	void disable() { m_widget->hide(); }

protected:	

	/// <summary>
	/// Gets the core engine.
	/// </summary>
	/// <returns>CoreEngine *.</returns>
	CoreEngine* getCoreEngine() { return m_parent->getCoreEngine(); }

	/// <summary>
	/// Sets the widget.
	/// </summary>
	/// <param name="widget">The widget.</param>
	void setWidget(CEGUI::Window* widget) { m_widget = widget; }

	/// <summary>
	/// Gets the widget.
	/// </summary>
	/// <returns>CEGUI.Window *.</returns>
	CEGUI::Window* getWidget() const { return m_widget; }

	/// <summary>
	/// Creates a widget.
	/// </summary>
	/// <param name="widgetType">Type of the widget.</param>
	/// <returns>CEGUI.Window *.</returns>
	CEGUI::Window* createWidget(const std::string& widgetType)
	{
		if (m_parentWidget == nullptr)
		{
			m_widget = m_parent->getCoreEngine()->getGUIEngine()->addWidget(widgetType, m_destRectPerc, m_destRectPix, m_parent->getName() + std::to_string(s_numWidgets));
		}
		else
		{
			m_widget = m_parent->getCoreEngine()->getGUIEngine()->addWidget(m_parentWidget->getWidget(), widgetType, m_destRectPerc, m_destRectPix, m_parent->getName() + std::to_string(s_numWidgets));
		}
		m_widget->moveToFront();
		s_numWidgets++;
		return m_widget;
	}

private:
	static int s_numWidgets;

	/// <summary>
	/// The parent GameObject.
	/// </summary>
	GameObject* m_parent;
	
	/// <summary>
	/// The parent widget.
	/// </summary>
	GUIComponent* m_parentWidget;
	
	/// <summary>
	/// The CEGUI widget.
	/// </summary>
	CEGUI::Window* m_widget;

	/// <summary>
	/// The destestion rectangle in percent relative to the parent window.
	/// </summary>
	PxVec4 m_destRectPerc;

	/// <summary>
	/// The destestion rectangle in pixels.
	/// </summary>
	PxVec4 m_destRectPix;

	/// Initializes a new instance of the <see cref="GameComponent" /> class.
	/// </summary>
	/// <param name="other">The other.</param>
	GUIComponent(const GUIComponent& other) {}

	/// <summary>
	/// Operator=s the specified other.
	/// </summary>
	/// <param name="other">The other.</param>
	void operator=(const GUIComponent& other) {}
};
