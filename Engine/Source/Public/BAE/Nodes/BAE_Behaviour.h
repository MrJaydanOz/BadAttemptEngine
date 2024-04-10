#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Behaviour.h"))
#endif
#include "Nodes/BAE_Node.h"

namespace bae
{
#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Behaviour))
#endif
	class Behaviour : public Node
	{
		NODE_BEGIN;

	private:
		bae::uintx_t<2> _enabledState;

	public:
		_NODISCARD bool IsEnabledSelf() const noexcept;
		void SetEnabledSelf(in<bool> enabled) noexcept;
		_NODISCARD bool IsEnabled() const noexcept;

	protected:
		Behaviour(in<Node*> parent) noexcept;
		virtual ~Behaviour() noexcept override;
		virtual void Create(in<const char*> name = "") override;
		virtual void Destroy() override;

		virtual void OnParentChanged() override;

		virtual void OnEnabled() { }

		virtual void OnDisabled() { }

	private:
		_NODISCARD bool _IsEnabledInHierarchy() const noexcept;
		void _SetEnabledInHierarchy(in<bool> enabled) noexcept;

		void _SetEnabledInHierarchyToSurfaceBehaviours(in<Node*> node, in<bool> enabled) const noexcept
		{
			for (Node* child : GetChildren())
				if (child != nullptr)
				{
					Behaviour* castedChild = dynamic_cast<Behaviour*>(child);
					if (castedChild != nullptr)
						castedChild->_SetEnabledInHierarchy(enabled);
					else
						_SetEnabledInHierarchyToSurfaceBehaviours(node, enabled);
				}
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, DEBUG_NODE_NAME(this) << " has a null child.");
		}
	};
}