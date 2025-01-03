#pragma once
#include "Component.h"
#include "../3rdParty/FlyFish/FlyFish.h"

class PPGATransform final : public Fluffy::Component
{
public:
	PPGATransform(class Fluffy::GameObject* pOwner, const ThreeBlade& position);
	void Update(const float) override;
	void SetPosition(const ThreeBlade& position);

private:
	ThreeBlade m_Position;
	void UpdateGameObjectTransform();
};

