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
		friend class Scene;

	public:
		Animation* animation;
		float animationSpeed;
		bool isPlaying;
	private:
		AnimationState* _animationState;
		float _animationTime;

	public:
		void Play(in<std::string> stateName) noexcept;
		void Play(in<AnimationState*> state) noexcept;

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