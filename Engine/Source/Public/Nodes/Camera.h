#pragma once
#include <SDL2/SDL_image.h>
#include "Game.h"
#include "Nodes/Transform.h"

class Camera : public Transform
{
public:
	int renderLayerMin;
	int renderLayerMax;

private:
	float _size;
	float _sizeControlsWidthToHeight;
	SDL_Renderer* _renderer;

public:
	Camera(const std::string& name = "") noexcept;
	virtual ~Camera() noexcept override;

	bool IsMainCamera();
	void SetMainCamera();
};