#pragma once
#include "GameGraphics.h"
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
	friend class Graphics;
	friend class Camera;

private:
	int _renderLayer;
	int _zOrder;

public:
	virtual ~Visual() noexcept override;

	int GetRenderLayer() const noexcept;
	void SetRenderLayer(int layer) noexcept;

	int GetZOrder() const noexcept;
	void SetZOrder(int index) noexcept;

	virtual void OnEnable() noexcept override;
	virtual void OnDisable() noexcept override;

	virtual void Render(SDL_Renderer* renderer, const Camera* camera) noexcept = 0;

protected:
	Visual(int zOrder, int renderLayer = 0) noexcept;
	Visual(const std::string& name = "", int zOrder = 0, int renderLayer = 0) noexcept;

private:
	void RemoveFromRenderList() noexcept;
	void AddToRenderList() noexcept;
};