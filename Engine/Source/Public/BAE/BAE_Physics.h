#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Physics.h"))
#endif
#include "Nodes/BAE_PhysicsBody.h"
#include "Nodes/BAE_Collider.h"
#include "Nodes/BAE_ColliderAxisBox.h"
#include <deque>

namespace bae
{
	class Game;

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(struct PhysicsCollision))
#endif
	struct PhysicsCollision
	{
		PhysicsBody* physicsBody1;
		Collider* collider1;
		PhysicsBody* physicsBody2;
		Collider* collider2;
		Vector2F contactPoint;
		Vector2F contactNormal;
		float contactOverlap;

		PhysicsCollision() noexcept;
	};

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Physics))
#endif
	class Physics
	{
		friend class PhysicsBody;
		friend class Collider;
		friend class Game;

	public:
		Vector2F gravity;

	private:
		bool _isWorking;
		std::vector<PhysicsBody*> _physicsBodies;
		std::vector<std::pair<Collider*, PhysicsBody*>> _collidersWithConnectedBody;
		std::deque<PhysicsCollision> _collisionLog;

	public:
		const std::deque<PhysicsCollision>& GetCollisionLog() const noexcept;

	private:
		Physics();
		~Physics();

		void _AddPhysicsBody(in<PhysicsBody*> physicsBody) noexcept;

		void _AddCollider(in<Collider*> collider) noexcept;

		void _RemovePhysicsBody(in<PhysicsBody*> physicsBody) noexcept;

		void _RemoveCollider(in<Collider*> collider) noexcept;

		void _Simulate(in<float> deltaTime) noexcept;
	};
}