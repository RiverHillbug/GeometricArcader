#pragma once
#include <FlyFish.h>

class LevelBounds final
{
public:
	LevelBounds(OneBlade top, OneBlade bottom, OneBlade left, OneBlade right)
		: m_Top{ top }
		, m_Bottom{ bottom }
		, m_Left{ left }
		, m_Right{ right }
	{

	}
	~LevelBounds() = default;

	inline bool DidCollide(const ThreeBlade& position, const float spriteWidth, const float spriteHeight, _In_ OneBlade& collision) const
	{
		if ((position ^ m_Top) - (spriteHeight / 2.0f) <= 0.0f)
		{
			collision = m_Top;
			return true;
		}
		if ((position ^ m_Bottom) - (spriteHeight / 2.0f) <= 0.0f)
		{
			collision = m_Bottom;
			return true;
		}
		if ((position ^ m_Left) - (spriteWidth / 2.0f) <= 0.0f)
		{
			collision = m_Left;
			return true;
		}
		if ((position ^ m_Right) - (spriteWidth / 2.0f) <= 0.0f)
		{
			collision = m_Right;
			return true;
		}

		return false;
	}

private:
	OneBlade m_Top;
	OneBlade m_Bottom;
	OneBlade m_Left;
	OneBlade m_Right;
};

