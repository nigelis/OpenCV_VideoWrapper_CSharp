/*!
Export Video related functions of OpenCV.
*/

#pragma once

#ifdef VIDEOWRAPPER_EXPORTS
#define VIDEOWRAPPER_API extern "C" __declspec(dllexport)
#else
#define VIDEOWRAPPER_API extern "C" __decspec(dllimport)
#endif

#include <string>
using namespace std;

/*! Video Capture related functions. */
VIDEOWRAPPER_API long __stdcall VideoCapture_Open(const char* filename);
VIDEOWRAPPER_API bool __stdcall VideoCapture_IsOpened(long handle);
VIDEOWRAPPER_API void __stdcall VideoCapture_Release(long handle);
VIDEOWRAPPER_API bool __stdcall VideoCapture_Grab(long handle);
VIDEOWRAPPER_API bool __stdcall VideoCapture_Retrieve(long handle, unsigned char* frameData, int& frameLength, int expectedWidth, int expectedHeight, int channel = 0);
VIDEOWRAPPER_API bool __stdcall VideoCapture_Read(long handle, unsigned char* frameData, int& frameLength, int expectedWidth, int expectedHeight);
VIDEOWRAPPER_API bool __stdcall VideoCapture_Set(long handle, int propId, double value);
VIDEOWRAPPER_API double __stdcall VideoCapture_Get(long handle, int propId);

/*! Video Writter related functions. */
VIDEOWRAPPER_API long __stdcall VideoWriter_Open(const char* filename, int fourcc, double fps, int frameWidth, int frameHeight, bool isColor = true);
VIDEOWRAPPER_API bool __stdcall VideoWriter_IsOpened(long handle);
VIDEOWRAPPER_API void __stdcall VideoWriter_Release(long handle);
VIDEOWRAPPER_API void __stdcall VideoWriter_Write(long handle, unsigned char* frameData, int& frameLength);
