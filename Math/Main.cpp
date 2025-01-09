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

	std::unique_ptr<GameObject> pBackground = std::make_unique<GameObject>();
	pBackground->AddComponent<Sprite>("space.png", windowSize / 2.0f);
	scene.Add(std::move(pBackground));

	std::unique_ptr<GameObject> pPlayer = std::make_unique<GameObject>();
	pPlayer->AddComponent<Sprite>("player.png");
	PPGATransform* const pPlayerTransform{ pPlayer->AddComponent<PPGATransform>(ThreeBlade(100.0f, 100.0f, 100.0f), true) };
	const ThreeBlade defaultVelocity{ ThreeBlade(50.0f, 0.0f, 10.0f) };
	const ThreeBlade maxVelocity{ ThreeBlade(100.0f, 0.0f, -50.0f) };
	const float speed{ 100.0f };
	const Motor velocity{ Motor::Translation(speed, TwoBlade(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f)) };
	PPGAPlayerMovement* const pPlayerMovementComponent { pPlayer->AddComponent<PPGAPlayerMovement>(pPlayerTransform, defaultVelocity, maxVelocity, velocity, pLevelBounds) };
	scene.Add(std::move(pPlayer));

	std::unique_ptr<GameObject> pPillar1 = std::make_unique<GameObject>();
	pPillar1->AddComponent<Pillar>("planet1.png", "planetHighlight.png");
	PPGATransform* const pPillar1Transform{ pPillar1->AddComponent<PPGATransform>(ThreeBlade(280.0f, 150.0f, 50.0f), false) };
	PillarsHolder::GetInstance().Add(pPillar1Transform);
	scene.Add(std::move(pPillar1));

	std::unique_ptr<GameObject> pPillar2 = std::make_unique<GameObject>();
	pPillar2->AddComponent<Pillar>("planet2.png", "planetHighlight.png");
	PPGATransform* const pPillar2Transform{ pPillar2->AddComponent<PPGATransform>(ThreeBlade(430.0f, 300.0f, 0.0f), false) };
	PillarsHolder::GetInstance().Add(pPillar2Transform);
	scene.Add(std::move(pPillar2));

	std::unique_ptr<GameObject> pPillar3 = std::make_unique<GameObject>();
	pPillar3->AddComponent<Pillar>("planet3.png", "planetHighlight.png");
	PPGATransform* const pPillar3Transform{ pPillar3->AddComponent<PPGATransform>(ThreeBlade(100.0f, 350.0f, 0.0f), false) };
	PillarsHolder::GetInstance().Add(pPillar3Transform);
	scene.Add(std::move(pPillar3));

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
