#pragma once
#include "Singleton.h"
#include <vector>

class PillarsHolder final : public Fluffy::Singleton<PillarsHolder>
{
	friend Fluffy::Singleton<PillarsHolder>;

public:
	~PillarsHolder() = default;
	void Add(class PPGATransform* pPillarTransform) { m_PillarsInScene.push_back(pPillarTransform); }
	inline const std::vector<class PPGATransform*>& GetAllPillarsInScene() const { return m_PillarsInScene; }

private:
	PillarsHolder() = default;
	std::vector<class PPGATransform*> m_PillarsInScene;
};
