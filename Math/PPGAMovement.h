#pragma once
#include "Component.h"
#include "FlyFish.h"

class PPGAMovement final : public Fluffy::Component
{
public:
	PPGAMovement(class Fluffy::GameObject* pOwner, class PPGATransform* pOwnerTransform, const ThreeBlade& defaultVelocity, const ThreeBlade& maxVelocity);
	~PPGAMovement() = default;
	void Update(const float deltaTime);
	void SpeedUp();

private:
	ThreeBlade m_DefaultVelocity;
	ThreeBlade m_MaxVelocity;
	ThreeBlade m_CurrentVelocity;
	class PPGATransform* m_pOwnerTransform;
};
