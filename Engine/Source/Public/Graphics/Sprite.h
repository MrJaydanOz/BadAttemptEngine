#pragma once

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Surface;

class Sprite
{
public:
	int posX, posY;

	float rotation;

	float scale;

private:
	SDL_Texture* _textureReference;

	SDL_Renderer* _rendererReference;

	SDL_Surface* _surfaceData;

	const char* _path;

public:
	Sprite(SDL_Renderer* _rendererReference);
	~Sprite();

	bool ImportTexture(const char* pathToFile);

	void Draw();

	void Dispose();

	const char* GetPath() const { return _path; }
};