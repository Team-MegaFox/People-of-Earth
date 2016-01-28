#pragma once
#include <CEGUI\CEGUI.h>
#include "../Core/CoreEngine.h"
#include "../Core/GameObject.h"
#include "../GUI/GUIEngine.h"

/// <summary>
/// A Game Component class that attaches to GameObjects to have custom funcationality.
/// </summary>
/// <example>
/// <code>
/// class MeshRenderer : public GameComponet { ... }
/// </code>
/// </example>
class GUIComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GameComponent"/> class.
	/// </summary>
	GUIComponent(const glm::vec4& destRectPerc, const glm::vec4& destRectPix) :
		m_parent(nullptr), m_widget(nullptr), m_destRectPerc(destRectPerc), m_destRectPix(destRectPix) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="GameComponent"/> class.
	/// </summary>
	virtual ~GUIComponent() { }

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
	virtual void addToEngine(CoreEngine* engine) { }

	/// <summary>
	/// Sets the parent GameObject..
	/// </summary>
	/// <param name="parent">The GameObject to be attached to.</param>
	virtual void setParent(GameObject* parent) { m_parent = parent; }

protected:
	CoreEngine* getCoreEngine() { return m_parent->getCoreEngine(); }
	void setWidget(CEGUI::Window* widget) { m_widget = widget; }
	CEGUI::Window* getWidget() { return m_widget; }

	CEGUI::Window* createWidget(const std::string& widgetType)
	{
		m_widget = m_parent->getCoreEngine()->getGUIEngine()->addWidget(widgetType, m_destRectPerc, m_destRectPix, m_parent->getName());
		return m_widget;
	}

private:
	/// <summary>
	/// The parent GameObject.
	/// </summary>
	GameObject* m_parent;
	
	/// <summary>
	/// The CEGUI widget.
	/// </summary>
	CEGUI::Window* m_widget;

	glm::vec4 m_destRectPerc;
	glm::vec4 m_destRectPix;

	/// <summary>
	/// Initializes a new instance of the <see cref="GameComponent"/> class.
	/// </summary>
	/// <param name="other">The other.</param>
	GUIComponent(const GUIComponent& other) {}
	/// <summary>
	/// Operator=s the specified other.
	/// </summary>
	/// <param name="other">The other.</param>
	void operator=(const GUIComponent& other) {}
};