#pragma once
#include "Common.h"
#include "TessyAPI.h"
#include "TesseractHeaders.h"
#include "TessyWords.h"

using namespace tesseract;

#pragma region Declarations
TessBaseAPI* tessbaseapi = nullptr;
bool isInitialized;
#pragma endregion

TESSY_API int TessyAPI_Initialize(const char*, const char*, OcrEngineMode);
TESSY_API int TessyAPI_Recognize();
TESSY_API void TessyAPI_Clear();
TESSY_API void TessyAPI_SetImage(const unsigned char*, uint, uint, uint, uint);
TESSY_API void TessyAPI_Shutdown();
TESSY_API const char* TessyAPI_GetUTF8Text();
TESSY_API void TessyAPI_SetPageSegMode(PageSegMode);
TESSY_API void TessyAPI_SetSourceResolution(UINT ppi);
TESSY_API void TessyAPI_GetWords(TessyWords** ,size_t*);
TESSY_API void TessyAPI_FreeWords(TessyWords*);
TESSY_API const char* TessyAPI_GetVersion();