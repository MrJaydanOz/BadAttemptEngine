#include "Nodes/BAE_Behaviour.h"
#include "Math/Func/BAE_Simple.h"

namespace bae
{
	Behaviour::Behaviour(in<std::string> name, in<bool> enabled) noexcept : 
		Node::Node(name),
		_enabledState(enabled ? 0b01 : 0b00) { }

	Behaviour::Behaviour(in<bool> enabled) noexcept :
		Behaviour::Behaviour("", enabled) { }

	Behaviour* Behaviour::CloneInto(Node* parent) noexcept
	{ return CloneIntoBegin<Behaviour>(parent, GetName(), IsEnabledSelf()); }

	void Behaviour::OnLoad()
	{
		if (IsEnabled())
			NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnEnabled);
	}

	Behaviour::~Behaviour() noexcept
	{
		if (IsEnabled())
			NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnDisabled);

		Node::~Node();
	}

	bool Behaviour::IsEnabledSelf() const noexcept
	{ return BitGet(_enabledState, 0); }
	void Behaviour::SetEnabledSelf(in<bool> enabled) noexcept
	{
		if (BitGet(_enabledState, 0) != enabled)
		{
			BitSet(_enabledState, 0, enabled);

			if (_IsEnabledInHierarchy())
			{
				if (enabled)
				{
					NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnEnabled);
				}
				else
				{
					NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnDisabled);
				}
				_SetEnabledInHierarchyToSurfaceBehaviours(this, enabled);
			}
		}
	}
	bool Behaviour::IsEnabled() const noexcept
	{ return _enabledState == 0b11; }

	void Behaviour::OnParentChanged()
	{
		Node::OnParentChanged();

		Behaviour* discard;

		if (IsEnabledSelf())
		{
			bool enabledInHierarchy = !TryFindParentThatRecursive<Behaviour>([](Behaviour* behaviour) -> bool 
				{ return !behaviour->IsEnabledSelf(); }, discard);

			if (BitGet(_enabledState, 1) != enabledInHierarchy)
			{
				BitSet(_enabledState, 1, enabledInHierarchy);

				if (enabledInHierarchy)
				{
					NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnEnabled);
				}
				else
				{
					NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnDisabled);
				}
				_SetEnabledInHierarchyToSurfaceBehaviours(this, enabledInHierarchy);
			}
		}
	}

	bool Behaviour::_IsEnabledInHierarchy() const noexcept
	{ return BitGet(_enabledState, 1); }
	void Behaviour::_SetEnabledInHierarchy(in<bool> enabled) noexcept
	{ 
		if (BitGet(_enabledState, 1) != enabled)
		{
			BitSet(_enabledState, 1, enabled);

			if (IsEnabledSelf())
			{
				if (enabled)
				{
					NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnEnabled);
				}
				else
				{
					NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnDisabled);
				}
				_SetEnabledInHierarchyToSurfaceBehaviours(this, enabled);
			}
		}
	}
}