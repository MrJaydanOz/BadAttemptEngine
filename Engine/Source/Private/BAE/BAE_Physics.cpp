#include "BAE_Physics.h"
#include "BAE_Game.h"
#include "Math/BAE_RectT.h"
#include "Math/Func/BAE_Comparison.h"

#include "BAE_Debug.h"

namespace bae
{
	PhysicsCollision::PhysicsCollision() noexcept :
		physicsBody1(nullptr),
		collider1(nullptr),
		physicsBody2(nullptr),
		collider2(nullptr),
		contactPoint(0.0f, 0.0f),
		contactNormal(0.0f, 0.0f),
		contactOverlap(0.0f) { }

	Physics::Physics() :
		_isWorking(true),
		_physicsBodies(),
		_colliders(),
		_collidersWithConnectedBodyBuffer(),
		_collisionLog() { }

	Physics::~Physics()
	{

	}

	const bae::List<PhysicsCollision>& Physics::GetCollisionLog() const noexcept
	{ return _collisionLog; }

	void Physics::_AddPhysicsBody(in<PhysicsBody*> physicsBody) noexcept
	{
		if (physicsBody != nullptr)
			_physicsBodies.Append(physicsBody);
	}

	void Physics::_AddCollider(in<Collider*> collider) noexcept
	{
		if (collider != nullptr)
			_colliders.Append(collider);
	}

	void Physics::_RemovePhysicsBody(in<PhysicsBody*> physicsBody) noexcept
	{
		if (physicsBody != nullptr)
			_physicsBodies.Remove(physicsBody);
	}

	void Physics::_RemoveCollider(in<Collider*> collider) noexcept
	{
		if (collider != nullptr)
			_colliders.Remove(collider);
	}

