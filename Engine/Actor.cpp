#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtils.h"
#include "Texture.h"
#include "Engine.h"
#include "Factory.h"


namespace nu
{
    FACTORY_REGISTER(Actor)

    //class RegisterActor
    //{
    //public:
    //    RegisterActor()
    //    {
    //        Factory::Instance().Register<Actor>("Acter");
    //    }
    //};

    void Actor::Update(float dt)
    {
        if (m_lifespan > 0.0f)
        {
            m_lifespan -= dt;
            m_destroyed = (m_lifespan <= 0.0f);
        }

        //for (auto component : m_component)
        //{
        //    component->Update();
        //}

        // ph
        m_transform.position += (m_velocity * dt);
        m_velocity *= 1.0f / ((1.0f) + m_damping * dt);

        m_transform.position.x = Wrap(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = Wrap(0.0f, 1024.0f, m_transform.position.y);
    }

    void Actor::Draw(const Renderer& renderer) const
    {
        for (auto component : m_component)
        {
            auto rendererComponent = dynamic_cast<RendererComponent*>(&component);

            rendererComponent->Draw(renderer);
        }

    }

    float Actor::GetRadius() const
    {
        return 0.0f;
    }

    void Actor::Read(const json::value_t& value)
    {
        Object::Read(value);

        if (JSON_HAS_NAME(value, "transform"))
        {
            m_transform.Read(JSON_GET_NAME(value, "transform"));
        }

        std::string textureName;
        JSON_READ_NAME(value, "texture", textureName);

        JSON_READ_NAME(value, "tag", m_tag);
        JSON_READ_NAME(value, "lifespan", m_lifespan);
        JSON_READ_NAME(value, "velocity", m_velocity);
        JSON_READ_NAME(value, "damping", m_damping);

        //if (JSON_HAS_NAME(value, "components"))
        //{
        //    for (auto& componentValue : JSON_GET_NAME(value,);
        //}
    }
}