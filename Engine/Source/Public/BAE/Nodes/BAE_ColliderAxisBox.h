#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_ColliderAxisBox.h"))
#endif
#include "Nodes/BAE_Collider.h"

namespace bae
{
	class Physics;

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class ColliderAxisBox))
#endif
	class ColliderAxisBox : public Collider
	{
		NODE_BEGIN;
		friend class Physics;

	public:
		Vector2F center;
		Vector2F size;

	protected:
		ColliderAxisBox(in<Node*> parent) noexcept;
		virtual ~ColliderAxisBox() noexcept override;
		virtual void Create(in<const char*> name = "") override;
		virtual void Destroy() override;
	};
}