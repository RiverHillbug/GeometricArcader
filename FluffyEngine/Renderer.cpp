#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "Rectf.h"

namespace Fluffy
{
	static int GetOpenGLDriverIndex()
	{
		auto openglIndex = -1;
		const auto driverCount = SDL_GetNumRenderDrivers();
		for (auto i = 0; i < driverCount; i++)
		{
			SDL_RendererInfo info;
			if (!SDL_GetRenderDriverInfo(i, &info))
				if (strcmp(info.name, "opengl") == 0)
					openglIndex = i;
		}
		return openglIndex;
	}

	void Renderer::Init(SDL_Window* window)
	{
		m_pWindow = window;
		m_pRenderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
		if (m_pRenderer == nullptr)
		{
			throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
		}
	}

	void Renderer::Render() const
	{
		const auto& color = GetBackgroundColor();
		SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a);
		SDL_RenderClear(m_pRenderer);

		SceneManager::GetInstance().Render();

		SDL_RenderPresent(m_pRenderer);
	}

	void Renderer::Destroy()
	{
		if (m_pRenderer != nullptr)
		{
			SDL_DestroyRenderer(m_pRenderer);
			m_pRenderer = nullptr;
		}
	}

	void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float rotationAngle /*= 0.0f*/) const
	{
		SDL_Rect dst{};
		dst.x = static_cast<int>(x);
		dst.y = static_cast<int>(y);
		SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, rotationAngle, nullptr, SDL_FLIP_NONE);
	}

	void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, const float rotationAngle /*= 0.0f*/) const
	{
		SDL_Rect dst{};
		dst.x = static_cast<int>(x);
		dst.y = static_cast<int>(y);
		dst.w = static_cast<int>(width);
		dst.h = static_cast<int>(height);
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, rotationAngle, nullptr, SDL_FLIP_NONE);
	}

	void Renderer::RenderTexture(const Texture2D& texture, const Rectf& source, const float x, const float y, const float rotationAngle /*= 0.0f*/) const
	{
		const SDL_Rect src
		{
			static_cast<int>(source.left),
			static_cast<int>(source.top),
			static_cast<int>(source.width),
			static_cast<int>(source.height),
		};

		SDL_Rect dst{};
		dst.x = static_cast<int>(x);
		dst.y = static_cast<int>(y);
		dst.w = static_cast<int>(source.width);
		dst.h = static_cast<int>(source.height);

		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, rotationAngle, nullptr, SDL_FLIP_NONE);
	}

	SDL_Renderer* Renderer::GetSDLRenderer() const { return m_pRenderer; }
}
