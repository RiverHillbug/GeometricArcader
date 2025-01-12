#pragma once
#include "Component.h"
#include "FlyFish.h"

namespace Fluffy
{
	class GameObject;
}

class PPGAPillarMovement final : public Fluffy::Component
{
public:
	PPGAPillarMovement(Fluffy::GameObject* pOwner, class PPGATransform* pOwnerTransform, const ThreeBlade& velocity);
	~PPGAPillarMovement() = default;
	void Update(const float deltaTime);

private:
	ThreeBlade m_Velocity;
	class PPGATransform* m_pOwnerTransform;
};
