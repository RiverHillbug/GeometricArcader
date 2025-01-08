#include "PPGATransform.h"
#include "Component.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Sprite.h"
#include "LevelBounds.h"

PPGATransform::PPGATransform(Fluffy::GameObject* pOwner, const ThreeBlade& position, bool isPlayerTransform = false)
	: Fluffy::Component(pOwner)
	, m_Position{ position }
	, m_IsPlayerTransform{ isPlayerTransform }
{
	if (m_IsPlayerTransform)
	{
		m_pOwnerSprite = m_pOwner->GetComponent<Fluffy::Sprite>();
		UpdatePlayerSpriteColor();
	}

	UpdateGameObjectTransform();
}

void PPGATransform::Update(const float)
{
}

void PPGATransform::Translate(ThreeBlade translation)
{
	m_Position += translation;

	if (m_IsPlayerTransform)
	{
		if (m_Position[2] >= m_PlayerMaxEnergy[2])
			m_Position[2] = m_PlayerMaxEnergy[2];
		UpdatePlayerSpriteColor();
	}

	UpdateGameObjectTransform();
}

void PPGATransform::SetPosition(const ThreeBlade& position)
{
	m_Position = position;
	UpdateGameObjectTransform();
}

void PPGATransform::UpdateGameObjectTransform()
{
	const float offset { Fluffy::Renderer::GetWindowSize().y };
	m_pOwner->SetLocalPosition(m_Position[0], offset - m_Position[1]);	// Because our origin is at bottom left, not top
}

void PPGATransform::UpdatePlayerSpriteColor()
{
	ThreeBlade color;

	color[0] = std::lerp(m_PlayerMaxEnergyColor[0], m_PlayerMinEnergyColor[0], ((m_PlayerMaxEnergy[2] - m_Position[2]) / m_PlayerMaxEnergy[2]));
	color[1] = std::lerp(m_PlayerMinEnergyColor[0], m_PlayerMaxEnergyColor[0], ((m_PlayerMaxEnergy[2] - m_Position[2]) / m_PlayerMaxEnergy[2]));

	m_pOwnerSprite->SetColor(glm::vec3(color[0], color[1], color[2]));
}
