#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Collider.h"))
#endif
#include "Nodes/BAE_Transform.h"

namespace bae
{
	class Physics;

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class Collider))
#endif
	class Collider : public Transform
	{
		NODE_BEGIN;
		friend class Physics;

	public:
		uint32 collisionLayers;
		bool isTrigger;

	protected:
		Collider(in<Node*> parent) noexcept;
		virtual ~Collider() noexcept override;
		virtual void Create(in<const char*> name = "") override;
		virtual void Destroy() override;

		virtual void OnParentChanged() noexcept override;
	};
}