#pragma once
#include "FluffyEngine.h"
#include <Component.h>
#include "Sprite.h"
#include <FlyFish.h>

namespace Fluffy
{
	class GameObject;
	class Sprite;
}

class Pillar : public Fluffy::Component
{
public:
	Pillar(Fluffy::GameObject* pOwner, std::string defaultSpritePath, std::string highlightedSpritePath);
	~Pillar() = default;

	Pillar(const Pillar& other) = default;
	Pillar& operator=(const Pillar& other) = default;
	Pillar(Pillar&& other) = default;
	Pillar& operator=(Pillar&& other) = default;

	void SetHighlightActive(bool active);

private:
	bool m_IsHighlighted{ false };

	std::string m_DefaultSpritePath;
	std::string m_HighlightedSpritePath;
	Fluffy::Sprite* m_pOwnerSpriteDefault;
	Fluffy::Sprite* m_pOwnerSpriteHighlight;
};
