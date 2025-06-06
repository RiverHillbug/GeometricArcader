#pragma once
#include "FluffyEngine.h"
#include "Command.h"
#include "PPGAPlayerMovement.h"
#include "PillarsHolder.h"

class TogglePlayerRotationCommand final : public Fluffy::Command
{
public:
	TogglePlayerRotationCommand(PPGAPlayerMovement* pOwnerMovement)
		: m_pOwnerMovement{ pOwnerMovement }
	{
	}
	~TogglePlayerRotationCommand() = default;

	TogglePlayerRotationCommand(const TogglePlayerRotationCommand& other) = default;
	TogglePlayerRotationCommand& operator=(const TogglePlayerRotationCommand& other) = default;
	TogglePlayerRotationCommand(TogglePlayerRotationCommand&& other) = default;
	TogglePlayerRotationCommand& operator=(TogglePlayerRotationCommand&& other) = default;

	void Execute()
	{
		m_pOwnerMovement->ToggleRotation();
		PillarsHolder::GetInstance().TogglePillarSelection();
	}

private:
	PPGAPlayerMovement* m_pOwnerMovement;
};

