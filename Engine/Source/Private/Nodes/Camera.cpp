#include "Nodes/Camera.h"
#include <limits.h>

Camera::Camera(const std::string& name) noexcept : Transform(name),
	renderLayerMin(INT_MIN),
	renderLayerMax(INT_MAX)
{
	if (Game::GetGame()->_mainCamera == nullptr)
		SetMainCamera();
}

Camera::~Camera() noexcept
{
	if (IsMainCamera())
		Game::GetGame()->_mainCamera = nullptr;

	Transform::~Transform();
}

bool Camera::IsMainCamera() { return this == Game::GetMainCamera(); }

void Camera::SetMainCamera() { Game::GetGame()->_mainCamera = this; }