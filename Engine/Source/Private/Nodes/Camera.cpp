#include "Nodes/Camera.h"

Camera::Camera(const std::string& name) noexcept : Transform(name)
{

}

Camera::~Camera() noexcept
{
	Transform::~Transform();
}