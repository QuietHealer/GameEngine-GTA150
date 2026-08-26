#include "pch.h"
#include "TextureFrames.h"
#include "Serialization/Json.h"
#include "Texture.h"

namespace nu
{
	bool TextureFrames::Load(const std::string& filename, class Renderer& renderer)
	{
		json::document_t document;

		if (!json::Load(filename, document))
		{

			std::cerr << "";
			return false;
		}

		std::string texture_name;
		JSON_READ(document, texture_name);
		if (texture_name.empty())
		{
			return false;
		}

		m_texture = Resources().Get<Texture>(texture_name, renderer);
		if (!m_texture)
		{
			std::cerr << "";
			return false;
		}

		JSON_READ_NAME(document, "columns", m_numColumns);
		JSON_READ_NAME(document, "rows", m_numRows);
		JSON_READ_NAME(document, "start_frame", m_startFrame);
		JSON_READ_NAME(document, "totalFrames", m_totalFrames);

		if (m_numColumns <= 0 || m_numRows <= 0)
		{
			std::cerr << "";
			return false;
		}

		Vector2 textureSize = m_texture->GetSize();
		//m_frameSize = textureSize / Vector2{ static_cast<float>m_numColumns, (float)m_numRows };

		return true;
	}

	Rect TextureFrames::GetFrameRect(unsigned int frame)
	{
		if (frame < 0 || frame >= m_totalFrames)
		{
			frame = 0;
		}

		int currentFrame = m_startFrame + frame;
		int colume = currentFrame % m_numColumns;
		int row = currentFrame / m_numColumns;
		float x = colume * m_frameSize.x;
		float y = row * m_frameSize.y;

		return Rect
		{
			x,
			y,
			m_frameSize.x,
			m_frameSize.y
		};
	}
}