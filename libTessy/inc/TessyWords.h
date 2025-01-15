#pragma once
#include "TessyAPI.h"
#include <Windows.h>
#include <string>

struct BOUNDINGBOX {
	int x, y, width, height;
	BOUNDINGBOX() : x(0),y(0),width(0), height(0) 
	{

	}
	BOUNDINGBOX(int X, int Y, int Width, int Height) : x(X), y(Y), width(Width), height(Height) 
	{

	}
};
struct TESSYWORDS
{
	std::string Word;
	float confidence;
	BOUNDINGBOX BoundingBox;
	TESSYWORDS() : Word(""), confidence(0.0f), BoundingBox()
	{

	}
};