#pragma once
#include <MegaEngine.h>
#include <glm\glm.hpp>

class TextLerpAlpha : public GameComponent
{
public:
	TextLerpAlpha() { }
	~TextLerpAlpha() { }

	virtual void onStart() 
	{
		m_label = getParent()->getGUIComponent<GUILabel>();
	}

	/// <summary>
	/// Virtual function for custom update functionality.
	/// </summary>
	/// <param name="delta">The frame time delta.</param>
	virtual void update(float delta) override
	{
		if (fadeOut)
		{
			m_alpha -= delta;
			if (m_alpha <= 0.1f)
			{
				fadeOut = false;
			}
		}
		else
		{
			m_alpha += delta;
			if (m_alpha >= 1.0f)
			{
				fadeOut = true;
			}
		}

		m_label->setAlpha(m_alpha);
	}

private:
	GUILabel* m_label;

	float m_alpha = 1.0f;

	bool fadeOut = true;

};