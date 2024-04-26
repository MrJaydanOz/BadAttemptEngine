#include "BAE_Animation.h"
#include "Nodes/BAE_Animator.h"
#include "Nodes/BAE_Sprite.h"
#include <numeric>

namespace bae
{
	AnimationControl::AnimationControl(in_initializer_list<std::string> nodePath) noexcept :
		nodePath(nodePath) { }

	AnimationControlSpriteImage::AnimationControlSpriteImage(in_initializer_list<std::string> nodePath) noexcept :
		AnimationControl::AnimationControl(nodePath),
		image(nullptr),
		clipSize(0, 0),
		clipStartPosition(0, 0),
		clipFrameDelta({}),
		frameCount(0),
		frameRate(0.0f) { }

	void AnimationControlSpriteImage::Process(in<Node*> targetNode, in<float> animationTime) noexcept
	{
		AnimationControl::Process(targetNode, animationTime);

		Sprite* targetSprite = dynamic_cast<Sprite*>(targetNode);
		if (targetSprite == nullptr)
		{
			DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT << " (AnimationControl)", "Path does not point to a sprite.");
			return;
		}

		targetSprite->image = image;

		int frame = (int)std::lround(std::floor(animationTime * frameRate)) % frameCount;

		targetSprite->clipRect = RectI
		(
			clipStartPosition + (clipFrameDelta.value_or(Vector2I(clipSize.x, 0)) * frame), 
			clipSize
		);
	}

	AnimationState::AnimationState(in<std::string> name) noexcept :
		State::State(name),
		changeToStateAfterDuration(nullptr),
		duration(0.0f),
		_controls() { }
	AnimationState::AnimationState(in<std::string> name, in_initializer_list<AnimationControl*> controls) noexcept :
		State::State(name),
		changeToStateAfterDuration(nullptr),
		duration(0.0f),
		_controls(controls) { }

	AnimationState::~AnimationState()
	{
		for (auto& control : _controls)
			delete control;
	}

	void AnimationState::OnStart(ParameterType)
	{ }

	void AnimationState::OnTick(ParameterType parameter)
	{
		if (duration > 0.0f && parameter.b > duration)
		{
			parameter.a->Play(changeToStateAfterDuration, true);
			return;
		}

		for (auto& control : _controls)
		{
			Node* foundNode = parameter.a;
			for (const std::string& name : control->nodePath)
			{
				Node* resultNode;
				if (foundNode->TryFindChildWithName<Node>(name, resultNode))
				{
					foundNode = resultNode;
					continue;
				}
				else
				{
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT << " (AnimationControl)", "Path does point to an existing node.");
					break;
				}
			}

			control->Process(foundNode, parameter.b);
		}
	}

	void AnimationState::OnEnd(ParameterType)
	{ }
}