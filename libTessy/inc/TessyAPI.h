#pragma once

#ifndef TESSY_API_IMPORT 
#define TESSY_API extern "C" __declspec(dllexport)
#else
#define TESSY_API extern "C" __declspec(dllimport)
#endif
