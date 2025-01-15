#include "../inc/Tessy.h"

int TessyAPI_Initialize(const char* tessdatapath, const char *languages, OcrEngineMode ocrenginemode) {
	tessbaseapi = new TessBaseAPI();
	return tessbaseapi->Init(tessdatapath, languages, ocrenginemode);
}
/// <summary>
/// Recognizes the image from SetThresholdImage.<br/>
/// Wrapper for TessBaseAPI::Recongize();
/// </summary>
/// <returns>If error, returns -1</returns>
int Tessy_Recongize() {
	if (tessbaseapi) 
	{
		return tessbaseapi->Recognize(0);
	}
	return -1;
}
void Tessy_Clear() {
	tessbaseapi->Clear();
}
void Tessy_SetImage(const unsigned char* data, uint width, uint height, uint channels, uint stride) {
	tessbaseapi->SetImage(data, width, height, channels, stride);
}
void Tessy_Shutdown() {
	tessbaseapi->End();
	delete tessbaseapi;
}
const char* Tessy_GetUTF8Text() {
	return tessbaseapi->GetUTF8Text();
}
void Tessy_SetPageSegMode(PageSegMode mode) {
	tessbaseapi->SetPageSegMode(mode);
}
void Tessy_SetSourceResolution(UINT ppi) {
	tessbaseapi->SetSourceResolution(ppi);
}

const TESSYWORDS* Tessy_GetWords() 
{
	ResultIterator* ri = tessbaseapi->GetIterator();
	PageIteratorLevel level = tesseract::RIL_WORD;
	std::vector<TESSYWORDS> words;
	if (ri != 0) {
		do {
			char* cWord = ri->GetUTF8Text(level);
			if (cWord != NULL) {
				std::string wordStr = std::string(cWord);
				float confidence = ri->Confidence(level);
				int x, y, width, height;
				ri->BoundingBox(level, &x, &y, &width, &height);
				TESSYWORDS tessywords;
				tessywords.Word = wordStr;
				tessywords.confidence = confidence;
				tessywords.BoundingBox = BOUNDINGBOX(x, y, width, height);

				words.push_back(tessywords);

			}
		} while (ri->Next(level));
	}
	TESSYWORDS* result = words.data();
	return result;
}
const char* Tessy_GetVersion() {
	return tessbaseapi->Version();
}