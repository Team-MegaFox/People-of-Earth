#include "GUIOnCamera.h"
#include <Core\Utility.h>

void GUIOnCamera::onStart()
{
	m_mainCamera = getGameObjectByName("camera");
	m_mainCameraComponent = m_mainCamera->getGameComponent<CameraComponent>();

	m_top = getGameObjectByName("top");
	m_bottom = getGameObjectByName("bottom");
	m_right = getGameObjectByName("right");
	m_left = getGameObjectByName("left");

	m_topRight = getGameObjectByName("top right");
	m_topLeft = getGameObjectByName("top left");
	m_bottomRight = getGameObjectByName("bottom right");
	m_bottomLeft = getGameObjectByName("bottom left");

	PxVec3 screen = m_mainCameraComponent->worldToScreenPoint(*m_bottom->getTransform()->getPosition());

	m_image = new GUIImage(PxVec4(0.0f, 0.0f, 0.2f, 0.2f), PxVec4(screen, 0.0f), "Textures/MegaFox.png");
	instantiate((new GameObject("GUI test image"))->addGUIComponent(m_image));
}

void GUIOnCamera::update(float delta)
{
	//m_top->getTransform()->setPosition((m_mainCamera->getTransform()->getTransformedPos() + (Utility::getForward(*m_mainCamera->getTransform()->getRotation()).getNormalized() * 10.0f)) + PxVec3(5.0f, 0.0f, 0.0f));
	
	//PxVec3 screen = m_mainCameraComponent->worldToScreenPoint(*m_top->getTransform()->getPosition());
	//m_image->setPixelPosition(PxVec2(screen.x, screen.y));
}
