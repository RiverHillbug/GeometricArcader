#include "Mouse.h"
#include "Command.h"
#include <functional>
#include <algorithm>
#include <iostream>
#include <stdint.h>

void Fluffy::Mouse::HandleInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{

		case SDL_MOUSEBUTTONUP:
			for (const auto& binding : m_Bindings)
			{
				if (binding.first.button == e.button.button && binding.first.inputState == InputState::Released)
				{
					binding.second->Execute();
				}
			}
		}
	}
}

void Fluffy::Mouse::AddCommand(MouseInput input, std::unique_ptr<class Command> command)
{
	m_Bindings.insert({ input, std::move(command) });

}
