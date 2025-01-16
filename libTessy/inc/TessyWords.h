#pragma once
#include "TessyAPI.h"
#include <Windows.h>
#include <string>

typedef struct _BoundingBox {
	int x, y, width, height;
} BoundingBox;
typedef struct _TessyWords
{
	const char* Word;
	float confidence;
	BoundingBox BoundingBox;
} TessyWords;