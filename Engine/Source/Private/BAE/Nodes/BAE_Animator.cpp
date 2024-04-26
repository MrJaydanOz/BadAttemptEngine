#include "Nodes/BAE_Animator.h"

namespace bae
{
	Animator::Animator(in<Node*> parent) noexcept :
		Behaviour::Behaviour(parent),
		animationSpeed(1.0f),
		isPlaying(false),
		_stateMachine(nullptr),
		_animationTime(0.0f) { }

	Animator::~Animator() noexcept { }

	void Animator::Create(in<const char*> name)
	{
		Behaviour::Create(name);
	}

	void Animator::Destroy()
	{
		Behaviour::Destroy();
	}

	void Animator::SetAnimation(Animation* animation) noexcept
	{ _stateMachine.machine = animation; }
	Animation* Animator::GetAnimation() const noexcept
	{ return _stateMachine.machine; }

	AnimationState* Animator::GetCurrentState() const noexcept
	{ return _stateMachine.GetCurrentState(); }

	float Animator::GetAnimationTime() const noexcept
	{ return _animationTime; }

	void Animator::Play(in<std::string> stateName, bool resetTime) noexcept
	{
		if (_stateMachine.machine == nullptr)
		{
			DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT << " (AnimationControl)", 
				DEBUG_NODE_NAME(this) << " doesn't have an Animation reference, therefore the state '" << stateName << "' is invalid.");
			return;
		}

		AnimationState* state = _stateMachine.machine->GetState(stateName);

		if (state == nullptr)
		{
			DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT << " (AnimationControl)", 
				DEBUG_NODE_NAME(this) << " doesn't have the state '" << stateName << "'.");
			return;
		}

		Play(state, resetTime);
	}

	void Animator::Play(in<size_t> stateIndex, bool resetTime) noexcept
	{
		if (_stateMachine.machine == nullptr)
		{
			DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT << " (AnimationControl)", 
				DEBUG_NODE_NAME(this) << " doesn't have an Animation reference, therefore the index '" << stateIndex << "' is invalid.");
			return;
		}

		AnimationState* state = _stateMachine.machine->GetState(stateIndex);

		if (state == nullptr)
		{
			DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT << " (AnimationControl)", 
				DEBUG_NODE_NAME(this) << " doesn't have the index '" << stateIndex << "'.");
			return;
		}

		Play(state, resetTime);
	}

	void Animator::Play(in<AnimationState*> state, bool resetTime) noexcept
	{
		_stateMachine.QueueState(state);
		isPlaying = true;
		if (resetTime)
			_animationTime = 0.0f;
	}

	void Animator::Pause() noexcept
	{
		isPlaying = false;
	}

	void Animator::Resume() noexcept
	{
		isPlaying = true;
	}

	void Animator::Stop() noexcept
	{
		_stateMachine.QueueState(nullptr);
		isPlaying = true;
		_animationTime = 0.0f;
	}

	void Animator::_Process(in<float> deltaTime) noexcept
	{
		_stateMachine.Tick({ this, _animationTime += deltaTime * animationSpeed });
	}
}