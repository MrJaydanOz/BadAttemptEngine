#pragma once
#include "Math/RectT.h"
#include "Math/VectorT.h"

struct SDL_Surface;

class Image
{
private:
public: SDL_Surface* _surfaceData;

	const char* _path;

public:
	/// <summary>
	/// Loads the image at the given path into memory and returns the pointer.
	/// </summary>
	/// <param name="path">- char[]</param>
	/// <returns>Image* or nullptr if failed.</returns>
	static Image* Load(const char* path);
	/// <summary>
	/// Tries to load the image at the given path into memory and returns the pointer.
	/// </summary>
	/// <param name="path">- char[]</param>
	/// <param name="image">- OUT Image*</param>
	/// <returns>true if successful, false otherwise.</returns>
	static bool TryLoad(const char* path, Image*& image);

	~Image();

	const char* GetPath() const { _path; }

	Vector2I GetSize() const;
	int GetWidth() const;
	int GetHeight() const;

private:
	Image(const char* path, SDL_Surface* surfaceData);
};