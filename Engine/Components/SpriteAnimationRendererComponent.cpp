#include "pch.h"
#include "SpriteAnimationRendererComponent.h"
#include "Core/Factory.h"
#include "Resources/ResourceManager.h"
#include "Renderer/TextureFrames.h"
#include "Engine.h"
#include "Math/MathUtils.h"

namespace nu
{
	FACTORY_REGISTER(SpriteAnimationRendererComponent)

		void SpriteAnimationRendererComponent::Start()
	{
		if (!m_textureFramesName.empty())
		{
			m_textureFrames = ResourceManager().Get<TextureFrames>(m_textureFramesName, Engine::Get().GetRenderer());
			if (m_textureFrames)
			{
				m_sourceRect = m_textureFrames->GetFrameRect(0);
				m_size = Vector2{ m_sourceRect.w, m_sourceRect.h };
				m_texture = m_textureFrames->GetTexture();
			}
		}
	}

	void SpriteAnimationRendererComponent::Update(float dt)
	{
		if (!m_textureFrames) return;

		m_frameTimer += dt;

		float frameTime = 1.0f / m_framesPerSecond;
		while (m_frameTimer >= frameTime)
		{
			m_frame++;
			if (m_loop)
			{
				m_frame = Wrap(0u, m_textureFrames->GetTotalFrames(), m_frame);
			}
			else
			{
				m_frame = Clamp(0u, m_textureFrames->GetTotalFrames() - 1, m_frame);
			}

			m_frameTimer -= frameTime;
		}
		m_sourceRect = m_textureFrames->GetFrameRect(m_frame);
	}


	void SpriteAnimationRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);

		JSON_READ_NAME_REQ(value, "frames_per_second", m_framesPerSecond);
		JSON_READ_NAME(value, "loop", m_loop);

		JSON_READ_NAME(value, "texture_frames", m_textureFramesName);
	}
}
