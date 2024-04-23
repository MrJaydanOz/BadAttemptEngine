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
	template<typename TKey, typename TParameter>
	class State
	{
	public:
		using KeyType = TKey;
		using ParameterType = TParameter;

		using InstanceType = StateMachineInstance<StateMachine<State>>;

	private:
		KeyType _key;

	public:
		const KeyType& GetKey()
		{ return _key; }

		virtual void OnStart(ParameterType parameter) = 0;

		virtual void OnTick(ParameterType parameter) = 0;

		virtual void OnEnd(ParameterType parameter) = 0;

		State(in<TKey> key) noexcept :
			_key(key) { }
	};

	template<typename TStateType>
	class StateMachine
	{
	public:
		using StateType = TStateType;

		using StateKeyType = StateType::KeyType;
		using StateParameterType = StateType::ParameterType;
		using IndexType = List<StateType>::size_type;

	private:
		List<StateType*> _states;
		List<StateType*> _deleteInDestructor;

	public:
		StateMachine() noexcept :
			_states(),
			_deleteInDestructor() { }

		StateMachine(in_initializer_list<StateType*> states) noexcept : 
			_states(states),
			_deleteInDestructor() { }

		~StateMachine() noexcept
		{
			for (StateType*& state : _deleteInDestructor)
				delete state;
		}

		_NODISCARD_ONLY_READ const List<StateType*>& GetStates() const noexcept
		{ return _states; }

		template<typename... TConstructorArguments>
		const void CreateState(in<StateKeyType> key, TConstructorArguments... constructorArguments) noexcept(noexcept(StateType(key, constructorArguments...)))
		{ AssignState(new StateType(key, constructorArguments...), true); }
		const void AssignState(in<StateType*> state, bool deleteOnDestruction = false) noexcept
		{
			_states.Append(state);
			if (deleteOnDestruction)
				_deleteInDestructor.Append(state);
		}

		_NODISCARD_RESULT StateType* GetState(in<StateKeyType> key) const noexcept requires requires(in<StateType*> state, in<StateKeyType> key) { state->GetKey() == key; }
		{ 
			StateType*const* result;
			return _states.TryFindIf([&](in<StateType*> state) -> bool { return state != nullptr && state->GetKey() == key; }, result) 
				? *result 
				: nullptr;
		}
		_NODISCARD_RESULT StateType* GetState(in<IndexType> index) const noexcept requires !std::is_convertible_v<StateKeyType, IndexType>
		{ return index >= _states.size() ? nullptr : _states[index]; }

		bool TryGetState(in<StateKeyType> key, ref<StateType*> result) const noexcept requires requires { GetState(key); }
		{ return (result = GetState(key)) != nullptr; }
	};

	template<typename TMachineType>
	class StateMachineInstance
	{
	public:
		using MachineType = TMachineType;

		using StateType = MachineType::StateType;
		using StateKeyType = MachineType::StateKeyType;
		using StateParameterType = MachineType::StateParameterType;
		using IndexType = MachineType::IndexType;

	public:
		MachineType* machine;

	private:
		StateType* _currentState;
		StateType* _queuedState;
		bool _useQueuedState;
		bool _doNoRecursionError;

	public:
		StateMachineInstance() noexcept :
			machine(nullptr),
			_currentState(nullptr),
			_queuedState(nullptr),
			_useQueuedState(false),
			_doNoRecursionError(false) { }

		StateMachineInstance(in<MachineType*> machine) noexcept :
			machine(machine),
			_currentState(nullptr),
			_queuedState(nullptr),
			_useQueuedState(false),
			_doNoRecursionError(false) { }

		void Tick(StateParameterType parameter)
		{
			if (_doNoRecursionError)
				DEBUG_RETURN_EXCEPTION_CONTEXTED(BAE_LOG_CONTEXT, std::exception(
					"Do not call Tick(StateParameterType) from inside a state."));

			if (_useQueuedState)
			{
				ChangeState(_queuedState, parameter);
			}

			if (_currentState != nullptr)
			{
				_doNoRecursionError = true;
				_currentState->OnTick(parameter);
				_doNoRecursionError = false;
			}
		}

		void ChangeState(in<StateType*> targetState, StateParameterType parameter)
		{
			if (_doNoRecursionError)
				DEBUG_RETURN_EXCEPTION_CONTEXTED(BAE_LOG_CONTEXT, std::exception(
					"Do not call ChangeState(StateType*, StateParameterType) from inside a State<>. Use QueueState(StateType*) instead."));

			if (_currentState != nullptr)
			{
				_doNoRecursionError = true;
				_currentState->OnEnd(parameter);
				_doNoRecursionError = false;
			}

			_currentState = targetState;

			_queuedState = nullptr;
			_useQueuedState = false;

			if (_currentState != nullptr)
			{
				_doNoRecursionError = true;
				_currentState->OnStart(parameter);
				_doNoRecursionError = false;
			}
		}
		void ChangeState(in<StateKeyType> targetStateKey, StateParameterType parameter) requires requires(in<StateType> state, in<StateKeyType> key) { state._key == key; }
		{
			if (machine == nullptr)
				DEBUG_RETURN_EXCEPTION_CONTEXTED(BAE_LOG_CONTEXT, std::exception(
					"There is no StateMachine to read a state from."));

			if (_doNoRecursionError)
				DEBUG_RETURN_EXCEPTION_CONTEXTED(BAE_LOG_CONTEXT, std::exception(
					"Do not call ChangeState(TStateKey, ...) from inside a State<>. Use QueueState(TStateKey) instead."));

			StateType* targetState = machine->GetState(targetStateKey);

			if (targetState)
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "No state has the given stateKey, setting state to null.");

			ChangeState(targetState, parameter);
		}
		void ChangeState(in<IndexType> targetStateIndex, StateParameterType parameter) requires !std::is_convertible_v<StateKeyType, IndexType>
		{
			if (machine == nullptr)
				DEBUG_RETURN_EXCEPTION_CONTEXTED(BAE_LOG_CONTEXT, std::exception(
					"There is no StateMachine to read a state from."));

			if (_doNoRecursionError)
				DEBUG_RETURN_EXCEPTION_CONTEXTED(BAE_LOG_CONTEXT, std::exception(
					"Do not call ChangeState(size_t, ...) from inside a State<>. Use QueueState(size_t) instead."));

			StateType* targetState = machine->GetState(targetStateIndex);

			if (targetState)
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "Index outside of range, setting state to null.");

			ChangeState(targetState, parameter);
		}

		void QueueState(in<StateType*> targetState) noexcept
		{
			_queuedState = targetState;
			_useQueuedState = true;
		}
		void QueueState(in<StateKeyType> targetStateKey) noexcept requires requires(in<StateType> state, in<StateKeyType> key) { state._key == key; }
		{
			if (machine == nullptr)
				DEBUG_RETURN_EXCEPTION_CONTEXTED(BAE_LOG_CONTEXT, std::exception(
					"There is no StateMachine to read a state from."));

			StateType* targetState = machine->GetState(targetStateKey);

			if (targetState)
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "No state has the given stateKey, setting state to null.");

			QueueState(targetState);
		}
		void QueueState(in<IndexType> targetStateIndex) noexcept requires !std::is_convertible_v<StateKeyType, IndexType>
		{
			if (machine == nullptr)
				DEBUG_RETURN_EXCEPTION_CONTEXTED(BAE_LOG_CONTEXT, std::exception(
					"There is no StateMachine to read a state from."));

			StateType* targetState = machine->GetState(targetStateIndex);

			if (targetState)
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "Index outside of range, setting state to null.");

			QueueState(targetState);
		}
	};
}