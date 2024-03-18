#pragma once
#include <SDL2/SDL_image.h>
#include "Nodes/Behaviour.h"
#include "Nodes/Transform.h"

class Camera : public Transform, public Behaviour
{
private:
	float size;
	float sizeControlsWidthToHeight;
	SDL_Renderer* renderer;

public:
	Camera(const std::string& name = "") noexcept;
	virtual ~Camera() noexcept override;


};