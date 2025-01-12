#include "Pillar.h"
#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"

Pillar::Pillar(Fluffy::GameObject* pOwner, std::string defaultSpritePath, std::string highlightedSpritePath)
	: Fluffy::Component(pOwner)
	, m_DefaultSpritePath{ defaultSpritePath }
	, m_HighlightedSpritePath{ highlightedSpritePath }
{
	m_pOwnerSpriteHighlight = pOwner->AddComponent<Fluffy::Sprite>(highlightedSpritePath);
	m_pOwnerSpriteDefault = pOwner->AddComponent<Fluffy::Sprite>(defaultSpritePath);
	m_pOwnerSpriteHighlight->SetEnabled(m_IsHighlighted);
}

void Pillar::SetHighlightActive(bool active)
{
	m_IsHighlighted = active;
	m_pOwnerSpriteHighlight->SetEnabled(active);
}
