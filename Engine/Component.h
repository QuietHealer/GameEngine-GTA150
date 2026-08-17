#pragma once
#include "Object.h"

namespace nu
{
	class Component : public Object
	{
	
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual void Start() {}
		virtual void Destroyed() {}

		virtual void Update(float dt) {}

		class Actor* GetOwner() { return m_owner; }
	protected:
		class Actor* m_owner = nullptr;
	};
}
