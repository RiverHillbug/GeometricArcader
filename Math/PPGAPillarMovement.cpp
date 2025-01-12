#include "PPGAPillarMovement.h"

PPGAPillarMovement::PPGAPillarMovement(Fluffy::GameObject* pOwner, class PPGATransform* pOwnerTransform, const ThreeBlade& velocity)
	: Fluffy::Component(pOwner)
	, m_pOwnerTransform{ pOwnerTransform }
	, m_Velocity{ velocity }
{
}

void PPGAPillarMovement::Update(const float)
{

}
