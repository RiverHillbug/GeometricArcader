#include "PPGAPlayerMovement.h"
#include "PPGATransform.h"
#include <GameObject.h>
#include "PillarsHolder.h"
#include <algorithm>
#include "Pillar.h"
#include <FlyFish.h>
#include <Sprite.h>
#include <iostream>

PPGAPlayerMovement::PPGAPlayerMovement(Fluffy::GameObject* pOwner, PPGATransform* pOwnerTransform, const ThreeBlade& defaultVelocity, const ThreeBlade& maxVelocity, const Motor& velocity, LevelBounds levelBounds)
	: Fluffy::Component(pOwner)
	, m_pOwnerTransform{ pOwnerTransform }
	, m_DefaultVelocity{ defaultVelocity }
	, m_MaxVelocity{ maxVelocity }
	, m_CurrentVelocity{ defaultVelocity }
	, m_Velocity{ velocity }
	, m_LevelBounds{ levelBounds }
{
	m_OwnerSpriteSize = m_pOwner->GetComponent<Fluffy::Sprite>()->GetTextureSize();
}

void PPGAPlayerMovement::Update(const float deltaTime)
{
	/*if (m_IsRotatingAroundPillar)
		m_pOwnerTransform->Translate(m_CurrentVelocity * deltaTime);
	else
	{
		ThreeBlade translation{ 0.0f, 0.0f, m_CurrentVelocity[2] * deltaTime };
		m_pOwnerTransform->Translate(m_CurrentVelocity * deltaTime);
	}

	if (m_pOwnerTransform->GetPosition()[2] <= 0.0f)
		m_CurrentVelocity = m_DefaultVelocity;*/

	Motor movementThisFrame{ m_Velocity * deltaTime };
	movementThisFrame[0] = 1.0f;	// norm is still 1

	const ThreeBlade newTransform{ (movementThisFrame * m_pOwnerTransform->GetPosition() * ~movementThisFrame).Grade3() };	// make sandwich
	m_pOwnerTransform->SetPosition(newTransform);

	std::cout << "Position: " << newTransform[0] << ", " << newTransform[1] << ", " << newTransform[2] << std::endl;

	OneBlade collision;
	 if (m_LevelBounds.DidCollide(newTransform, m_OwnerSpriteSize.x, m_OwnerSpriteSize.y, collision))
	 {
		 auto temp { collision * m_Velocity * ~collision };

		 //"s", "e01", "e02", "e03", "e23", "e31", "e12", "e0123" ---> Motor
		 Motor newVelocity{ temp[0], temp[5], temp[6] ,temp[7], temp[8], temp[9], temp[10], temp[15] };
		 m_Velocity = newVelocity;
	 }
}

void PPGAPlayerMovement::SpeedUp()
{
	if (m_pOwnerTransform->GetPosition()[2] >= 0.0f)
		m_CurrentVelocity = m_MaxVelocity;
}

void PPGAPlayerMovement::ToggleRotation()
{
	m_IsRotatingAroundPillar = !m_IsRotatingAroundPillar;
	FindClosestPillar();
}

void PPGAPlayerMovement::FindClosestPillar()
{
	const std::vector<PPGATransform*>& pillars{ PillarsHolder::GetInstance().GetAllPillarsInScene() };

	ThreeBlade distanceToClosestPillar{ FLT_MAX, FLT_MAX, 0.0f };
	PPGATransform* pSelectedPillar{ nullptr };

	for (int i{ 0 }; i < pillars.size(); ++i)
	{
		ThreeBlade pillarPosition2D{ pillars[i]->GetPosition()[0], pillars[i]->GetPosition()[1], 0.0f };
		ThreeBlade playerPosition2D{ pillars[i]->GetPosition()[0], pillars[i]->GetPosition()[1], 0.0f };

		ThreeBlade playerToPillarDistance2D{ pillarPosition2D - playerPosition2D };

		if (playerToPillarDistance2D.VNorm() < distanceToClosestPillar.VNorm())
		{
			distanceToClosestPillar = playerToPillarDistance2D;
			pSelectedPillar = pillars[i];
		}
	}
	
	if (pSelectedPillar != nullptr)
	{
		Pillar* pPillar{ pSelectedPillar->GetGameObject()->GetComponent<Pillar>() };
		pPillar->ToggleHighlight();

		m_RotationCenter = pSelectedPillar->GetPosition();
	}
}
