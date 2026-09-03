#pragma once
#include "Framework/Game.h"
#include"Renderer/Text.h"
#include "Resources/Resource.h"

class SpriteGame : public nu::Game
{
	enum class GameState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

public:
	SpriteGame() = default;
	SpriteGame(nu::Scene* scene) :
		Game{scene}
	{ }

	bool Initialize() override;

	void Update(float dt) override;
	void Draw(class nu::Renderer& renderer) override;

	void OnPlayerDead();
	void AddPoints(int points) { m_score += points; }


private:
	void SpawnPlayer();
	void SpawnEnemy();

private:
	int m_score{ 0 };
	int m_lives{ 0 };

	float m_stateTimer = 0.0f;

	float m_spawnTime = 0.0f;
	int m_spawnCount = 0;
	//res_t<Texture> m_bg;

	GameState m_gameState = GameState::Title;

	nu::res_t<nu::Font> m_titleFont;
	nu::res_t<nu::Font> m_gameFont;


	//nu::Font* m_titleFont{ nullptr };
	nu::Text* m_titleText{ nullptr };

	nu::Font* m_gameOverFont{ nullptr };
	nu::Text* m_gameOverText{ nullptr };

	//nu::Font* m_gameFont{ nullptr };

	nu::Text* m_scoreText{ nullptr };
	nu::Text* m_livesText{ nullptr };
};