#include "BAE_Scene.h"
#include "Nodes/BAE_Transform.h"
#include <deque>

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

	void Scene::ClearWorldPositionCaches() const noexcept
	{
		std::vector<Transform*> transformBuffer;

		for (Node* node : GetRootNodes())
			if (node != nullptr)
			{
				transformBuffer.clear();
				node->FindChildrenOfTypeRecursive<Transform>(transformBuffer);
				for (Transform* transform : transformBuffer)
				{
					transform->ClearWorldPoseCache(false);
				}
			}
			else
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "The scene has a null root node.");
	}
}