#pragma once
#include "BAE_Def.h"
#include <vector>
#include <map>
#include "Nodes/BAE_Node.h"
#include "Math/BAE_VectorT.h"
#include "BAE_Image.h"

namespace bae
{
	class Animator;
	class AnimationState;

	class AnimationControl
	{
		friend class AnimationState;

	public:
		std::vector<std::string> nodePath;

	public:
		AnimationControl(std::initializer_list<std::string> nodePath) noexcept;
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
		AnimationControlSpriteImage(std::initializer_list<std::string> nodePath) noexcept;

	protected:
		virtual void Process(in<Node*> targetNode, in<float> animationTime) noexcept override;
	};

	class AnimationState
	{
		friend class Animator;

	private:
		std::vector<AnimationControl> _controls;

	public:
		AnimationState() noexcept;
		AnimationState(std::initializer_list<AnimationControl> controls) noexcept;

	private:
		void _Process(in<Animator*> animator, in<float> animationTime) noexcept;
	};

	class Animation
	{
		friend class Animator;

	private:
		std::map<std::string, AnimationState> _states; // This type gives me high blood pressure.

	public:
		Animation(std::initializer_list<std::pair<std::string, AnimationState>> states) noexcept;

		void AddAnimationState(in<std::string> name, in<AnimationState> state) noexcept;

		void RemoveAnimationState(in<std::string> name) noexcept;

		AnimationState* GetState(in<std::string> name) noexcept;
	};
}

#include "Nodes/BAE_Animator.h"