#pragma once
#include <iostream>
#include "FluffyEngine.h"
#include "Command.h"


class SpeedUpCommand final : public Fluffy::Command
{
public:
	SpeedUpCommand() = default;
	~SpeedUpCommand() = default;

	SpeedUpCommand(const SpeedUpCommand& other) = default;
	SpeedUpCommand& operator=(const SpeedUpCommand& other) = default;
	SpeedUpCommand(SpeedUpCommand&& other) = default;
	SpeedUpCommand& operator=(SpeedUpCommand&& other) = default;

	void Execute()
	{
		std::cout << "Speeding up." << std::endl;
	}
};
