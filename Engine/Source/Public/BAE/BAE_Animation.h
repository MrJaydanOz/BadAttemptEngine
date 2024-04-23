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

	class AnimationState : protected State<std::string, in<tuple<in<Animator*>, in<float>>>>
	{
	public:
		using KeyType = State::KeyType;
		using ParameterType = State::ParameterType;

		using InstanceType = State::InstanceType;

		friend class Animator;

	private:
		bae::List<AnimationControl*> _controls;

	public:
		AnimationState(in<KeyType> name) noexcept;
		AnimationState(in<KeyType> name, in_initializer_list<AnimationControl*> controls) noexcept;
		~AnimationState();

		const KeyType& GetKey()
		{ return State::GetKey(); }

		virtual void OnStart(ParameterType) override;

		virtual void OnTick(ParameterType parameter) override;

		virtual void OnEnd(ParameterType) override;
	};

	using Animation = StateMachine<AnimationState>;
}