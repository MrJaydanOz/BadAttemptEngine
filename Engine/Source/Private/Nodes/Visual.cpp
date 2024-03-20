#include "Nodes/Visual.h"
#include <algorithm>

Visual::~Visual() noexcept
{
	Behaviour::~Behaviour();
}

int Visual::GetRenderLayer() const { return _renderLayer; }

void Visual::SetRenderLayer(int layer)
{
	if (layer != _renderLayer)
	{
		RemoveFromRenderList();
		_renderLayer = layer;
		AddToRenderList();
	}
}

int Visual::GetZOrder() const { return _zOrder; }

void Visual::SetZOrder(int index)
{
	if (index != _zOrder)
	{
		RemoveFromRenderList();
		_zOrder = index;
		AddToRenderList();
	}
}

Visual::Visual(int zOrder, int renderLayer) noexcept : Visual("", zOrder, renderLayer) { }

Visual::Visual(const std::string& name, int zOrder, int renderLayer) noexcept : Behaviour(name),
	_zOrder(zOrder),
	_renderLayer(renderLayer)
{ }

void Visual::RemoveFromRenderList()
{
	std::vector<Graphics::VisualsInRenderLayer>& visuals = Game::GetGame()->GetGraphics()->_visualsInRenderLayers;

	auto foundLayer = std::find_if(visuals.begin(), visuals.end(), [&](const Graphics::VisualsInRenderLayer& v) -> bool { return v.index == _renderLayer; });

	if (foundLayer != visuals.end())
	{
		auto removeIndex = std::find(foundLayer->visualsInZOrder.begin(), foundLayer->visualsInZOrder.end(), this);

		if (removeIndex != foundLayer->visualsInZOrder.end())
			foundLayer->visualsInZOrder.erase(removeIndex);
	}
}

void Visual::AddToRenderList()
{
	std::vector<Graphics::VisualsInRenderLayer>& visuals = Game::GetGame()->GetGraphics()->_visualsInRenderLayers;

	auto foundLayer = std::find_if(visuals.begin(), visuals.end(), [&](const Graphics::VisualsInRenderLayer& v) -> bool { return v.index == _renderLayer; });

	if (foundLayer != visuals.end())
	{
		auto insertIndex = std::upper_bound(foundLayer->visualsInZOrder.begin(), foundLayer->visualsInZOrder.end(), _zOrder, [](const int& a, const Visual* b) -> bool { return a < b->GetZOrder(); });

		foundLayer->visualsInZOrder.insert(insertIndex, this);
	}
}