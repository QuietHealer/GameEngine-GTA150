#pragma once
#include "Framework/Actor.h"

class Damager : public nu::Actor
{
public:
	CLASS_PROTOTYPE(Damager)

	void Read(const nu::json::value_t& value) override;

	void SetDamade(float damage) { m_damage = damage; }
	float GetDamage() { return m_damage; }

protected:
	float m_damage = 0.0f;
};
