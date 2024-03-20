#include "Graphics/Stamp.h"

Stamp::~Stamp()
{
	SDL_DestroyTexture(_texture);
}

Vector2I Stamp::GetSize() const noexcept { return _size; }

int Stamp::GetWidth() const noexcept { return _size.x; }

int Stamp::GetHeight() const noexcept { return _size.y; }

Stamp::Stamp(SDL_Texture* texture, const Vector2I& size) noexcept : 
	_texture(texture), 
	_size(size)
{ }