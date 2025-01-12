#pragma once
#include "BaseInputDevice.h"
#include <SDL_scancode.h>
#include <unordered_map>
#include <memory>
#include <sstream>

namespace Fluffy
{
	struct MouseInput
	{
		Uint8 button;
		InputState inputState;

		bool operator!=(const MouseInput& other) const
		{
			return	button != other.button ||
				inputState != other.inputState;
		}

		bool operator==(const MouseInput& other) const
		{
			return !(*this != other);
		}
	};
}

template <>
struct std::hash<Fluffy::MouseInput>
{
	auto operator()(const Fluffy::MouseInput& input) const -> size_t
	{
		std::stringstream hashStr;
		hashStr << unsigned int(input.button) << unsigned int(input.inputState);

		return std::hash<std::string>()(hashStr.str());
	}
};

namespace Fluffy
{
	class Mouse final : public BaseInputDevice
	{
	public:
		Mouse() = default;
		~Mouse() = default;

		Mouse(const Mouse&) = delete;
		Mouse(Mouse&&) = delete;
		Mouse& operator=(const Mouse&) = delete;
		Mouse& operator=(Mouse&&) = delete;

		void Update() override {};

		bool IsPressed(unsigned int) override {};
		bool IsReleased(unsigned int) override {};
		bool IsHeld(unsigned int) override {};

		void HandleInput() override;

		void AddCommand(MouseInput input, std::unique_ptr<class Command> command);

	private:
		std::vector<uint32_t> m_PressedButtons;
		std::vector<uint32_t> m_ReleasedButtons;
		std::vector<uint32_t> m_PreviousButtons;

		std::unordered_map<MouseInput, std::unique_ptr<class Command>> m_Bindings;
	};
}
