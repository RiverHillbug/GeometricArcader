#include "PPGAPlayerMovement.h"
#include "PPGATransform.h"
#include <GameObject.h>
#include "PillarsHolder.h"
#include <algorithm>
#include "Pillar.h"
#include <FlyFish.h>
#include <Sprite.h>
#include <iostream>

PPGAPlayerMovement::PPGAPlayerMovement(Fluffy::GameObject* pOwner, PPGATransform* pOwnerTransform, float defaultSpeed, float fastSpeed, TwoBlade defaultDirection, TwoBlade fastMoveDirection, LevelBounds levelBounds)
	: Fluffy::Component(pOwner)
	, m_pOwnerTransform{ pOwnerTransform }
	, m_DefaultSpeed{ defaultSpeed }
	, m_FastSpeed{ fastSpeed }
	, m_DefaultDirection{ defaultDirection }
	, m_FastMoveDirection{ fastMoveDirection }
	, m_LevelBounds{ levelBounds }
{
	m_OwnerSpriteSize = m_pOwner->GetComponent<Fluffy::Sprite>()->GetTextureSize();
	m_CurrentVelocity = Motor::Translation(defaultSpeed, defaultDirection);
	m_CurrentSpeed = defaultSpeed;
	m_CurrentDirection = defaultDirection;
}

void PPGAPlayerMovement::Update(const float deltaTime)
{
	if (m_IsRotatingAroundPillar)
	{
		m_RotationCenter = PillarsHolder::GetInstance().GetSelectedPillar()->GetPosition();

		// Off-origin rotation: Translation * Rotation * ~Translation

		Motor rotation{ Motor::Rotation(m_RotationFrequency * 360 * deltaTime, TwoBlade(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)) };
		Motor translation{ Motor::Translation(-m_RotationCenter.VNorm(), !TwoBlade(m_RotationCenter & ThreeBlade(0.0f, 0.0f, 0.0f))) };
		Motor combined{ translation * rotation * ~translation };
		auto newTransform{ combined * m_pOwnerTransform->GetPosition() * ~combined };
		m_pOwnerTransform->SetPosition(newTransform.Grade3());
	}
	else
	{
		m_CurrentVelocity = Motor::Translation(m_CurrentSpeed, m_CurrentDirection);
		Motor movementThisFrame{ m_CurrentVelocity * deltaTime };
		movementThisFrame[0] = 1.0f;	// norm is still 1
		ThreeBlade newTransform{ (movementThisFrame * m_pOwnerTransform->GetPosition() * ~movementThisFrame).Grade3() };	// make sandwich

		if (newTransform[2] <= 0.0f)
		{
			ToggleSpeedUp();
			newTransform[2] = 0.0f;
		}

		m_pOwnerTransform->SetPosition(newTransform);
	}

	// Haven't decided yet about how the collisions should be handled if player is rotating around an object
	OneBlade collision;
	if (m_LevelBounds.DidCollide(m_pOwnerTransform->GetPosition(), m_OwnerSpriteSize.x, m_OwnerSpriteSize.y, collision))
	{
		const auto newDirection{ collision * m_CurrentDirection * ~collision };
		m_CurrentDirection = newDirection.Grade2();
	}
}

void PPGAPlayerMovement::ToggleSpeedUp()
{
	if (m_pOwnerTransform->GetPosition()[2] > 0.0f && m_CurrentSpeed == m_DefaultSpeed)
	{
		m_CurrentSpeed = m_FastSpeed;
		m_CurrentDirection[2] = -1.0f;
	}
	else
	{
		m_CurrentSpeed = m_DefaultSpeed;
		m_CurrentDirection[2] = 1.0f;
	}
}

void PPGAPlayerMovement::ToggleRotation()
{
	m_IsRotatingAroundPillar = !m_IsRotatingAroundPillar;
}
