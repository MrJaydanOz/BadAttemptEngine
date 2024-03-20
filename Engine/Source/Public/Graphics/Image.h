#pragma once
#include <SDL2/SDL_image.h>
#include "Math/RectT.h"
#include "Math/VectorT.h"
#include "Nodes/Sprite.h"

class Image
{
	friend class Sprite;

private:
	SDL_Surface* _sdlSurface;
	SDL_Texture* _sdlTexture;

	const char* _path;

public:
	/// <summary>
	/// Loads the image at the given path into memory and returns the pointer.
	/// </summary>
	/// <param name="path">char[]</param>
	/// <returns>Image* or nullptr if failed.</returns>
	static Image* Load(const char* path) noexcept;
	/// <summary>
	/// Tries to load the image at the given path into memory and returns the pointer.
	/// </summary>
	/// <param name="path">char[]</param>
	/// <param name="image">OUT Image*</param>
	/// <returns>true if successful, false otherwise.</returns>
	static bool TryLoad(const char* path, Image*& image) noexcept;

	~Image() noexcept;

	const char* GetPath() const noexcept { _path; }

	Vector2I GetSize() const noexcept;
	int GetWidth() const noexcept;
	int GetHeight() const noexcept;

private:
	Image(const char* path, SDL_Surface* sdlSurface) noexcept;
};