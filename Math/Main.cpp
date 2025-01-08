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
#include "Scene.h"
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Keyboard.h"
#include "ToggleSoundCommand.h"
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"
#include "SoundManager.h"
#include "SpeedUpCommand.h"
#include "PPGATransform.h"
#include "PPGAPlayerMovement.h"
#include <FlyFish.h>
#include "TogglePlayerRotationCommand.h"
#include "Pillar.h"
#include "PillarsHolder.h"
#include "Renderer.h"
#include "LevelBounds.h"

using namespace Fluffy;

static void CreateScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene("MainScene");

	const glm::vec2 windowSize{ Fluffy::Renderer::GetInstance().GetWindowSize() };
	OneBlade top{ windowSize.y, 0.0f, -1.0f, 0.0f };
	OneBlade bottom{ 0.0f, 0.0f, 1.0f, 0.0f };
	OneBlade left{ 0.0f, 1.0f, 0.0f, 0.0f };
	OneBlade right{ windowSize.x, -1.0f, 0.0f, 0.0f };

	LevelBounds pLevelBounds{ top, bottom, left, right };

	std::unique_ptr<GameObject> m_pPlayer = std::make_unique<GameObject>();
	m_pPlayer->AddComponent<Sprite>("star.png");
	PPGATransform* const pPlayerTransform{ m_pPlayer->AddComponent<PPGATransform>(ThreeBlade(100.0f, 100.0f, 100.0f), true) };
	const ThreeBlade defaultVelocity{ ThreeBlade(50.0f, 0.0f, 10.0f) };
	const ThreeBlade maxVelocity{ ThreeBlade(100.0f, 0.0f, -50.0f) };
	const float speed{ 100.0f };
	const Motor velocity{ Motor::Translation(speed, TwoBlade(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f)) };
	PPGAPlayerMovement* const pPlayerMovementComponent { m_pPlayer->AddComponent<PPGAPlayerMovement>(pPlayerTransform, defaultVelocity, maxVelocity, velocity, pLevelBounds) };
	scene.Add(std::move(m_pPlayer));

	std::unique_ptr<GameObject> m_pPillar1 = std::make_unique<GameObject>();
	m_pPillar1->AddComponent<Pillar>("PillarDefault.png", "PillarHighlighted.png");
	PPGATransform* const pPillar1Transform{ m_pPillar1->AddComponent<PPGATransform>(ThreeBlade(280.0f, 200.0f, 50.0f), false) };
	PillarsHolder::GetInstance().Add(pPillar1Transform);
	scene.Add(std::move(m_pPillar1));

	//------- Inputs -------//
	std::unique_ptr<Keyboard> keyboard = std::make_unique<Keyboard>();

	const KeyboardInput k_S{ SDL_SCANCODE_S, InputState::Pressed };
	keyboard->AddCommand(k_S, std::make_unique<SpeedUpCommand>(pPlayerMovementComponent));
	
	const KeyboardInput k_R{ SDL_SCANCODE_R, InputState::Pressed };
	keyboard->AddCommand(k_R, std::make_unique<TogglePlayerRotationCommand>(pPlayerMovementComponent));

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
