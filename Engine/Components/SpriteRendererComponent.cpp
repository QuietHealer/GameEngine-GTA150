#include "pch.h"
#include "SpriteRendererComponent.h"
#include "Actor.h"
#include "ResourceManager.h"
#include "Engine.h"

namespace nu
{
	FACTORY_REGISTER(SpriteRendererComponent)

	void SpriteRendererComponent::Draw(const Renderer& renderer)
	{
		renderer.DrawTexture(*m_texture, GetOwner()->GetTransform().position.x, GetOwner()->GetTransform().position.y, GetOwner()->GetTransform().rotation, GetOwner()->GetTransform().scale);

	}

	void SpriteRendererComponent::Read(const json::value_t& value)
	{
		Object::Read(value);
	}
}
