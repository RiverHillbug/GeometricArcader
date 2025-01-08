#pragma once
#include "FluffyEngine.h"
#include "Command.h"
#include "PPGAPlayerMovement.h"


class SpeedUpCommand final : public Fluffy::Command
{
public:
	SpeedUpCommand(PPGAPlayerMovement* pOwnerMovement)
		: m_pOwnerMovement{ pOwnerMovement }
	{
	}
	~SpeedUpCommand() = default;

	SpeedUpCommand(const SpeedUpCommand& other) = default;
	SpeedUpCommand& operator=(const SpeedUpCommand& other) = default;
	SpeedUpCommand(SpeedUpCommand&& other) = default;
	SpeedUpCommand& operator=(SpeedUpCommand&& other) = default;

	void Execute()
	{
		m_pOwnerMovement->SpeedUp();
	}

private:
	PPGAPlayerMovement* m_pOwnerMovement;
};
