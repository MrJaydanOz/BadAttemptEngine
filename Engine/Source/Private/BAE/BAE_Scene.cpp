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

	void Scene::_DeleteDestroyed() noexcept
	{
		for (Node* node : _nodesToDelete)
			delete node;

		_nodesToDelete.Clear();
	}
}