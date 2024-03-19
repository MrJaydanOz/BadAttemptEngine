#include "Graphics/Stamp.h"

Stamp::~Stamp()
{
	delete _texture;
}

Vector2I Stamp::GetSize() const { return _size; }

int Stamp::GetWidth() const { return _size.x; }

int Stamp::GetHeight() const { return _size.y; }

Stamp::Stamp(SDL_Texture* texture, const Vector2I& size) noexcept : 
	_texture(texture), 
	_size(size)
{ }