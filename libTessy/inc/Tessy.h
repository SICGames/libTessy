#pragma once
#include "Common.h"
#include "TessyAPI.h"
#include "TesseractHeaders.h"
#include "TessyWords.h"

using namespace tesseract;

#pragma region Declarations
TessBaseAPI* tessbaseapi = nullptr;
#pragma endregion

TESSY_API int TessyAPI_Initialize(const char*, const char*, OcrEngineMode);
TESSY_API int Tessy_Recongize();
TESSY_API void Tessy_Clear();
TESSY_API void Tessy_SetImage(const unsigned char*, uint, uint, uint, uint);
TESSY_API void Tessy_Shutdown();
TESSY_API const char* Tessy_GetUTF8Text();
TESSY_API void Tessy_SetPageSegMode(PageSegMode);
TESSY_API void Tessy_SetSourceResolution(UINT ppi);
TESSY_API const TESSYWORDS* Tessy_GetWords();
TESSY_API const char* Tessy_GetVersion();