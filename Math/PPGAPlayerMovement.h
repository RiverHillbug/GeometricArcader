#pragma once
#include "Component.h"
#include "FlyFish.h"
#include <glm/glm.hpp>
#include "LevelBounds.h"

namespace Fluffy
{
	class GameObject;
	class Sprite;
}

class PPGAPlayerMovement final : public Fluffy::Component
{
public:
	PPGAPlayerMovement(Fluffy::GameObject* pOwner, class PPGATransform* pOwnerTransform, float defaultSpeed, float fastSpeed, TwoBlade defaultDirection, TwoBlade fastDirection, LevelBounds levelBounds);
	~PPGAPlayerMovement() = default;
	void Update(const float deltaTime);
	void ToggleSpeedUp();
	void ToggleRotation();
	inline TwoBlade GetCurrentDirection() { return m_CurrentDirection; }

private:
	bool m_IsRotatingAroundPillar{ false };

	float m_DefaultSpeed;
	float m_FastSpeed;
	float m_CurrentSpeed;

	TwoBlade m_DefaultDirection;
	TwoBlade m_FastMoveDirection;
	TwoBlade m_CurrentDirection;

	Motor m_CurrentVelocity;

	Motor m_Rotation;
	ThreeBlade m_RotationCenter;
	float m_RotationFrequency{ 0.1f };

	class PPGATransform* m_pOwnerTransform;
	ThreeBlade m_PreviousPosition{};
	LevelBounds m_LevelBounds;

	OneBlade m_PreviousCollision{};

	Fluffy::Sprite* m_pOwnerSprite1{ nullptr };
	Fluffy::Sprite* m_pOwnerSprite2{ nullptr };
	glm::vec2 m_OwnerSpriteSize{};

	void CalculateRotationAngle();
};
