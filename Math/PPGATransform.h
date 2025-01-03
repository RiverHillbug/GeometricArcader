#pragma once
#include "Component.h"
#include "FlyFish.h"

namespace Fluffy
{
	class GameObject;
	class Sprite;
}

class PPGATransform final : public Fluffy::Component
{
public:
	PPGATransform(Fluffy::GameObject* pOwner, const ThreeBlade& position);
	void Update(const float) override;
	void Translate(ThreeBlade translation);
	inline const ThreeBlade& GetPosition() const { return m_Position; }
	void SetPosition(const ThreeBlade& position);

private:
	ThreeBlade m_Position;
	ThreeBlade m_MaxEnergy{ 0.0f, 0.0f, 100.0f };

	ThreeBlade m_MaxEnergyColor{ 0.0f,255.0f, 0.0f };
	ThreeBlade m_MinEnergyColor{ 255.0f,0.0f, 0.0f };
	Fluffy::Sprite* m_pOwnerSprite;

	void UpdateGameObjectTransform();
	void UpdateSpriteColor();
};
