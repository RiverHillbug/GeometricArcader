#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FluffyEngine.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Text.h"
#include "Scene.h"
#include "GameObject.h"
#include "Sprite.h"
#include "FPSCounter.h"
#include "Rotator.h"
#include "InputManager.h"
#include "Controller.h"
#include "Keyboard.h"
#include "ToggleSoundCommand.h"
#include "CollidersHandler.h"
#include "CollisionLayers.h"
#include "Structs.h"
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"
#include "SoundManager.h"
#include "SpeedUpCommand.h"
#include "PPGATransform.h"
#include "PPGAMovement.h"
#include <FlyFish.h>

using namespace Fluffy;

static void CreateScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene("MainScene");

	std::unique_ptr<GameObject> m_pPlayer = std::make_unique<GameObject>();
	PPGATransform* const pPlayerTransform{ m_pPlayer->AddComponent<PPGATransform>(ThreeBlade(100.0f, 100.0f, 100.0f)) };
	const ThreeBlade defaultVelocity{ ThreeBlade(50.0f, 0.0f, 10.0f) };
	const ThreeBlade maxVelocity{ ThreeBlade(100.0f, 0.0f, -50.0f) };
	PPGAMovement* const pPlayerMovementComponent { m_pPlayer->AddComponent<PPGAMovement>(pPlayerTransform, defaultVelocity, maxVelocity) };
	m_pPlayer->AddComponent<Sprite>("star.png");
	scene.Add(std::move(m_pPlayer));

	std::unique_ptr<Keyboard> keyboard = std::make_unique<Keyboard>();
	const KeyboardInput k_S{ SDL_SCANCODE_S, InputState::Pressed };
	keyboard->AddCommand(k_S, std::make_unique<SpeedUpCommand>(pPlayerMovementComponent));

	auto& input = InputManager::GetInstance();
	input.AddDevice(std::move(keyboard));
}

void load()
{
	CreateScene();
}

int main(int, char* [])
{
	Fluffy::FluffyEngine engine("../Data/");
	engine.Run(load);
	return 0;
}
