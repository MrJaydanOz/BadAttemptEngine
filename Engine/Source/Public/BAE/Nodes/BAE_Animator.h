#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Animator.h"))
#endif
#include "Nodes/BAE_Behaviour.h"
#include "BAE_Animation.h"

namespace bae
{
	class Scene;

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class Animator))
#endif
	class Animator : public Behaviour
	{
		NODE_BEGIN;
		friend class Scene;

	public:
		float animationSpeed;
		bool isPlaying;
	private:
		StateMachineInstance<Animation> _stateMachine;
		float _animationTime;

	public:
		void SetAnimation(Animation* animation) noexcept;
		Animation* GetAnimation() const noexcept;

		AnimationState* GetCurrentState() const noexcept;

		float GetAnimationTime() const noexcept;

		void Play(in<std::string> stateName, bool resetTime = true) noexcept;
		void Play(in<size_t> stateIndex, bool resetTime = true) noexcept;
		void Play(in<AnimationState*> state, bool resetTime = true) noexcept;

		void Pause() noexcept;

		void Resume() noexcept;

		void Stop() noexcept;

	private:
		Animator(in<Node*> parent) noexcept;
		virtual ~Animator() noexcept override;
		virtual void Create(in<const char*> name = "") override;
		virtual void Destroy() override;

		void _Process(in<float> deltaTime) noexcept;
	};
}