#pragma once
#include <Components/GameComponents.h>
#include <Audio/AudioListener.h>
#include <Core/Utility.h>

class Listener : public GameComponent
{
public:
	Listener()
	{
		m_theListener = new AudioListener();
	}
	~Listener()
	{
		delete m_theListener;
	}

	virtual void update(float deltaTime) override
	{
		m_pos = *getTransform()->getPosition();
		m_vel = glm::vec3(0.0f);
		m_forward = Utility::getForward(*getTransform()->getRotation());
		m_up = Utility::getUp(*getTransform()->getRotation());

		m_theListener->setAsListener(m_pos, m_vel, m_forward, m_up);
	}

protected:
	AudioListener * m_theListener;

private:
	GameObject * m_parent;
	glm::vec3 m_pos, m_vel, m_forward, m_up;
};
