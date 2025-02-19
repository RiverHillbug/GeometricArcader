#pragma once
#include <SDL.h>
#include <glm/glm.hpp>
#include "Singleton.h"
#include "FluffyEngine.h"

class Texture2D;

namespace Fluffy
{
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* pWindow);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y, const float rotationAngle = 0.0f) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, const float rotationAngle = 0.0f) const;
		void RenderTexture(const Texture2D& texture, const struct Rectf& source, const float x, const float y, const float rotationAngle = 0.0f) const;

		SDL_Renderer* GetSDLRenderer() const;

		inline const SDL_Color& GetBackgroundColor() const { return m_ClearColor; }
		inline static const glm::vec2 GetWindowSize() { return glm::vec2{ g_ScreenWidth, g_ScreenHeight }; }
		inline void SetBackgroundColor(const SDL_Color& color) { m_ClearColor = color; }

	private:
		struct SDL_Renderer* m_pRenderer{};
		struct SDL_Window* m_pWindow{};
		SDL_Color m_ClearColor{};
	};
}
