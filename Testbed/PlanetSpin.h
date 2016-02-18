#pragma once
#include <Components\GameComponents.h>

class PlanetSpin : public GameComponent
{
public:
	PlanetSpin() { }
	~PlanetSpin() { }

	virtual void update(float delta) override
	{
		m_angle += 0.001f;

		getTransform()->setRotation(glm::angleAxis(m_angle, glm::vec3(0.0f, 0.0f, 1.0f)));


	}

private:
	float m_angle;
	bool goAhead = false;
};