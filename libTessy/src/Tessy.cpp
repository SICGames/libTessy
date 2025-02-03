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
int TessyAPI_Recognize() {
	if (tessbaseapi) 
	{
		return tessbaseapi->Recognize(0);
	}
	return -1;
}
void TessyAPI_Clear() {
	tessbaseapi->Clear();
}
void TessyAPI_SetImage(const unsigned char* data, uint width, uint height, uint channels, uint stride) {
	tessbaseapi->SetImage(data, width, height, channels, stride);
}
void TessyAPI_Shutdown() {
	tessbaseapi->End();
	delete tessbaseapi;
}
const char* TessyAPI_GetUTF8Text() {
	return tessbaseapi->GetUTF8Text();
}
void TessyAPI_SetPageSegMode(PageSegMode mode) {
	tessbaseapi->SetPageSegMode(mode);
}
void TessyAPI_SetSourceResolution(UINT ppi) {
	tessbaseapi->SetSourceResolution(ppi);
}

void TessyAPI_GetWords(TessyWords** wordsArray, size_t* size) 
{
	ResultIterator* ri = tessbaseapi->GetIterator();
	PageIteratorLevel level = tesseract::RIL_WORD;
	auto words = new std::vector<TessyWords>();
	if (ri != 0) {
		do {
			char* cWord = ri->GetUTF8Text(level);
			if (cWord != NULL) {
				const char* word = cWord;
				float confidence = ri->Confidence(level);
				int x, y, width, height;
				ri->BoundingBox(level, &x, &y, &width, &height);
				TessyWords tessywords;
				tessywords.Word = word;
				tessywords.confidence = confidence;
				tessywords.BoundingBox.x = x;
				tessywords.BoundingBox.y = y;
				tessywords.BoundingBox.width = width - x;
				tessywords.BoundingBox.height = height - y;

				words->push_back(tessywords);
				delete[] word;
			}
		} while (ri->Next(level));
	}
	*size = words->size();
	*wordsArray = (TessyWords*)malloc(*size * sizeof(TessyWords));
	for (auto i = 0; i < *size; i++) 
	{
		if (*wordsArray) {
			(*wordsArray)[i].Word = words->at(i).Word;

			(*wordsArray)[i].confidence = words->at(i).confidence;
			(*wordsArray)[i].BoundingBox.x = words->at(i).BoundingBox.x;
			(*wordsArray)[i].BoundingBox.y = words->at(i).BoundingBox.y;
			(*wordsArray)[i].BoundingBox.width = words->at(i).BoundingBox.width;
			(*wordsArray)[i].BoundingBox.height = words->at(i).BoundingBox.height;
		}
	}
}

void TessyAPI_FreeWords(TessyWords* words) {
	free(words);
}
const char* TessyAPI_GetVersion() {
	return tesseract::TessBaseAPI::Version();
}
