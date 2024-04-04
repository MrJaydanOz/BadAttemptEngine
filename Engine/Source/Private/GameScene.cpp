#include "GameScene.h"

namespace bae
{
	const std::vector<Node*>& Scene::GetRootNodes() const noexcept
	{ return _rootNodes; }
}