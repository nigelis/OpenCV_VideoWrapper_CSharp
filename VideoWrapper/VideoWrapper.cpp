#include "VideoWrapper.h"
#include <opencv2/opencv.hpp>
using namespace cv;

/*! 
Encode the resized image to jpg format.

@param src [in] Mat, source image.
@param frameData, frameLength [out] encoded image output.
@param expectedWidth, expectedHeight [in] expected size.
*/
void ResizeEncodeImage(InputArray src, unsigned char* frameData, int& frameLength, int expectedWidth, int expectedHeight)
{
	Mat source = src.getMat();
	CV_Assert(!source.empty());

	Size expected;
	double ratioHorizon = static_cast<double>(source.cols) / expectedWidth;
	double ratioVertica = static_cast<double>(source.rows) / expectedHeight;

	if (ratioHorizon <= 1.0 && ratioVertica <= 1.0) expected = Size(expectedWidth, expectedHeight);
	else if (ratioHorizon <= ratioVertica) expected = Size(static_cast<int>(source.cols / ratioVertica), expectedHeight);
	else expected = Size(expectedWidth, static_cast<int>(source.rows / ratioHorizon));

	Mat resized;
	resize(source, resized, expected);

	vector<unsigned char> buf;
	imencode(".jpg", resized, buf);
	memcpy(frameData, buf.data(), buf.size());
	frameLength = static_cast<int>(buf.size());
}

long __stdcall VideoCapture_Open(const char* filename)
{
	VideoCapture* capture = new VideoCapture();
	bool opened = capture->open(filename);

	if (opened) return reinterpret_cast<long>(capture);

	capture->release();
	delete capture;
	return 0x0000;
}

bool __stdcall VideoCapture_IsOpened(long handle)
{
	VideoCapture* capture = reinterpret_cast<VideoCapture*>(handle);
	return capture->isOpened();
}

void __stdcall VideoCapture_Release(long handle)
{
	VideoCapture* capture = reinterpret_cast<VideoCapture*>(handle);
	capture->release();
	delete capture;
}

bool __stdcall VideoCapture_Grab(long handle)
{
	VideoCapture* capture = reinterpret_cast<VideoCapture*>(handle);
	return capture->grab();
}

bool __stdcall VideoCapture_Retrieve(long handle, unsigned char* frameData, int& frameLength, int expectedWidth, int expectedHeight, int channel)
{
	VideoCapture* capture = reinterpret_cast<VideoCapture*>(handle);

	Mat frame;
	bool retrieved = capture->retrieve(frame, channel);

	if (!retrieved) return false;

	ResizeEncodeImage(frame, frameData, frameLength, expectedWidth, expectedHeight);
	return true;
}

bool __stdcall VideoCapture_Read(long handle, unsigned char* frameData, int& frameLength, int expectedWidth, int expectedHeight)
{
	VideoCapture* capture = reinterpret_cast<VideoCapture*>(handle);

	Mat frame;
	bool retrieved = capture->read(frame);

	if (!retrieved) return false;

	ResizeEncodeImage(frame, frameData, frameLength, expectedWidth, expectedHeight);
	return true;
}

bool __stdcall VideoCapture_Set(long handle, int propId, double value)
{
	VideoCapture* capture = reinterpret_cast<VideoCapture*>(handle);

	return capture->set(propId, value);
}

double __stdcall VideoCapture_Get(long handle, int propId)
{
	VideoCapture* capture = reinterpret_cast<VideoCapture*>(handle);

	return capture->get(propId);
}

long __stdcall VideoWriter_Open(const char* filename, int fourcc, double fps, int frameWidth, int frameHeight, bool isColor)
{
	VideoWriter* writer = new VideoWriter();
	bool opened = writer->open(filename, fourcc, fps, Size(frameWidth, frameHeight), isColor);

	if (opened) return reinterpret_cast<long>(writer);

	writer->release();
	delete writer;
	return 0x0000;
}

bool __stdcall VideoWriter_IsOpened(long handle)
{
	VideoWriter* writer = reinterpret_cast<VideoWriter*>(handle);
	return writer->isOpened();
}

void __stdcall VideoWriter_Release(long handle)
{
	VideoWriter* writer = reinterpret_cast<VideoWriter*>(handle);
	writer->release();
	delete writer;
}

void __stdcall VideoWriter_Write(long handle, unsigned char* frameData, int& frameLength)
{
	VideoWriter* writer = reinterpret_cast<VideoWriter*>(handle);

	Mat buf = Mat(1, frameLength, CV_8U, frameData);
	Mat source = imdecode(buf, IMREAD_COLOR);

	writer->write(source);
}
