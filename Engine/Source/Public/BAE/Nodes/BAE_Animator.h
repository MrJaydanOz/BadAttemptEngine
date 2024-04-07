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

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Animator))
#endif
	class Animator : public Behaviour
	{
		NODE_BEGIN;

	public:
		Animation* animation;
		float animationSpeed;
		bool isPlaying;
	private:
		AnimationState* _animationState;
		float _animationTime;

	public:
		virtual ~Animator() noexcept override;

		virtual Animator* CloneInto(in<Node*> parent) noexcept override;

		void Play(in<std::string> stateName) noexcept;
		void Play(in<AnimationState*> state) noexcept;

		void Pause() noexcept;

		void Resume() noexcept;

		void Stop() noexcept;

	private:
		Animator(in<std::string> name = "", in<bool> enabled = true) noexcept;
		Animator(in<bool> enabled) noexcept;

		void _Process(in<float> deltaTime) noexcept;
	};
}