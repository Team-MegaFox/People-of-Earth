#pragma once
#include <MegaEngine.h>

#include "MissionOneScene.h"

class MissionSelectManager : public GameComponent
{
public:
	MissionSelectManager(Uint8 numMissions) : m_numMissions(numMissions) { }
	~MissionSelectManager() { }

	virtual void onStart() override
	{
		for (size_t i = 1; i <= m_numMissions; i++)
		{
			m_missionWidgets.push_back(getGameObjectByName("Mission " + std::to_string(i))->getGUIComponent<GUIContainer>());
		}

		m_focusMission = m_missionWidgets[m_focusMissionIndex];
	}

	/// <summary>
	/// Virtual function for custom input processing.
	/// </summary>
	/// <param name="input">The input manager.</param>
	/// <param name="delta">The frame time delta.</param>
	virtual void processInput(const InputManager& input, float delta) override
	{
		if (!m_move)
		{
			if (input.KeyPress(SDLK_d) || input.GetThumbLPosition().x > 0.2f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
			{
				if (m_focusMission != m_missionWidgets.back())
				{
					m_focusMissionIndex++;
					m_focusMission = m_missionWidgets[m_focusMissionIndex];

					m_move = true;
					m_moveLeft = false;
				}
				else
				{
					m_focusMission = m_missionWidgets.back();
				}
			}
			else if (input.KeyPress(SDLK_a) || input.GetThumbLPosition().x < -0.2f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
			{
				if (m_focusMission != m_missionWidgets.front())
				{
					m_focusMissionIndex--;
					m_focusMission = m_missionWidgets[m_focusMissionIndex];

					m_move = true;
					m_moveLeft = true;
				}
				else
				{
					m_focusMission = m_missionWidgets.front();
				}
			}

			if (input.KeyPress(SDLK_RETURN) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_A))
			{
				if (m_focusMissionIndex == 0)
				{
					getCoreEngine()->getSceneManager()->push(new MissionOneScene);
				}
			}
		}
	}

	/// <summary>
	/// Virtual function for custom update functionality.
	/// </summary>
	/// <param name="delta">The frame time delta.</param>
	virtual void update(float delta) 
	{
		if (m_move)
		{
			m_movePosition += m_moveSpeed * delta;
			if (m_moveLeft)
			{
				for (size_t i = 0; i < m_missionWidgets.size(); i++)
				{
					m_missionWidgets[i]->setPercentPosition(m_missionWidgets[i]->getPercentPosition() + PxVec2(m_moveSpeed * delta, 0.0f));
				}
			}
			else
			{
				for (size_t i = 0; i < m_missionWidgets.size(); i++)
				{
					m_missionWidgets[i]->setPercentPosition(m_missionWidgets[i]->getPercentPosition() - PxVec2(m_moveSpeed * delta, 0.0f));
				}
			}

			if (m_movePosition >= 1.0f)
			{
				m_move = false;
				m_movePosition = 0.0f;
			}
		}
	}

private:
	std::vector<GUIContainer*> m_missionWidgets;

	GUIContainer* m_focusMission;

	Uint8 m_focusMissionIndex = 0;

	Uint8 m_numMissions = 0;

	bool m_moveLeft = false, m_move = false;

	float m_movePosition = 0.0f;

	float m_moveSpeed = 2.0f;

};
