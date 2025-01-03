#include "PPGATransform.h"
#include "Component.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Sprite.h"

PPGATransform::PPGATransform(Fluffy::GameObject* pOwner, const ThreeBlade& position)
	: Fluffy::Component(pOwner)
	, m_Position{ position }
{
	m_pOwnerSprite = m_pOwner->GetComponent<Fluffy::Sprite>();
	UpdateGameObjectTransform();
	UpdateSpriteColor();
}

void PPGATransform::Update(const float)
{
}

void PPGATransform::Translate(ThreeBlade translation)
{
	m_Position += translation;

	if (m_Position[2] >= m_MaxEnergy[2])
		m_Position[2] = m_MaxEnergy[2];

	UpdateGameObjectTransform();
	UpdateSpriteColor();
}

void PPGATransform::SetPosition(const ThreeBlade& position)
{
	m_Position = position;
}

void PPGATransform::UpdateGameObjectTransform()
{
	const float offset { Fluffy::Renderer::GetWindowSize().y };
	m_pOwner->SetLocalPosition(m_Position[0], offset - m_Position[1]);	// Because our origin is at bottom left, not top
}

void PPGATransform::UpdateSpriteColor()
{
	ThreeBlade color;

	color[0] = std::lerp(m_MaxEnergyColor[0], m_MinEnergyColor[0], ((m_MaxEnergy[2] - m_Position[2]) / m_MaxEnergy[2]));
	color[1] = std::lerp(m_MinEnergyColor[0], m_MaxEnergyColor[0], ((m_MaxEnergy[2] - m_Position[2]) / m_MaxEnergy[2]));

	m_pOwnerSprite->SetColor(glm::vec3(color[0], color[1], color[2]));
}
