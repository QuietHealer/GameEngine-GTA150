#include "pch.h"
#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"


using namespace nu;

bool SpaceGame::Initialize()
{
	Game::Initialize();
	
	m_scene = new Scene();
	m_scene->SetGame(this);

	m_titleFont = new Font();
	m_titleFont->Load("fonts/airstrike.ttf", 64);

	m_titleText = new Text(m_titleFont);
	m_titleText->Create(Engine::Get().GetRenderer(), "XETRON", Color{ 1.0f, 1.0f, 1.0f });

	m_gameFont = new Font();
	m_gameFont->Load("fonts/airstrike.ttf", 32);

	m_scoreText = new Text(m_gameFont);
	m_livesText = new Text(m_gameFont);

	Engine::Get().GetAudio().AddSound("laser", "audio/laser.wav");
	Engine::Get().GetAudio().AddSound("explosion", "audio/Explosion.wav");
	Engine::Get().GetAudio().AddSound("theme", "audio/Battle_theme_loopable.wav", true);

	return true;
}

void SpaceGame::Update(float dt)
{
	switch (m_gameState)
	{
	case GameState::Title:
		nu::Engine::Get().GetAudio().PlaySound("theme");
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_gameState = GameState::StartGame;
		}
		break;
	case GameState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_stateTimer = 5.0f;
		m_stateTimer = 0.5f;
		m_gameState = GameState::StartLevel;
		break;
	case GameState::StartLevel:
		m_spawnCount = 1;
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAllActors();
			SpawnPlayer();
			m_spawnTime = 5.0f;
			m_gameState = GameState::Game;
		}
		break;
	case GameState::Game:
		m_spawnTime -= dt;
		if (m_spawnTime <= 0.0f)
		{
			m_spawnTime = nu::RandomFloat(3.0f, 5.0f);
			for (int i = m_spawnCount; i > 0; i--)
			{
				SpawnEnemy();
			}
			m_spawnCount++;
			if (m_spawnCount > 7)
			{
				m_spawnCount = 1;
			}
		}
		break;
	case GameState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAllActors();
			m_gameState = GameState::Title;
		}
		break;
	default:
		break;
		
	}

	Game::Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
	switch (m_gameState)
	{
	case GameState::Title:
		m_titleText->Draw(renderer, 400, 400);
		break;
	case GameState::StartGame:
	case GameState::StartLevel:
	case GameState::Game:

		m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 30, 30);

		m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
		m_livesText->Draw(renderer, (float)renderer.GetWidth() - 160, 30.0f);
		break;
	case GameState::GameOver:
		break;
	default:
		break;
	}
	Game::Draw(renderer);
}

void SpaceGame::OnPlayerDead()
{
	m_lives--;

	m_gameState = (m_lives == 0) ? GameState::GameOver : GameState::StartLevel;
	//if (m_lives == 0) m_gameState = GameState::GameOver;
	//else m_gameState = GameState::StartLevel;

	m_stateTimer = 2.0f;

}

void SpaceGame::SpawnPlayer()
{
	PlayerDesc playerDesc;
	playerDesc.name = "Player";
	playerDesc.model = assets::playerModel;
	playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f}, 0.0f, 15.0f };
	playerDesc.velocity = Vector2{ 0.0f, 0.0f };
	playerDesc.damping = 3.0f;
	playerDesc.speed = 2000.0f;

	std::unique_ptr<Player> player  = std::make_unique<Player>(playerDesc);
	m_scene->AddActor(std::move(player));
}

void SpaceGame::SpawnEnemy()
{
	EnemyDesc enemyDesc;
	enemyDesc.name = "Enemy";
	enemyDesc.model = assets::enemyModel;
	float x = nu::RandomFloat((float)Engine::Get().GetRenderer().GetWidth());
	float y = nu::RandomFloat((float)Engine::Get().GetRenderer().GetHeight());
	enemyDesc.transform = Transform{ Vector2{ x, y }, 90.0f, 10.0f };
	enemyDesc.damping = 3.0f;
	enemyDesc.speed = 800.0f;

	Enemy* enemy = new Enemy{ enemyDesc };
	m_scene->AddActor(std::make_unique<Enemy>(enemy));
}
