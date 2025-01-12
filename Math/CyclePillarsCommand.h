#pragma once
#include "FluffyEngine.h"
#include "Command.h"
#include "PillarsHolder.h"

class CyclePillarsCommand final : public Fluffy::Command
{
public:
	CyclePillarsCommand() = default;
	~CyclePillarsCommand() = default;

	CyclePillarsCommand(const CyclePillarsCommand& other) = default;
	CyclePillarsCommand& operator=(const CyclePillarsCommand& other) = default;
	CyclePillarsCommand(CyclePillarsCommand&& other) = default;
	CyclePillarsCommand& operator=(CyclePillarsCommand&& other) = default;

	void Execute()
	{
		PillarsHolder::GetInstance().CyclePillarSelection();
	}
};