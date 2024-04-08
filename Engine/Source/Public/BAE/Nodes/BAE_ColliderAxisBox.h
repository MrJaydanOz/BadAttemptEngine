#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_ColliderAxisBox.h"))
#endif
#include "Nodes/BAE_Collider.h"

namespace bae
{
	class Scene;
	class Physics;

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class ColliderAxisBox))
#endif
	class ColliderAxisBox : public Collider
	{
		NODE_BEGIN;
		friend class Physics;

	public:
		Vector2F center;
		Vector2F size;

	public:
		virtual ~ColliderAxisBox() noexcept override;

	protected:
		ColliderAxisBox(in<std::string> name = "") noexcept;
	};
}