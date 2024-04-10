#include "Nodes/BAE_Behaviour.h"
#include "Math/Func/BAE_Simple.h"

namespace bae
{
	Behaviour::Behaviour(in<Node*> parent) noexcept :
		Node::Node(parent) 
	{
		_enabledState = 0b01;

		Behaviour* result;
		if (TryFindParentOfTypeRecursive<Behaviour>(result) ? result->IsEnabled() : true)
			_enabledState |= 0b10;
	}

	Behaviour::~Behaviour() noexcept { }

	void Behaviour::Create(in<const char*> name)
	{
		Node::Create(name);

		if (IsEnabled())
			NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnEnabled);
	}

	void Behaviour::Destroy()
	{
		if (IsEnabled())
			NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnDisabled);

		Node::Destroy();
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