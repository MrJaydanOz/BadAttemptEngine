#include "BAE_Animation.h"
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

	AnimationState::AnimationState() noexcept :
		_controls() { }
	AnimationState::AnimationState(in_initializer_list<AnimationControl*> controls) noexcept :
		_controls(controls) { }

	AnimationState::~AnimationState()
	{
		for (auto& control : _controls)
			delete control;
	}

	void AnimationState::_Process(in<Animator*> animator, in<float> animationTime) noexcept
	{
		for (auto& control : _controls)
		{
			Node* foundNode = animator;
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

			control->Process(foundNode, animationTime);
		}
	}

	Animation::Animation(in_initializer_list<bae::Pair<std::string, AnimationState*>> states) noexcept :
		_states(states) { }

	Animation::~Animation()
	{
		for (auto& state : _states)
			delete state.second;
	}

	void Animation::CreateAnimationState(in<std::string> name, in_initializer_list<AnimationControl*> controls) noexcept
	{
		AnimationState* result = GetState(name);
		if (result != nullptr)
		{
			delete result;
			result = new AnimationState(controls);
		}
		else
			_states.Append({ name, new AnimationState(controls) });
	}

	void Animation::RemoveAnimationState(in<std::string> name) noexcept
	{
		_states.RemoveFirstWhere([&](in<bae::Pair<std::string, AnimationState*>> pair) -> bool { return pair.first.compare(name) == 0; });
	}

	AnimationState* Animation::GetState(in<std::string> name) noexcept
	{
		bae::Pair<std::string, AnimationState*>* result;
		if (_states.TryFindIf([&](in<bae::Pair<std::string, AnimationState*>> pair) -> bool { return pair.first.compare(name) == 0; }, result))
			return (*result).second;
		else
			return nullptr;
	}
}