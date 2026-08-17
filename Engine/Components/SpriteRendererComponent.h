#pragma once
#include "RendererComponent.h"
#include "Engine.h"

namespace nu
{
	class SpriteRendererComponent : public RendererComponent
	{
	public:
		CLASS_PROTOTYPE(SpriteRendererComponent)

		void Draw(const Renderer& renderer) override;

		virtual void Read(const json::value_t& value) override;

	private:
		Texture* m_texture{ nullptr };
	};
}