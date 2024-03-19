#pragma once
#include "Game.h"
#include "Nodes/Behaviour.h"
#include "SDL2/SDL_image.h"
#include "Nodes/Camera.h"
#include "GameGraphics.h"

enum VisualBlendingMode
{
	None,
	Alpha,
	Add,
	Modulate,
	Multiply
};

class Visual : public Behaviour
{
	friend Camera;
	friend Graphics;

private:
	int _renderLayer;
	int _zOrder;

public:
	virtual ~Visual() noexcept override;

	int GetRenderLayer() const;
	void SetRenderLayer(int layer);

	int GetZOrder() const;
	void SetZOrder(int layer);

protected:
	Visual(int zOrder, int renderLayer = 0) noexcept;
	Visual(const std::string& name = "", int zOrder = 0, int renderLayer = 0) noexcept;

	virtual void Render(SDL_Renderer* renderer, const Camera* camera) = 0;

private:
	void RemoveFromRenderList();
	void AddToRenderList();
};