	void Physics::_Simulate(in<float> deltaTime) noexcept
	{
		_collisionLog.Clear();

		for (auto& physicsBody : _physicsBodies)
		{
			physicsBody->_velocity += gravity;
			physicsBody->_velocity *= 1.0f - physicsBody->_drag;
			physicsBody->Translate(physicsBody->_velocity * deltaTime);
			physicsBody->Rotate(physicsBody->_angularVelocity * deltaTime);
		}

		_collidersWithConnectedBodyBuffer.Clear();
		_collidersWithConnectedBodyBuffer.SetCapacityAtLeast(_colliders.Size());
		for (auto& collider : _colliders)
			_collidersWithConnectedBodyBuffer.Append({ collider, collider->FindParentOfTypeRecursive<PhysicsBody>() });

		bool didCollide;
		PhysicsCollision collision;

		auto processCollisionForPair = [&](PhysicsBody* physicsBody1, PhysicsBody* physicsBody2) -> void
			{
				for (auto& [collider2, collider2physicsBody] : _collidersWithConnectedBodyBuffer)
				{
					if (collider2 != nullptr && collider2physicsBody == physicsBody2)
					{
						for (auto& [collider1, collider1physicsBody] : _collidersWithConnectedBodyBuffer)
						{
							if (collider1 != nullptr && collider1physicsBody == physicsBody1 && !(collider1->isTrigger && collider2->isTrigger) && (collider1->collisionLayers & collider2->collisionLayers) != 0)
							{
								didCollide = false;

								ColliderAxisBox* collider1AsAxisBox = dynamic_cast<ColliderAxisBox*>(collider1);
								if (collider1AsAxisBox)
								{
									ColliderAxisBox* collider2AsAxisBox = dynamic_cast<ColliderAxisBox*>(collider2);
									if (collider2AsAxisBox) // collider1 == AxisBox && collider2 == AxisBox
									{
										Vector2F combinedBoundsSize = collider1AsAxisBox->size + collider2AsAxisBox->size;
										BoundsF combinedBounds = BoundsF::AsCenterSize(collider1AsAxisBox->TransformPoint(collider1AsAxisBox->center), combinedBoundsSize);
										Vector2F otherCenter = collider2AsAxisBox->TransformPoint(collider2AsAxisBox->center);

										if (combinedBounds.Contains(otherCenter))
										{
											Vector2F combinedBoundsExtent = combinedBoundsSize * 0.5f;

											collision.physicsBody1 = physicsBody1;
											collision.collider1 = collider1;
											collision.physicsBody2 = physicsBody2;
											collision.collider2 = collider2;

											Vector2F deltaOtherCenter = otherCenter - combinedBounds.GetCenter();

											collision.contactPoint = otherCenter + (deltaOtherCenter * -0.5f);

											std::pair<uint8, float> distancesFromEdges[4]
											{
												{ 0, combinedBoundsExtent.x - deltaOtherCenter.x },
												{ 1, combinedBoundsExtent.y - deltaOtherCenter.y },
												{ 2, combinedBoundsExtent.x + deltaOtherCenter.x },
												{ 3, combinedBoundsExtent.y + deltaOtherCenter.y }
											};

											const auto distanceComparison = [](in<std::pair<uint8, float>> a, in<std::pair<uint8, float>> b) noexcept -> bool { return a.second < b.second; };

											std::pair<uint8, float> minDistanceFromEdge = Min(Min(Min(
												distancesFromEdges[0],
												distancesFromEdges[1], distanceComparison),
												distancesFromEdges[2], distanceComparison),
												distancesFromEdges[3], distanceComparison);

											collision.contactOverlap = minDistanceFromEdge.second;

											switch (minDistanceFromEdge.first)
											{
											case 0: collision.contactNormal = Vector2F(+1.0f, 0.0f); break;
											case 1: collision.contactNormal = Vector2F(0.0f, +1.0f); break;
											case 2: collision.contactNormal = Vector2F(-1.0f, 0.0f); break;
											case 3: collision.contactNormal = Vector2F(0.0f, -1.0f); break;
											}

											didCollide = true;
										}
									}
								}

								if (didCollide)
								{
									if (!collider1->isTrigger)
									{
										if (physicsBody2 == nullptr)
										{
											float physicsBody1_velocity_Dot_collision_contactNormal = physicsBody1->_velocity.Dot(collision.contactNormal);
											if (physicsBody1_velocity_Dot_collision_contactNormal > 0.0f)
												physicsBody1->_velocity -= collision.contactNormal * physicsBody1_velocity_Dot_collision_contactNormal;

											physicsBody1->Translate(collision.contactNormal * -collision.contactOverlap);
										}
										else
										{
											Vector2F deltaVelocity = physicsBody1->_velocity - physicsBody2->_velocity;
											float massRatio = physicsBody1->_mass / (physicsBody2->_mass + physicsBody1->_mass);
											Vector2F combinedVelocity = Lerp(physicsBody2->_velocity, physicsBody1->_velocity, massRatio);

											float deltaVelocity_Dot_collision_contactNormal = deltaVelocity.Dot(collision.contactNormal);
											if (deltaVelocity_Dot_collision_contactNormal > 0.0f)
											{
												physicsBody1->_velocity -= collision.contactNormal * ((1.0f - massRatio) * deltaVelocity_Dot_collision_contactNormal);
												physicsBody2->_velocity += collision.contactNormal * (massRatio * deltaVelocity_Dot_collision_contactNormal);
											}

											physicsBody1->Translate(collision.contactNormal * ((1.0f - massRatio) * -collision.contactOverlap));
											physicsBody2->Translate(collision.contactNormal * (massRatio * collision.contactOverlap));
										}
									}

									_collisionLog.Append(collision);
								}
							}
						}
					}
				}
			};

		for (auto i1 = _physicsBodies.begin(); i1 < _physicsBodies.end(); i1++)
		{
			for (auto i2 = i1 + 1; i2 < _physicsBodies.end(); i2++)
				processCollisionForPair(*i1, *i2);
			processCollisionForPair(*i1, nullptr);
		}

		_collidersWithConnectedBodyBuffer.Clear();
	}
}
