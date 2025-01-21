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
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"
#include "ToggleSpeedUpCommand.h"
#include "PPGATransform.h"
#include "PPGAPlayerMovement.h"
#include <FlyFish.h>
#include "TogglePlayerRotationCommand.h"
#include "Pillar.h"
#include "PillarsHolder.h"
#include "Renderer.h"
#include "LevelBounds.h"
#include "MovePillarCommand.h"
#include "CyclePillarsCommand.h"

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
	pPlayer->AddComponent<Sprite>("playerHighlight1.png");
	pPlayer->AddComponent<Sprite>("player1.png");
	PPGATransform* const pPlayerTransform{ pPlayer->AddComponent<PPGATransform>(ThreeBlade(100.0f, 100.0f, 100.0f), true) };
	const float defaultSpeed{ 100.0f };
	const float maxSpeed{ 250.0f };
	const TwoBlade defaultMoveDirection{ 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f };
	const TwoBlade fastMoveDirection{ 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f };
	PPGAPlayerMovement* const pPlayerMovementComponent { pPlayer->AddComponent<PPGAPlayerMovement>(pPlayerTransform, defaultSpeed, maxSpeed, defaultMoveDirection, fastMoveDirection, pLevelBounds) };
	scene.Add(std::move(pPlayer));

	//------- Pillars -------//
	std::unique_ptr<GameObject> pPillar1 = std::make_unique<GameObject>();
	Pillar* const pPillar1Pillar{ pPillar1->AddComponent<Pillar>("planet1.png", "planetHighlight.png") };
	pPillar1->AddComponent<PPGATransform>(ThreeBlade(280.0f, 150.0f, 50.0f), false);
	PillarsHolder::GetInstance().Add(pPillar1Pillar);
	scene.Add(std::move(pPillar1));

	std::unique_ptr<GameObject> pPillar2 = std::make_unique<GameObject>();
	Pillar* const pPillar2Pillar{ pPillar2->AddComponent<Pillar>("planet2.png", "planetHighlight2.png") };
	pPillar2->AddComponent<PPGATransform>(ThreeBlade(430.0f, 300.0f, 0.0f), false);
	PillarsHolder::GetInstance().Add(pPillar2Pillar);
	scene.Add(std::move(pPillar2));

	std::unique_ptr<GameObject> pPillar3 = std::make_unique<GameObject>();
	Pillar* const pPillar3Pillar{ pPillar3->AddComponent<Pillar>("planet3.png", "planetHighlight3.png") };
	pPillar3->AddComponent<PPGATransform>(ThreeBlade(100.0f, 350.0f, 0.0f), false);
	PillarsHolder::GetInstance().Add(pPillar3Pillar);
	scene.Add(std::move(pPillar3));

	//------- Inputs -------//
	std::unique_ptr<Keyboard> keyboard = std::make_unique<Keyboard>();

	const KeyboardInput k_S{ SDL_SCANCODE_S, InputState::Pressed };
	keyboard->AddCommand(k_S, std::make_unique<ToggleSpeedUpCommand>(pPlayerMovementComponent));
	
	const KeyboardInput k_R{ SDL_SCANCODE_R, InputState::Pressed };
	keyboard->AddCommand(k_R, std::make_unique<TogglePlayerRotationCommand>(pPlayerMovementComponent));

	const KeyboardInput k_C{ SDL_SCANCODE_C, InputState::Pressed };
	keyboard->AddCommand(k_C, std::make_unique<CyclePillarsCommand>());

	const KeyboardInput k_Left{ SDL_SCANCODE_LEFT, InputState::Held };
	const Motor& directionLeft{ Motor::Translation(defaultSpeed, TwoBlade(-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)) };
	keyboard->AddCommand(k_Left, std::make_unique<MovePillarCommand>(directionLeft));

	const KeyboardInput k_Right{ SDL_SCANCODE_RIGHT, InputState::Held };
	const Motor& directionRight{ Motor::Translation(defaultSpeed, TwoBlade(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)) };
	keyboard->AddCommand(k_Right, std::make_unique<MovePillarCommand>(directionRight));

	const KeyboardInput k_Up{ SDL_SCANCODE_UP, InputState::Held };
	const Motor& up{ Motor::Translation(defaultSpeed, TwoBlade(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f)) };
	keyboard->AddCommand(k_Up, std::make_unique<MovePillarCommand>(up));

	const KeyboardInput k_Down{ SDL_SCANCODE_DOWN, InputState::Held };
	const Motor& down{ Motor::Translation(defaultSpeed, TwoBlade(0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f)) };
	keyboard->AddCommand(k_Down, std::make_unique<MovePillarCommand>(down));

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
