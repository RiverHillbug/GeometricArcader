#pragma once
#include "Component.h"
#include "FlyFish.h"

class PPGATransform final : public Fluffy::Component
{
public:
	PPGATransform(class Fluffy::GameObject* pOwner, const ThreeBlade& position);
	void Update(const float) override;
	void Translate(ThreeBlade translation);
	inline const ThreeBlade& GetPosition() const { return m_Position; }
	void SetPosition(const ThreeBlade& position);

private:
	ThreeBlade m_Position;
	ThreeBlade m_MaxEnergy{ 0.0f, 0.0f, 100.0f };
	void UpdateGameObjectTransform();
};
