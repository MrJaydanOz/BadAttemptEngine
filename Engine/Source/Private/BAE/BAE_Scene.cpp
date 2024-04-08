#include "BAE_Scene.h"
#include "Nodes/BAE_Transform.h"
#include <deque>
#include "Nodes/BAE_Animator.h"

namespace bae
{
	const std::vector<Node*>& Scene::GetRootNodes() const noexcept
	{ return _rootNodes; }

	Scene::Scene() : 
		_rootNodes(),
		_prefabs(),
		_isWorking(true) { }

	Scene::~Scene()
	{
		for (auto i = _prefabs.rbegin(); i < _prefabs.rend(); i++)
			delete *i;

		for (auto i = _rootNodes.rbegin(); i < _rootNodes.rend(); i++)
			delete* i;
	}

	void Scene::_ProcessAnimation(in<float> deltaTime) noexcept
	{
		std::deque<Animator*> animatorBuffer;
		FindNodesThat<Animator>([](in<Animator*> animator) -> bool { return animator->IsEnabled(); }, animatorBuffer);

		for (Animator* animator : animatorBuffer)
			animator->_Process(deltaTime);
	}

	void Scene::_ClearWorldPositionCaches() const noexcept
	{
		std::deque<Transform*> transformBuffer;
		for (Node* child : GetRootNodes())
			if (child != nullptr)
			{
				Transform* castedChild = dynamic_cast<Transform*>(child);
				if (castedChild != nullptr)
					transformBuffer.push_back(castedChild);
				
				child->FindChildrenOfTypeRecursive<Transform>(transformBuffer);
			}
			else
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "The scene has a null root node.");

		for (Transform* transform : transformBuffer)
			transform->ClearWorldPoseCache(false);
	}
}