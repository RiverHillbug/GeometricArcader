#pragma once
#include "Component.h"
#include "FlyFish.h"
#include <glm/glm.hpp>
#include "LevelBounds.h"

namespace Fluffy
{
	class GameObject;
}

class PPGAPlayerMovement final : public Fluffy::Component
{
public:
	PPGAPlayerMovement(Fluffy::GameObject* pOwner, class PPGATransform* pOwnerTransform, const ThreeBlade& defaultVelocity, const ThreeBlade& maxVelocity, const Motor& velocity, LevelBounds levelBounds);
	~PPGAPlayerMovement() = default;
	void Update(const float deltaTime);
	void SpeedUp();
	void ToggleRotation();

private:
	bool m_IsRotatingAroundPillar{ false };

	ThreeBlade m_DefaultVelocity;
	ThreeBlade m_MaxVelocity;
	ThreeBlade m_CurrentVelocity;
	ThreeBlade m_RotationCenter;

	float m_RotationFrequency{ 0.1f };

	Motor m_Velocity;
	Motor m_Rotation;

	class PPGATransform* m_pOwnerTransform;
	LevelBounds m_LevelBounds;

	glm::vec2 m_OwnerSpriteSize;

	void FindClosestPillar();
};
