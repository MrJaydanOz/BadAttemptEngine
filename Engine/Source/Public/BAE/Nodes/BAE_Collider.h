#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Collider.h"))
#endif
#include "Nodes/BAE_Transform.h"

namespace bae
{
	class Scene;
	class Physics;

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Collider))
#endif
	class Collider : public Transform
	{
		NODE_BEGIN;
		friend class Physics;

	public:
		bool isTrigger;

	public:
		virtual ~Collider() noexcept override;

	protected:
		Collider(in<std::string> name = "") noexcept;

		virtual void OnLoad() noexcept override;

		virtual void OnParentChanged() noexcept override;

		virtual void OnDestroy() noexcept override;
	};
}