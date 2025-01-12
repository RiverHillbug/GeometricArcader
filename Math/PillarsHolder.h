#pragma once
#include "Singleton.h"
#include "Pillar.h"
#include "PPGATransform.h"
#include "GameObject.h"
#include <vector>

class PillarsHolder final : public Fluffy::Singleton<PillarsHolder>
{
	friend Fluffy::Singleton<PillarsHolder>;

public:
	~PillarsHolder() = default;
	inline void Add(Pillar* pPillar) { m_PillarsInScene.push_back(pPillar); }
	inline const std::vector<Pillar*>& GetAllPillarsInScene() const { return m_PillarsInScene; }
	inline PPGATransform* GetSelectedPillar() const { return m_IsSelectionActive ? m_PillarsInScene[m_SelectedPillarIndex]->GetGameObject()->GetComponent<PPGATransform>() : nullptr; }
	void CyclePillarSelection()
	{
		m_PillarsInScene[m_SelectedPillarIndex]->SetHighlightActive(false);

		if (++m_SelectedPillarIndex == m_PillarsInScene.size())
			m_SelectedPillarIndex = 0;

		m_PillarsInScene[m_SelectedPillarIndex]->SetHighlightActive(m_IsSelectionActive);
	}

	void TogglePillarSelection()
	{
		m_IsSelectionActive = !m_IsSelectionActive;
		m_PillarsInScene[m_SelectedPillarIndex]->SetHighlightActive(m_IsSelectionActive);
	}

private:
	PillarsHolder() = default;
	std::vector<Pillar*> m_PillarsInScene;
	int m_SelectedPillarIndex{ 0 };
	bool m_IsSelectionActive{ false };
};
