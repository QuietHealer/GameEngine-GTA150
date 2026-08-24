#pragma once

#include "Random.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Math/MathUtils.h"
#include "File.h"
#include "Texture.h"
#include "StringUtils.h"

#include "Text.h"
#include "Factory.h"

#include "Renderer.h"
#include "Input.h"
#include "Font.h"
#include "Audio.h"
#include "GameTime.h"
#include "ParticleSystem.h"

#include "ResourceManager.h"
#include "Components/RendererComponent.h"

#include "Actor.h"
#include "Scene.h"
#include "Game.h"
#include "fmod.hpp"
#include "Object.h"
#include "Physics/Physcs.h"


#define ENGINE			Engine::Get()

namespace nu
{
	class Engine
	{
	public:
	    static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }
		ParticleSystem& GetPS() { return m_particleSystem; }

		Engine(const Engine&) = delete;
		Engine& operator = (const Engine&) = delete;

		Audio& GetAudio() { return m_audio; }
		Physics& GetPhysics() { return m_physics; }

	private:
		Engine() = default;


	private:
		Input m_input;
		Renderer m_renderer;
		Audio m_audio;
		ParticleSystem m_particleSystem;
		Time m_time;
		Physics m_physics;
	};
}

