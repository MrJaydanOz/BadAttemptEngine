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
		_isWorking(true) { }

	Physics::~Physics()
	{

	}

	const std::deque<PhysicsCollision>& Physics::GetCollisionLog() const noexcept
	{ return _collisionLog; }

	void Physics::_AddPhysicsBody(in<PhysicsBody*> physicsBody) noexcept
	{ 
		if (physicsBody != nullptr)
			_physicsBodies.push_back(physicsBody);
	}

	void Physics::_AddCollider(in<Collider*> collider) noexcept
	{
		if (collider != nullptr)
			_collidersWithConnectedBody.push_back({ collider, collider->FindParentOfTypeRecursive<PhysicsBody>() });
	}

	void Physics::_RemovePhysicsBody(in<PhysicsBody*> physicsBody) noexcept
	{
		if (physicsBody != nullptr)
		{
			std::deque<Collider*> collidersConnectedToGivenBody;

			for (auto i = _collidersWithConnectedBody.begin(); i != _collidersWithConnectedBody.end();)
			{
				if (i->second == physicsBody)
				{
					collidersConnectedToGivenBody.push_front(i->first);
					_collidersWithConnectedBody.erase(i);
				}
				else
					i++;
			}

			auto found = std::find(_physicsBodies.begin(), _physicsBodies.end(), physicsBody);

			if (found != _physicsBodies.end())
				_physicsBodies.erase(found);
		}
	}

	void Physics::_RemoveCollider(in<Collider*> collider) noexcept
	{
		if (collider != nullptr)
		{
			auto found = std::find_if(_collidersWithConnectedBody.begin(), _collidersWithConnectedBody.end(), [&](in<std::pair<Collider*, PhysicsBody*>> pair) -> bool
				{ return pair.first == collider; });

			if (found != _collidersWithConnectedBody.end())
				_collidersWithConnectedBody.erase(found);
		}
	}

	void Physics::_Simulate(in<float> deltaTime) noexcept
	{
		_collisionLog.clear();

		for (auto& physicsBody : _physicsBodies)
		{
			physicsBody->_velocity += gravity;
			physicsBody->Translate(physicsBody->_velocity * deltaTime);
			physicsBody->Rotate(physicsBody->_angularVelocity * deltaTime);
			physicsBody->CacheWorldPose();
		}

		for (auto& [collider, physicsBody] : _collidersWithConnectedBody)
		{
			if (physicsBody == nullptr)
				collider->CacheWorldPose();
		}

		bool didCollide;
		PhysicsCollision collision;

		for (auto i1 = _physicsBodies.begin(); i1 < _physicsBodies.end(); i1++)
			for (auto i2 = i1 + 0; i2 < _physicsBodies.end(); i2++)
			{
				DEBUG_LOG_INFO(DEBUG_NODE_NAME(*i1) << " & " << DEBUG_NODE_NAME(*i2));

				for (auto& [collider1, physicsBody1] : _collidersWithConnectedBody)
					if (collider1 != nullptr && physicsBody1 == *i1)
					{
						DEBUG_LOG_INFO("collider1: " << DEBUG_NODE_NAME(collider1) << " at " << collider1->GetPosition());
						if (physicsBody1 != nullptr)
							DEBUG_LOG_INFO("physicsBody1: " << DEBUG_NODE_NAME(physicsBody1) << " at " << physicsBody1->GetPosition());

						for (auto& [collider2, physicsBody2] : _collidersWithConnectedBody)
							if (collider2 != nullptr && (i1 == i2 ? physicsBody2 == nullptr : physicsBody2 == *i2) && !collider2->isTrigger)
							{
								DEBUG_LOG_INFO("collider2: " << DEBUG_NODE_NAME(collider2) << " at " << collider2->GetPosition());
								if (physicsBody2 != nullptr)
									DEBUG_LOG_INFO("physicsBody2: " << DEBUG_NODE_NAME(physicsBody2) << " at " << physicsBody2->GetPosition());

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

										DEBUG_LOG_INFO("collider1AsAxisBox: " << DEBUG_NODE_NAME(collider1AsAxisBox) << " & " << "collider2AsAxisBox: " << DEBUG_NODE_NAME(collider2AsAxisBox) << ", combinedBounds:" << combinedBounds << ", otherCenter:" << otherCenter);

										if (combinedBounds.Contains(otherCenter))
										{
											DEBUG_LOG_INFO("contains");

											Vector2F combinedBoundsExtent = combinedBoundsSize * 0.5f;

											collision.physicsBody1 = physicsBody1;
											collision.collider1 = collider1;
											collision.physicsBody2 = physicsBody2;
											collision.collider2 = collider2;

											Vector2F deltaOtherCenter = otherCenter - combinedBounds.GetCenter();

											collision.contactPoint = otherCenter + (deltaOtherCenter * -0.5f);

											Vector<4, std::pair<uint8, float>> distancesFromEdges;
											distancesFromEdges.x = { 0, combinedBoundsExtent.x - deltaOtherCenter.x };
											distancesFromEdges.y = { 1, combinedBoundsExtent.y - deltaOtherCenter.y };
											distancesFromEdges.z = { 2, deltaOtherCenter.x - combinedBoundsExtent.x };
											distancesFromEdges.w = { 3, deltaOtherCenter.y - combinedBoundsExtent.y };

											const auto distanceComparison = [](in<std::pair<uint8, float>> a, in<std::pair<uint8, float>> b) noexcept -> bool { return a.second < b.second; };

											std::pair<uint8, float> maxDistanceFromEdge = Max(Max(Max(
												distancesFromEdges.x,
												distancesFromEdges.y, distanceComparison),
												distancesFromEdges.z, distanceComparison),
												distancesFromEdges.w, distanceComparison);

											DEBUG_LOG_INFO(maxDistanceFromEdge.first << " : " << maxDistanceFromEdge.second);

											collision.contactOverlap = maxDistanceFromEdge.second;

											switch (maxDistanceFromEdge.first)
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
											physicsBody1->CacheWorldPose(true);
										}
										else
										{
											// collision between two bodies
										}
									}

									_collisionLog.push_back(collision);
								}
							}
					}
			}
	}
}
