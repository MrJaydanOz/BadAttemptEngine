#include "Nodes/BAE_Animator.h"

namespace bae
{
	Animator::Animator(in<Node*> parent) noexcept :
		Behaviour::Behaviour(parent),
		animation(nullptr),
		isPlaying(false),
		animationSpeed(1.0f),
		_animationState(nullptr),
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

	void Animator::Play(in<std::string> stateName) noexcept
	{
		if (animation == nullptr)
		{
			DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT << " (AnimationControl)", DEBUG_NODE_NAME(this) << " doesn't have an Animation reference, therefore the state '" << stateName << "' is invalid.");
			return;
		}

		AnimationState* state = animation->GetState(stateName);

		if (state == nullptr)
		{
			DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT << " (AnimationControl)", DEBUG_NODE_NAME(this) << " doesn't have the state '" << stateName << "'.");
			return;
		}

		Play(state);
	}

	void Animator::Play(in<AnimationState*> state) noexcept
	{
		_animationState = state;
		isPlaying = true;
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
		_animationState = nullptr;
		isPlaying = true;
		_animationTime = 0.0f;
	}

	void Animator::_Process(in<float> deltaTime) noexcept
	{
		if (_animationState != nullptr)
		{
			_animationTime += deltaTime * animationSpeed;

			_animationState->_Process(this, _animationTime);
		}
	}
}