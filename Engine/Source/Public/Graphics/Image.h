#pragma once

struct SDL_Texture;
struct SDL_Surface;

class Image
{
private:
	SDL_Surface* _surfaceData;

	const char* _path;

public:
	static Image* Load(const char* path);

	~Image();

private:
	Image(const char* path, SDL_Surface* surfaceData);
};