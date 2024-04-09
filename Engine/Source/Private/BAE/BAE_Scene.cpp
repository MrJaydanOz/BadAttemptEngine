#include "BAE_Scene.h"
#include "Nodes/BAE_Transform.h"
#include "Nodes/BAE_Animator.h"

namespace bae
{
	const bae::List<Node*>& Scene::GetRootNodes() const noexcept
	{ return _rootNodes; }

	Scene::Scene() : 
		_rootNodes(),
		_prefabs(),
		_isWorking(true) { }

	Scene::~Scene()
	{
		_isWorking = false;

		for (auto& node : _prefabs)
			delete node;

		for (auto& node : _rootNodes)
			delete node;
	}

	void Scene::_ProcessAnimation(in<float> deltaTime) noexcept
	{
		bae::List<Animator*> animatorBuffer;
		FindNodesThat<Animator>([](in<Animator*> animator) -> bool { return animator->IsEnabled(); }, animatorBuffer);

		for (Animator* animator : animatorBuffer)
			animator->_Process(deltaTime);
	}

	void Scene::_ClearWorldPositionCaches() const noexcept
	{
		bae::List<Transform*> transformBuffer;
		for (Node* child : GetRootNodes())
			if (child != nullptr)
			{
				Transform* castedChild = dynamic_cast<Transform*>(child);
				if (castedChild != nullptr)
					transformBuffer.Append(castedChild);
				
				child->FindChildrenOfTypeRecursive<Transform>(transformBuffer);
			}
			else
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "The scene has a null root node.");

		for (Transform* transform : transformBuffer)
			transform->ClearWorldPoseCache(false);
	}
}