#pragma once
#include "FluffyEngine.h"
#include <Component.h>
#include "Sprite.h"

class PlayerCharacter : public Fluffy::Component
{
public:
	PlayerCharacter();
	~PlayerCharacter();

	PlayerCharacter(const PlayerCharacter& other) = default;
	PlayerCharacter& operator=(const PlayerCharacter& other) = default;
	PlayerCharacter(PlayerCharacter&& other) = default;
	PlayerCharacter& operator=(PlayerCharacter&& other) = default;


private:
	
};
