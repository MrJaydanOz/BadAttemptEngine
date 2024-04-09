#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Physics.h"))
#endif
#include "Nodes/BAE_PhysicsBody.h"
#include "Nodes/BAE_Collider.h"
#include "Nodes/BAE_ColliderAxisBox.h"


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
		bae::List<PhysicsBody*> _physicsBodies;
		bae::List<std::pair<Collider*, PhysicsBody*>> _collidersWithConnectedBody;
		bae::List<PhysicsCollision> _collisionLog;

	public:
		const bae::List<PhysicsCollision>& GetCollisionLog() const noexcept;

		template<typename TResultCollection = bae::List<PhysicsCollision>>
		size_t FindCollisionsOf(in<PhysicsBody*> physicsBody, ref<TResultCollection> results)
		{
			for (const PhysicsCollision& collision : _collisionLog)
			{
				if (collision.physicsBody1 == physicsBody)
					results.push_back(collision);
				else if (collision.physicsBody2 == physicsBody)
				{
					PhysicsCollision flippedCollision = collision;
					Swap(flippedCollision.physicsBody1, flippedCollision.physicsBody2);
					Swap(flippedCollision.collider1, flippedCollision.collider2);
					flippedCollision.contactNormal = -flippedCollision.contactNormal;

					results.push_back(flippedCollision);
				}
			}
		}

		template<typename TResultCollection = bae::List<PhysicsCollision>>
		size_t FindCollisionsOf(in<Collider*> collider, ref<TResultCollection> results)
		{
			for (const PhysicsCollision& collision : _collisionLog)
			{
				if (collision.collider1 == collider)
					results.push_back(collision);
				else if (collision.collider2 == collider)
				{
					PhysicsCollision flippedCollision = collision;
					Swap(flippedCollision.physicsBody1, flippedCollision.physicsBody2);
					Swap(flippedCollision.collider1, flippedCollision.collider2);
					flippedCollision.contactNormal = -flippedCollision.contactNormal;

					results.push_back(flippedCollision);
				}
			}
		}

		template<typename TPredicate = bool(in<PhysicsCollision>)>
		bool CollisionExistsWithWhere(in<PhysicsBody*> physicsBody, in_delegate<TPredicate> predicate)
		{
			for (const PhysicsCollision& collision : _collisionLog)
			{
				if (collision.physicsBody1 == physicsBody)
				{
					if (predicate(collision))
						return true;
				}
				else if (collision.physicsBody2 == physicsBody)
				{
					PhysicsCollision flippedCollision = collision;
					Swap(flippedCollision.physicsBody1, flippedCollision.physicsBody2);
					Swap(flippedCollision.collider1, flippedCollision.collider2);
					flippedCollision.contactNormal = -flippedCollision.contactNormal;

					if (predicate(flippedCollision))
						return true;
				}
			}

			return false;
		}

		template<typename TPredicate = bool(in<PhysicsCollision>)>
		bool CollisionExistsWithWhere(in<Collider*> collider, in_delegate<TPredicate> predicate)
		{
			for (const PhysicsCollision& collision : _collisionLog)
			{
				if (collision.collider1 == collider)
				{
					if (predicate(collision))
						return true;
				}
				else if (collision.collider2 == collider)
				{
					PhysicsCollision flippedCollision = collision;
					Swap(flippedCollision.physicsBody1, flippedCollision.physicsBody2);
					Swap(flippedCollision.collider1, flippedCollision.collider2);
					flippedCollision.contactNormal = -flippedCollision.contactNormal;

					if (predicate(flippedCollision))
						return true;
				}
			}

			return false;
		}

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