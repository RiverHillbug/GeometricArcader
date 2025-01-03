#include "PPGATransform.h"
#include "Component.h"
#include "GameObject.h"
#include "Renderer.h"

PPGATransform::PPGATransform(Fluffy::GameObject* pOwner, const ThreeBlade& position)
	: Fluffy::Component(pOwner)
	, m_Position{ position }
{
	UpdateGameObjectTransform();
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
