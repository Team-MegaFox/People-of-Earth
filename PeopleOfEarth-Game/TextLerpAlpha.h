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
		m_orginalText = m_label->getText();
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

		int alphaV = (int)(m_alpha * 255.0f);
		std::stringstream ss;
		ss << "[colour='" << std::hex << alphaV << "FFFFFF']";
		std::string stringstream = ss.str();
		m_label->setText(ss.str() + m_orginalText);
	}

private:
	GUILabel* m_label;

	float m_alpha = 1.0f;

	bool fadeOut = true;

	std::string m_orginalText;

};