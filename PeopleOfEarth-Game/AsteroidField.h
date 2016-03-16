#pragma once
#include <Components\GameComponents.h>
#include "MegaEngine.h"

class AsteroidField : public GameComponent
{
public:

	AsteroidField() :
		m_aster1("aster1", 0.5f, 4, Texture("Asteroids/Asteroid_A.png"), Texture("Asteroids/Asteroid_NRM.png")),
		m_aster2("aster2", 0.5f, 4, Texture("Asteroids/Asteroid_B.png"), Texture("Asteroids/Asteroid_NRM.png")),
		m_aster3("aster3", 0.5f, 4, Texture("Asteroids/Asteroid_C.png"), Texture("Asteroids/Asteroid_NRM.png"))
	{ }

	~AsteroidField() {}

	virtual void onStart() override
	{
		positions[0] = PxVec3(7.0f, 1.0f, -3.5f);
		positions[1] = PxVec3(-7.0f, 1.0f, -3.5f);
		positions[2] = PxVec3(0.0f, 1.0f, -6.0f);
		positions[3] = PxVec3(0.0f, 0.0f, -8.0f);
		positions[4] = PxVec3(15.0f, 1.0f, -3.5f);
		positions[5] = PxVec3(-9.0f, -7.0f, -5.0f);
		positions[6] = PxVec3(4.0f, 6.0f, -16.0f);
		positions[7] = PxVec3(0.0f, 20.0f, -16.0f);

		rotations[0] = PxQuat(ToRadians(45.0f), PxVec3(0.0f, 1.0f, 0.0f).getNormalized());
		rotations[1] = PxQuat(ToRadians(45.0f), PxVec3(0.0f, 0.0f, 1.0f).getNormalized());
		rotations[2] = PxQuat(ToRadians(45.0f), PxVec3(1.0f, 0.0f, 0.0f).getNormalized());
		rotations[3] = PxQuat(ToRadians(45.0f), PxVec3(1.0f, 1.0f, 0.0f).getNormalized());
		rotations[4] = PxQuat(ToRadians(45.0f), PxVec3(0.0f, 1.0f, 1.0f).getNormalized());
		rotations[5] = PxQuat(ToRadians(45.0f), PxVec3(1.0f, 0.0f, 1.0f).getNormalized());
		rotations[6] = PxQuat(ToRadians(180.0f), PxVec3(1.0f, 0.0f, 1.0f).getNormalized());
		rotations[7] = PxQuat(ToRadians(180.0f), PxVec3(1.0f, 1.0f, 0.0f).getNormalized());

		for (int i = 0; i < 8; i++)
		{
			asteroidGroupA[i] = new GameObject("asteroid" + std::to_string(i), positions[i], rotations[i]);
			asteroidGroupA[i]->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_A.obj", 10.0f), Material("aster1")));
		}

		groupA = new GameObject("AsteroidGroupA", *getTransform()->getPosition() + PxVec3(0.0f, 0.0f, 30.0f), *getTransform()->getRotation() + PxQuat(ToRadians(45.0f), PxVec3(0.0f, 0.0f, 1.0f).getNormalized()));
		groupA->addChild(asteroidGroupA[0]);
		groupA->addChild(asteroidGroupA[1]);
		groupA->addChild(asteroidGroupA[2]);
		groupA->addChild(asteroidGroupA[3]);
		groupA->addChild(asteroidGroupA[4]);
		groupA->addChild(asteroidGroupA[5]);
		groupA->addChild(asteroidGroupA[6]);
		groupA->addChild(asteroidGroupA[7]);

		instantiate(groupA);
		// Needs a Collider
		

		for (int i = 0; i < 8; i++)
		{
			asteroidGroupB[i] = new GameObject("asteroid" + std::to_string(i), positions[i], rotations[i]);
			asteroidGroupB[i]->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_B.obj", 10.0f), Material("aster2")));
		}

		groupB = new GameObject("AsteroidGroupB", *getTransform()->getPosition() + PxVec3(30.0f, 0.0f, 30.0f), *getTransform()->getRotation() + PxQuat(ToRadians(45.0f), PxVec3(1.0f, 0.0f, 0.0f).getNormalized()));
		groupB->addChild(asteroidGroupB[0]);
		groupB->addChild(asteroidGroupB[1]);
		groupB->addChild(asteroidGroupB[2]);
		groupB->addChild(asteroidGroupB[3]);
		groupB->addChild(asteroidGroupB[4]);
		groupB->addChild(asteroidGroupB[5]);
		groupB->addChild(asteroidGroupB[6]);
		groupB->addChild(asteroidGroupB[7]);

		instantiate(groupB);
		// needs a collider

		for (int i = 0; i < 8; i++)
		{
			asteroidGroupC[i] = new GameObject("asteroid" + std::to_string(i), positions[i], rotations[i]);
			asteroidGroupC[i]->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_C.obj", 10.0f), Material("aster3")));
		}

		groupC = new GameObject("AsteroidGroupC", *getTransform()->getPosition() + PxVec3(-30.0f, 0.0f, 30.0f));
		groupC->addChild(asteroidGroupC[0]);
		groupC->addChild(asteroidGroupC[1]);
		groupC->addChild(asteroidGroupC[2]);
		groupC->addChild(asteroidGroupC[3]);
		groupC->addChild(asteroidGroupC[4]);
		groupC->addChild(asteroidGroupC[5]);
		groupC->addChild(asteroidGroupC[6]);
		groupC->addChild(asteroidGroupC[7]);

		instantiate(groupC);
		// needs a collider
	}

private:
	GameObject * groupA;
	GameObject * groupB;
	GameObject * groupC;

	GameObject * asteroidGroupA[8];
	GameObject * asteroidGroupB[8];
	GameObject * asteroidGroupC[8];
	PxVec3 positions[8];
	PxQuat rotations[8];
	Material m_aster1;
	Material m_aster2;
	Material m_aster3;
};