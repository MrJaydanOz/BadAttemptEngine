#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_StateMachine.h"))
#endif

#include "BAE_Collections.h"
#include "BAE_Debug.h"

namespace bae
{
#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class StateMachine))
#endif
	template<typename TStateType>
	class StateMachine;

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class StateMachineInstance))
#endif
	template<typename TMachineType>
	class StateMachineInstance;

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class State))
#endif
	template<typename TKey, typename... TParameters>
	class State
	{
	public:
		using KeyType = TKey;
		using ParameterTypes = TParameters;

		using MachineType = StateMachineInstance<StateMachine<State>>;

		friend class MachineType;

	private:
		KeyType _key;

	protected:
		virtual void OnStart(ref<MachineType> machine, ParameterTypes... parameters) = 0;

		virtual void OnTick(ref<MachineType> machine, ParameterTypes... parameters) = 0;

		virtual void OnEnd(ref<MachineType> machine, ParameterTypes... parameters) = 0;

		State(in<TKey> key) noexcept :
			_key(key) { }
	};

	template<typename TStateType>
	class StateMachine
	{
	public:
		using StateType = TStateType;

		using StateKeyType = StateType::KeyType;
		using StateParameterTypes = StateType::ParameterTypes;
		using IndexType = List<StateType>::size_type;

	private:
		List<StateType> _states;

	public:
		StateMachine() noexcept :
			_states(),
			_currentState(nullptr),
			_doNoRecursionError(false) { }

		StateMachine(in_initializer_list<StateType> states) noexcept : 
			_states(states),
			_currentState(nullptr),
			_doNoRecursionError(false) { }

		_NODISCARD_RESULT StateType* GetState(in<StateKeyType> key) const noexcept requires requires(in<StateType> state, in<StateKeyType> key) { state._key == key; }
		{ return _states.FindIf([&](in<StateType> state) -> bool { return state._key == key }); }
		_NODISCARD_RESULT StateType* GetState(in<IndexType> index) const noexcept requires !std::is_convertible_v<StateKeyType, IndexType>
		{ return _states[index]; }

		bool TryGetState(in<StateKeyType> key, ref<StateType*> result) const noexcept requires requires(in<StateType> state, in<StateKeyType> key) { state._key == key; }
		{ return (result = GetState(key)) != nullptr; }
	};

	template<typename TMachineType>
	class StateMachineInstance
	{
	public:
		using MachineType = TMachineType;

		using StateType = MachineType::StateType;
		using StateKeyType = MachineType::StateKeyType;
		using StateParameterTypes = MachineType::StateParameterTypes;
		using IndexType = MachineType::IndexType;

	private:
		MachineType* _machine;

		StateType* _currentState;
		std::optional<StateType*> _queuedState;
		bool _doNoRecursionError;

	public:
		StateMachineInstance() noexcept :
			_machine(nullptr) { }

		StateMachineInstance(in<MachineType*> machine) noexcept :
			_machine(machine) { }

		void Tick(StateParameterTypes... parameters)
		{
			if (_doNoRecursionError)
				throw new std::exception("Do not call Tick(...) from inside a state.");

			if (_queuedState.has_value())
				ChangeState(_queuedState.value(), parameters...);

			if (_currentState != nullptr)
			{
				_doNoRecursionError = true;
				_currentState->OnTick(this, parameters...);
				_doNoRecursionError = false;
			}
		}

		void ChangeState(in<StateType*> targetState, StateParameterTypes... parameters)
		{
			if (_doNoRecursionError)
				throw new std::exception("Do not call ChangeState(StateType*, ...) from inside a State<>. Use QueueState(StateType*) instead.");

			_queuedState = {};

			if (_currentState != nullptr)
			{
				_doNoRecursionError = true;
				_currentState->OnEnd(this, parameters...);
				_doNoRecursionError = false;
			}

			_currentState = targetState;

			if (_currentState != nullptr)
			{
				_doNoRecursionError = true;
				_currentState->OnStart(this, parameters...);
				_doNoRecursionError = false;
			}
		}
		void ChangeState(in<StateKeyType> targetStateKey, StateParameterTypes... parameters) requires requires(in<StateType> state, in<StateKeyType> key) { state._key == key; }
		{
			if (_doNoRecursionError)
				throw new std::exception("Do not call ChangeState(TStateKey, ...) from inside a State<>. Use QueueState(TStateKey) instead.");

			StateType* targetState = GetState(targetStateKey);

			if (targetState)
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "No state has the given stateKey, setting state to null.");

			ChangeState(targetState, parameters...);
		}
		void ChangeState(in<IndexType> targetStateIndex, StateParameterTypes... parameters) requires !std::is_convertible_v<StateKeyType, IndexType>
		{
			if (_doNoRecursionError)
				throw new std::exception("Do not call ChangeState(size_t, ...) from inside a State<>. Use QueueState(size_t) instead.");

			StateType* targetState = GetState(targetStateIndex);

			if (targetState)
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "Index outside of range, setting state to null.");

			ChangeState(targetState, parameters...);
		}

		void QueueState(in<StateType*> targetState) noexcept
		{
			_queuedState = targetState;
		}
		void QueueState(in<StateKeyType> targetStateKey) noexcept requires requires(in<StateType> state, in<StateKeyType> key) { state._key == key; }
		{
			StateType* targetState = GetState(targetStateIndex);

			if (targetState)
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "No state has the given stateKey, setting state to null.");

			QueueState(targetState);
		}
		void QueueState(in<IndexType> targetStateIndex) noexcept requires !std::is_convertible_v<StateKeyType, IndexType>
		{
			StateType* targetState = GetState(targetStateIndex);

			if (targetState)
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "Index outside of range, setting state to null.");

			QueueState(targetState);
		}
	};
}