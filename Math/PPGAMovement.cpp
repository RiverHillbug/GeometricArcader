#include "PPGAMovement.h"
#include "PPGATransform.h"
#include <GameObject.h>

PPGAMovement::PPGAMovement(Fluffy::GameObject* pOwner, PPGATransform* pOwnerTransform, const ThreeBlade& defaultVelocity, const ThreeBlade& maxVelocity)
	: Fluffy::Component(pOwner)
	, m_pOwnerTransform{ pOwnerTransform }
	, m_DefaultVelocity{ defaultVelocity }
	, m_MaxVelocity{ maxVelocity }
	, m_CurrentVelocity{ defaultVelocity }
{
}

void PPGAMovement::Update(const float deltaTime)
{
	m_pOwnerTransform->Translate(m_CurrentVelocity * deltaTime);

	if (m_pOwnerTransform->GetPosition()[2] <= 0.0f)
		m_CurrentVelocity = m_DefaultVelocity;
}

void PPGAMovement::SpeedUp()
{
	if (m_pOwnerTransform->GetPosition()[2] >= 0.0f)
		m_CurrentVelocity = m_MaxVelocity;
}
