#pragma once
#include "FluffyEngine.h"
#include "Command.h"
#include "PPGAPlayerMovement.h"


class ToggleSpeedUpCommand final : public Fluffy::Command
{
public:
	ToggleSpeedUpCommand(PPGAPlayerMovement* pOwnerMovement)
		: m_pOwnerMovement{ pOwnerMovement }
	{
	}
	~ToggleSpeedUpCommand() = default;

	ToggleSpeedUpCommand(const ToggleSpeedUpCommand& other) = default;
	ToggleSpeedUpCommand& operator=(const ToggleSpeedUpCommand& other) = default;
	ToggleSpeedUpCommand(ToggleSpeedUpCommand&& other) = default;
	ToggleSpeedUpCommand& operator=(ToggleSpeedUpCommand&& other) = default;

	void Execute()
	{
		m_pOwnerMovement->ToggleSpeedUp();
	}

private:
	PPGAPlayerMovement* m_pOwnerMovement;
};
