#include "PPGAPlayerMovement.h"
#include "PPGATransform.h"
#include "Pillar.h"
#include "PillarsHolder.h"
#include <GameObject.h>
#include <Sprite.h>
#include <algorithm>
#include <FlyFish.h>
#include <iostream>

PPGAPlayerMovement::PPGAPlayerMovement(Fluffy::GameObject* pOwner, PPGATransform* pOwnerTransform, float defaultSpeed, float fastSpeed, TwoBlade defaultDirection, TwoBlade fastMoveDirection, LevelBounds levelBounds)
	: Fluffy::Component(pOwner)
	, m_pOwnerTransform{ pOwnerTransform }
	, m_PreviousPosition{ pOwnerTransform->GetPosition() }
	, m_DefaultSpeed{ defaultSpeed }
	, m_FastSpeed{ fastSpeed }
	, m_DefaultDirection{ defaultDirection }
	, m_FastMoveDirection{ fastMoveDirection }
	, m_LevelBounds{ levelBounds }
{
	const auto& sprites{ m_pOwner->GetComponents<Fluffy::Sprite>() };
	if (sprites.size() > 0)
	{
		m_pOwnerSprite1 = sprites[0];
		m_OwnerSpriteSize = m_pOwnerSprite1->GetTextureSize();

		if (sprites.size() > 1)
			m_pOwnerSprite2 = sprites[1];
	}

	m_CurrentVelocity = Motor::Translation(defaultSpeed, defaultDirection);
	m_CurrentSpeed = defaultSpeed;
	m_CurrentDirection = defaultDirection;
}

void PPGAPlayerMovement::Update(const float deltaTime)
{
	m_PreviousPosition = m_pOwnerTransform->GetPosition();

	if (m_IsRotatingAroundPillar)
	{
		m_RotationCenter = PillarsHolder::GetInstance().GetSelectedPillar()->GetPosition();

		// Off-origin rotation: Translation * Rotation * ~Translation
		const Motor& rotation{ Motor::Rotation(m_RotationFrequency * 360.0f * deltaTime, TwoBlade(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)) };
		const Motor& translation{ Motor::Translation(-m_RotationCenter.VNorm(), !TwoBlade(m_RotationCenter & ThreeBlade(0.0f, 0.0f, 0.0f))) };
		const Motor& combined{ translation * rotation * ~translation };
		const MultiVector& newTransform{ combined * m_pOwnerTransform->GetPosition() * ~combined };

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

	CalculateRotationAngle();
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

void PPGAPlayerMovement::CalculateRotationAngle()
{
	const ThreeBlade& currentPosition{ m_pOwnerTransform->GetPosition() };
	const TwoBlade& movementSinceLastFrame{ TwoBlade::LineFromPoints(m_PreviousPosition[0], m_PreviousPosition[1], 1.0f,
																	 currentPosition[0], currentPosition[1], 1.0f) };

	const float angle{ std::atan2(movementSinceLastFrame[1], -movementSinceLastFrame[0]) * (180.0f / 3.1415f) };

	m_pOwnerSprite1->SetRotation(angle);
	m_pOwnerSprite2->SetRotation(angle);
}
