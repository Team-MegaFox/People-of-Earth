// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 04-04-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 04-04-2016
// ***********************************************************************
// <copyright file="MissileGUI.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#include <MegaEngine.h>
#include "FireProjectile.h"
#include <MegaEngine.h>

class MissileGUI : public GameComponent
{
public:
	MissileGUI() {}

	~MissileGUI() {}

	virtual void onStart() override
	{
		m_playerFireProjectile = getGameObjectByName("player")->getGameComponent<FireProjectile>();
		m_dialogueBox = getGameObjectByName("DialogueBox")->getGameComponent<DialogueBox>();
		missileText = getParent()->getGUIComponent<GUILabel>();
	}

	virtual void processInput(const InputManager& input, float delta) override
	{
		if (input.PadButtonPress(SDL_CONTROLLER_BUTTON_B))
		{
			missileText->setText(std::to_string(m_playerFireProjectile->getMissileCount()));
			if (m_playerFireProjectile->getMissileCount() == 0)
			{
				m_dialogueBox->sendMessage("Message From [colour='FFFFFF00']Terra 1 :\n[colour='FFFF0000']Our systems indicate your[colour='FF00FF00']MISSILE[colour='FFFF0000']\nreserves are[colour='FF0000FF']dangerously empty[colour='FF0000FF']!!!", Importance::HIGH, false);
			}
		}
	}

private:
	FireProjectile* m_playerFireProjectile;
	DialogueBox * m_dialogueBox;
	GUILabel* missileText;
};