#include "BaseLight.h"
#include "RenderingEngine.h"
#include "CoreEngine.h"

#define COLOR_DEPTH 256

void BaseLight::addToEngine(CoreEngine * engine) const
{
	engine->getRenderingEngine()->addLight(*this);
}

ShadowCameraTransform BaseLight::calcShadowCameraTransform(const glm::vec3 & mainCameraPos, const glm::quat & mainCameraRot) const
{
	return ShadowCameraTransform(getTransform().getTransformedPos(), getTransform().getTransformedRot());
}
