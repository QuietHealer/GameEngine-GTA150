#include "EnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Damager.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void EnemyController::Update(float dt)
{
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();

	switch (m_state)
	{
	case CharacterBase::State::Move:
	{
		float dir = 0.0f;
		auto player = m_scene->GetActorByName<Actor>("PlayerPrototype");
		if (player)
		{
			nu::Vector2 position = GetTransform().position;
			nu::Vector2 playerPosition = player->GetTransform().position;
			nu::Vector2 direction = playerPosition - position;

			if (direction.Length() < 70.0f)
			{
				m_state = State::Attack;
				m_hasAttacked = false;
				m_rendererComponent->Play("Attack");
				break;
			}

			if (playerPosition.x < position.x) dir = -1.0f;
			else dir = 1.0f;
		}

		if (dir != 0.0f)
		{
			velocity.x = dir * 50.0f;
			m_rendererComponent->Play("run");
			m_rendererComponent->SetFlipH(dir < 0.0f);
		}
		else
		{
			m_rendererComponent->Play("idle");
		}
	}
		break;
	case CharacterBase::State::Attack:
		if (m_hasAttacked == false && m_rendererComponent->GetFrame() == 3)
		{
			auto damager = nu::Factory::Instance().Create<Damager>("DamagerPrototype");
			damager->SetDamage(3.0f);
			damager->SetPosition(GetTransform().position + nu::Vector2{ (m_rendererComponent->GetFlipH()) ? -60.0f : 20.0f, -30.0f });
			damager->SetScale(1.0f);
			damager->SetTag("EnemyDamager");
			m_scene->AddActor(std::move(damager));
			m_hasAttacked = true;
		}
		if (m_rendererComponent->IsAnimationDone())
		{
			m_state = State::Move;
			m_rendererComponent->Play("idle");
		}
		break;
	case CharacterBase::State::Hit:
		if (m_rendererComponent->IsAnimationDone())
		{
			m_state = State::Move;
			m_rendererComponent->Play("idle");
		}
		break;
	case CharacterBase::State::Death:
		break;
	default:
		break;
	}

	m_physicsComponent->SetVelocity(velocity);

	CharacterBase::Update(dt);
}

void EnemyController::OnCollision(nu::Actor* other)
{
	if (nu::EqualsIgnoreCase(other->GetTag(), "PlayerDamager"))
	{
		m_state = State::Hit;
		m_rendererComponent->Play("hit");
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager)
		{
			m_health -= damager->GetDamage();
		}
		if (m_health <= 0)
		{
			SetDestroyed();
		}
	}
}

void EnemyController::Read(const nu::json::value_t& value)
{
	CharacterBase::Read(value);
}
