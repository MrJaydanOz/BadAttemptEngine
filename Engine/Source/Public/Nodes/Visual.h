#pragma once
#include "Game.h"
#include "SDL2/SDL_image.h"
#include "Nodes/Behaviour.h"
#include "Nodes/Camera.h"

enum VisualBlendingMode
{
	VisualBlendingMode_None,
	VisualBlendingMode_Alpha,
	VisualBlendingMode_Add,
	VisualBlendingMode_Modulate,
	VisualBlendingMode_Multiply
};

class Visual : public Behaviour
{
	friend class Camera;

private:
	int _renderLayer;
	int _zOrder;

public:
	virtual ~Visual() noexcept override;

	int GetRenderLayer() const;
	void SetRenderLayer(int layer);

	int GetZOrder() const;
	void SetZOrder(int index);

	void RemoveFromRenderList();
	void AddToRenderList();

	virtual void Render(SDL_Renderer* renderer, const Camera* camera) = 0;

protected:
	Visual(int zOrder, int renderLayer = 0) noexcept;
	Visual(const std::string& name = "", int zOrder = 0, int renderLayer = 0) noexcept;
};