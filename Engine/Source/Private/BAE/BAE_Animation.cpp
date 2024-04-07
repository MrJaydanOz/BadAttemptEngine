#include "BAE_Animation.h"
#include "Nodes/BAE_Sprite.h"
#include <numeric>

namespace bae
{
	AnimationControl::AnimationControl(std::initializer_list<std::string> nodePath) noexcept :
		nodePath(nodePath) { }

	AnimationControlSpriteImage::AnimationControlSpriteImage(std::initializer_list<std::string> nodePath) noexcept :
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
	AnimationState::AnimationState(std::initializer_list<AnimationControl> controls) noexcept :
		_controls(controls) { }

	void AnimationState::_Process(in<Animator*> animator, in<float> animationTime) noexcept
	{
		for (auto& control : _controls)
		{
			Node* foundNode = animator;
			for (const std::string& name : control.nodePath)
			{
				if (foundNode->TryFindChildWithName<Node>(name, foundNode))
					continue;
				else
				{
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT << " (AnimationControl)", "Path does point to an existing node.");
					break;
				}
			}

			control.Process(foundNode, animationTime);
		}
	}

	Animation::Animation(std::initializer_list<std::pair<std::string, AnimationState>> states) noexcept :
		_states()
	{
		for (auto& [key, value] : states)
			_states[key] = value;
	}

	void Animation::AddAnimationState(in<std::string> name, in<AnimationState> state) noexcept
	{
		_states[name] = state;
	}

	void Animation::RemoveAnimationState(in<std::string> name) noexcept
	{
		_states.erase(name);
	}

	AnimationState* Animation::GetState(in<std::string> name) noexcept
	{
		auto i = _states.find(name);

		if (i == _states.end())
			return nullptr;
		else
			return &(*i).second;
	}
}