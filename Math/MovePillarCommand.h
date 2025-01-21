#pragma once
#include "FluffyEngine.h"
#include "Command.h"
#include "FluffyTime.h"
#include "PillarsHolder.h"
#include "PPGATransform.h"


class MovePillarCommand final : public Fluffy::Command
{
public:
	MovePillarCommand(const Motor& velocity)
		: m_Velocity{ velocity }
	{
	}
	~MovePillarCommand() = default;

	MovePillarCommand(const MovePillarCommand& other) = default;
	MovePillarCommand& operator=(const MovePillarCommand& other) = default;
	MovePillarCommand(MovePillarCommand&& other) = default;
	MovePillarCommand& operator=(MovePillarCommand&& other) = default;

	void Execute()
	{
		PPGATransform* pillar{ PillarsHolder::GetInstance().GetSelectedPillar() };
		if (pillar == nullptr)
			return;

		Motor movementThisFrame{ m_Velocity * Fluffy::FluffyTime::DeltaTime() };
		movementThisFrame[0] = 1.0f;	// norm is still 1
		const ThreeBlade newTransform{ (movementThisFrame * pillar->GetPosition() * ~movementThisFrame).Grade3() };	// make sandwich
		pillar->SetPosition(newTransform);
	}

private:
	Motor m_Velocity;
};
