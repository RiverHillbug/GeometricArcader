#include "Pillar.h"
#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"

Pillar::Pillar(Fluffy::GameObject* pOwner, std::string defaultSpritePath, std::string highlightedSpritePath)
	: Fluffy::Component(pOwner)
	, m_DefaultSpritePath{ defaultSpritePath }
	, m_HighlightedSpritePath{ highlightedSpritePath }
{
	m_pOwnerSpriteDefault = pOwner->AddComponent<Fluffy::Sprite>(defaultSpritePath);
	m_pOwnerSpriteDefault->SetEnabled(!m_IsHighlighted);
	m_pOwnerSpriteHighlight = pOwner->AddComponent<Fluffy::Sprite>(highlightedSpritePath);
	m_pOwnerSpriteHighlight->SetEnabled(m_IsHighlighted);
}

void Pillar::ToggleHighlight()
{
	m_IsHighlighted = !m_IsHighlighted;
	m_pOwnerSpriteDefault->SetEnabled(!m_IsHighlighted);
	m_pOwnerSpriteHighlight->SetEnabled(m_IsHighlighted);
}
