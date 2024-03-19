#pragma once
#include <SDL2/SDL_image.h>
#include "Graphics/Image.h"
#include "Math/RectT.h"
#include "Math/VectorT.h"

class Stamp
{
private:
	SDL_Texture* _texture;

	Vector2I _size;

public:
	~Stamp() noexcept;

	Vector2I GetSize() const noexcept;
	int GetWidth() const noexcept;
	int GetHeight() const noexcept;

private:
	Stamp(SDL_Texture* texture, const Vector2I& size) noexcept;
};