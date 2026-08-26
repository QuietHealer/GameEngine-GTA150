#include "pch.h"
#include "Box2DPhysicsComponent.h"
#include "Core/Factory.h"
#include "Framework/Actor.h"
#include "Math/MathUtils.h"
#include "Core/StringUtils.h"

namespace nu
{
    FACTORY_REGISTER(Box2DPhysicsComponent)

        Box2DPhysicsComponent::Box2DPhysicsComponent(const Box2DPhysicsComponent& other)
    {
        m_bodyDef = other.m_bodyDef;
        m_size = other.m_size;
        m_scale = other.m_scale;
    }

    void Box2DPhysicsComponent::Start()
    {
        m_bodyDef.actor = GetOwner();
        //m_physicsBody std::make_unique<PhysicsBody>
    }

    void Box2DPhysicsComponent::Update(float dt)
    {
        GetOwner()->SetPosition(GetPosition());
        GetOwner()->SetRotation(GetRotation());
    }


    void Box2DPhysicsComponent::ApplyForce(const Vector2& force)
    {
        m_physicsBody->ApplyForce(force);
    }

    void Box2DPhysicsComponent::SetVelocity(const Vector2& velocity)
    {

    }

    Vector2 Box2DPhysicsComponent::GetVelocity()
    {
        return Vector2();
    }

    void Box2DPhysicsComponent::ApplyTorque(float torque)
    {
        //m_phy
    }

    void Box2DPhysicsComponent::SetAngularVelocity(float angularVelocity)
    {
    }

    float Box2DPhysicsComponent::GetAngularVelocity() const
    {
        return 0.0f;
    }

    void Box2DPhysicsComponent::SetPosition(const Vector2& position)
    {
    }

    Vector2 Box2DPhysicsComponent::GetPosition() const
    {
        return Vector2();
    }

    void Box2DPhysicsComponent::SetRotation(float rotation)
    {
    }

    float Box2DPhysicsComponent::GetRotation()
    {
        return 0.0f;
    }

    void Box2DPhysicsComponent::Read(const json::value_t& value)
    {

        PhysicsComponent::Read(value);

        JSON_READ_NAME(value, "size", m_size);
        JSON_READ_NAME(value, "scale", m_scale);

        JSON_READ_NAME(value, "gravity_scale", m_bodyDef.gravityScale);
        JSON_READ_NAME(value, "linear_damping", m_bodyDef.linearDamping);
        JSON_READ_NAME(value, "angular_damping", m_bodyDef.angularDamping);
        JSON_READ_NAME(value, "constrain_angle", m_bodyDef.constrainAngle);
        JSON_READ_NAME(value, "is_dynamic", m_bodyDef.isDynamic);
        JSON_READ_NAME(value, "friction", m_bodyDef.friction);
        JSON_READ_NAME(value, "restitution", m_bodyDef.restitution);
        JSON_READ_NAME(value, "density", m_bodyDef.density);
        JSON_READ_NAME(value, "is_sensor", m_bodyDef.isSensor);

        std::string shapeName;
        JSON_READ_NAME(value, "shape", shapeName);

        if (!shapeName.empty())
        {
            if (EqualsIngnoreCase(shapeName, "box")) m_bodyDef.shape = PhysicsBody::Shape::Box;
            else if (EqualsIngnoreCase(shapeName, "capsule")) m_bodyDef.shape = PhysicsBody::Shape::Capsule;
            else if (EqualsIngnoreCase(shapeName, "circle")) m_bodyDef.shape = PhysicsBody::Shape::Circle;
        }

    }
}
