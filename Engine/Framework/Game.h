#pragma once
#include "Scene.h"

namespace nu
{
	class Game
	{
	public:
		Game();
		virtual ~Game();
		Game(std::unique_ptr<Scene> scene) :
			m_scene{ std::move(scene) } {};

		virtual bool Initialize() { return true; }
		virtual void Shutdown() {}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		void SetScene(std::unique_ptr<Scene> scene);

	protected:
		std::unique_ptr<Scene> m_scene = nullptr;
	};
}
