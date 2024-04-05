#pragma once
#include "Nodes/BAE_Node.h"

namespace bae
{
	class Behaviour : public Node
	{
	private:
		bae::uintx_t<2> _enabledState;

	public:
		virtual ~Behaviour() noexcept;

		bool IsEnabledSelf() const noexcept;
		void SetEnabledSelf(in<bool> enabled) noexcept;
		bool IsEnabled() const noexcept;

	protected:
		virtual void OnParentChanged() override;

		virtual void OnEnabled() { }

		virtual void OnDisabled() { }

	private:
		Behaviour(in<std::string> name = "", in<bool> enabled = true) noexcept;
		Behaviour(in<bool> enabled) noexcept;

		bool _IsEnabledInHierarchy() const noexcept;
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