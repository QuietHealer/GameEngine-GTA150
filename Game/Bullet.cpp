#include "Bullet.h"
#include "Math/MathUtils.h"
#include "Core/Factory.h"
#include "Components/PhysicsComponent.h"


FACTORY_REGISTER(Bullet)

void Bullet::Update(float dt)
{

    auto physicsComponent = GetComponent<nu::PhysicsComponent>();
    if (physicsComponent)
    {
        nu::Vector2 forward{ 1,0 };
        nu::Vector2 force = forward.Rotate(m_transform.rotation * nu::DegToRad) * m_speed;

        physicsComponent->SetVelocity(m_speed);
        //  physicsComponent->ApplyTorque(rotate);
    }
	//SetVelocity(velocity);

	Actor::Update(dt);
}


