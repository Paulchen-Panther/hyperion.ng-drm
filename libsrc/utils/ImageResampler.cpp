#include "utils/ImageResampler.h"
#include <utils/ColorSys.h>
#include <utils/Logger.h>

// libyuv includes
#include <libyuv.h>

ImageResampler::ImageResampler()
	: _horizontalDecimation(8)
	, _verticalDecimation(8)
	, _cropLeft(0)
	, _cropRight(0)
	, _cropTop(0)
	, _cropBottom(0)
	, _videoMode(VideoMode::VIDEO_2D)
	, _flipMode(FlipMode::NO_CHANGE)
{

}

void ImageResampler::setCropping(int cropLeft, int cropRight, int cropTop, int cropBottom)
{
	_cropLeft   = cropLeft;
	_cropRight  = cropRight;
	_cropTop    = cropTop;
	_cropBottom = cropBottom;
}

void ImageResampler::processImage(const uint8_t * data, int width, int height, int size, PixelFormat pixelFormat, Image<ColorRgb> &outputImage) const
{
	int cropRight  = _cropRight;
	int cropBottom = _cropBottom;

	// handle 3D mode
	switch (_videoMode)
	{
		case VideoMode::VIDEO_3DSBS:
			cropRight = width >> 1;
			break;
		case VideoMode::VIDEO_3DTAB:
			cropBottom = height >> 1;
			break;
		default:
			break;
	}

	// calculate the cropped size
	int croppedWidth = width - _cropLeft - cropRight;
	int croppedHeight = height - _cropTop - cropBottom;

	uint8_t* croppedARGB = (uint8_t*)malloc((size_t)croppedWidth * croppedHeight * 4);
	libyuv::ConvertToARGB(
		data,
		size,
		croppedARGB,
		croppedWidth * 4,
		_cropLeft,
		_cropTop,
		width,
		height,
		croppedWidth,
		croppedHeight,
		libyuv::kRotate0,
		GetFOURCCForPixelFormat(pixelFormat)
	);

	// calculate the scaled size
	int outputWidth = (croppedWidth - (_horizontalDecimation >> 1) + _horizontalDecimation - 1) / _horizontalDecimation;
	int outputHeight = (croppedHeight - (_verticalDecimation >> 1) + _verticalDecimation - 1) / _verticalDecimation;

	uint8_t* scaledARGB = (uint8_t*)malloc((size_t)outputWidth * outputHeight * 4);
	libyuv::ARGBScale(
		croppedARGB,
		croppedWidth * 4,
		(_flipMode == FlipMode::VERTICAL   || _flipMode == FlipMode::BOTH) ? -abs(croppedWidth)  : croppedWidth,
		(_flipMode == FlipMode::HORIZONTAL || _flipMode == FlipMode::BOTH) ? -abs(croppedHeight) : croppedHeight,
		scaledARGB,
		outputWidth * 4,
		outputWidth,
		outputHeight,
		libyuv::kFilterNone
	);

	outputImage.resize(outputWidth, outputHeight);
	libyuv::ARGBToRAW(scaledARGB, outputWidth * 4, (uint8_t*)outputImage.memptr(), outputWidth * 3, outputWidth, outputHeight);

	free(croppedARGB);
	free(scaledARGB);
}
