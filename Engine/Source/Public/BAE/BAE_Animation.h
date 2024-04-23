#pragma once
#include "BAE_Def.h"
#include "BAE_Collections.h"
#include "Nodes/BAE_Node.h"
#include "Math/BAE_VectorT.h"
#include "BAE_Image.h"
#include "BAE_StateMachine.h"

namespace bae
{
	class Animator;
	class AnimationState;

	class AnimationControl
	{
		friend class AnimationState;

	public:
		bae::List<std::string> nodePath;

	public:
		AnimationControl(in_initializer_list<std::string> nodePath) noexcept;
		virtual ~AnimationControl() noexcept { }

	protected:
		virtual void Process(in<Node*> targetNode, in<float> animationTime) noexcept { }
	};

	class AnimationControlSpriteImage : public AnimationControl
	{
	public:
		Image* image;
		Vector2I clipSize;
		Vector2I clipStartPosition;
		std::optional<Vector2I> clipFrameDelta;
		int frameCount;
		float frameRate;

	public:
		AnimationControlSpriteImage(in_initializer_list<std::string> nodePath) noexcept;
		virtual ~AnimationControlSpriteImage() noexcept { }

	protected:
		virtual void Process(in<Node*> targetNode, in<float> animationTime) noexcept override;
	};

	class AnimationState : public State<std::string, in<float>>
	{
		friend class Animator;

	private:
		bae::List<AnimationControl*> _controls;

	public:
		AnimationState() noexcept;
		AnimationState(in_initializer_list<AnimationControl*> controls) noexcept;
		~AnimationState();

	protected:
		virtual void OnStart(ref<MachineType> machine, in<float>) override;

		virtual void OnTick(ref<MachineType> machine, in<float> animationTime) override;

		virtual void OnEnd(ref<MachineType> machine, in<float>) override;

	private:
		void _Process(in<Animator*> animator, in<float> animationTime) noexcept;
	};

	class Animation : public StateMachine<State<std::string, in<float>>>
	{
		friend class Animator;

	private:
		bae::List<bae::Pair<std::string, AnimationState*>> _states;

	public:
		Animation(in_initializer_list<bae::Pair<std::string, AnimationState*>> states) noexcept;
		~Animation();

		void CreateAnimationState(in<std::string> name, in_initializer_list<AnimationControl*> controls) noexcept;

		void RemoveAnimationState(in<std::string> name) noexcept;

		AnimationState* GetState(in<std::string> name) noexcept;
	};
}