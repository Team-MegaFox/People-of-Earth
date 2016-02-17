
#pragma once
#include <Components\GameComponents.h>

class Laser : public GameComponent
{

public:
	
	Laser() : m_lifeTime(3.0f) {}
	~Laser() {}

	virtual void update(float delta) override
	{
		getTransform()->setPosition(
			*getTransform()->getPosition() + 
			Utility::getForward(*getTransform()->getRotation()) * 1.0f);

		m_lifeTime -= delta;
		if (m_lifeTime < 0)
		{
			destroy(getParent());
		}

	}

private:
		
	float m_lifeTime;
};