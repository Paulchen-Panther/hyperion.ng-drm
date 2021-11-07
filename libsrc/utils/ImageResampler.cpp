#include "utils/ImageResampler.h"
#include <utils/ColorSys.h>
#include <utils/Logger.h>

// OpenMP
#include <omp.h>

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

void ImageResampler::processImage(const uint8_t * data, int width, int height, int lineLength, PixelFormat pixelFormat, Image<ColorRgb> &outputImage) const
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

	// calculate the output size
	int outputWidth = (width - _cropLeft - cropRight - (_horizontalDecimation >> 1) + _horizontalDecimation - 1) / _horizontalDecimation;
	int outputHeight = (height - _cropTop - cropBottom - (_verticalDecimation >> 1) + _verticalDecimation - 1) / _verticalDecimation;

	outputImage.resize(outputWidth, outputHeight);

	omp_set_dynamic(0);
	omp_set_num_threads(qMax(QThread::idealThreadCount(), 1));

#pragma omp parallel
	{
		int ySource = 0, xSource = 0, uOffset = 0, vOffset = 0, yOffset;
#pragma omp for collapse(2) private(ySource, xSource, uOffset, vOffset, yOffset)
		for ( int yDest = 0; yDest < outputHeight; ++yDest)
		{
			for ( int xDest = 0; xDest < outputWidth; ++xDest)
			{
				ySource = _cropTop + (_verticalDecimation >> 1) + yDest * _verticalDecimation;
				xSource = _cropLeft + (_horizontalDecimation >> 1) + xDest * _horizontalDecimation;

				yOffset = lineLength * ySource;

				if (pixelFormat == PixelFormat::NV12)
				{
					uOffset = (height + ySource / 2) * lineLength;
				}
				else if (pixelFormat == PixelFormat::I420)
				{
					uOffset = width * height + (ySource/2) * width/2;
					vOffset = width * height * 1.25 + (ySource/2) * width/2;
				}

				int xDestFlip = xDest, yDestFlip = yDest;
				if (_flipMode != FlipMode::NO_CHANGE)
				{
					switch (_flipMode)
					{
						case FlipMode::HORIZONTAL:
							xDestFlip = xDest;
							yDestFlip = outputHeight-yDest-1;
							break;
						case FlipMode::VERTICAL:
							xDestFlip = outputWidth-xDest-1;
							yDestFlip = yDest;
							break;
						case FlipMode::BOTH:
							xDestFlip = outputWidth-xDest-1;
							yDestFlip = outputHeight-yDest-1;
							break;
						case FlipMode::NO_CHANGE:
							break;
					}
				}

				ColorRgb &rgb = outputImage(xDestFlip, yDestFlip);
				switch (pixelFormat)
				{
					case PixelFormat::UYVY:
					{
						int index = yOffset + (xSource << 1);
						uint8_t y = data[index+1];
						uint8_t u = ((xSource&1) == 0) ? data[index  ] : data[index-2];
						uint8_t v = ((xSource&1) == 0) ? data[index+2] : data[index  ];
						ColorSys::yuv2rgb(y, u, v, rgb.red, rgb.green, rgb.blue);
					}
					break;
					case PixelFormat::YUYV:
					{
						int index = yOffset + (xSource << 1);
						uint8_t y = data[index];
						uint8_t u = ((xSource&1) == 0) ? data[index+1] : data[index-1];
						uint8_t v = ((xSource&1) == 0) ? data[index+3] : data[index+1];
						ColorSys::yuv2rgb(y, u, v, rgb.red, rgb.green, rgb.blue);
					}
					break;
					case PixelFormat::BGR16:
					{
						int index = yOffset + (xSource << 1);
						rgb.blue  = (data[index] & 0x1f) << 3;
						rgb.green = (((data[index+1] & 0x7) << 3) | (data[index] & 0xE0) >> 5) << 2;
						rgb.red   = (data[index+1] & 0xF8);
					}
					break;
					case PixelFormat::BGR24:
					{
						int index = yOffset + (xSource << 1) + xSource;
						rgb.blue  = data[index  ];
						rgb.green = data[index+1];
						rgb.red   = data[index+2];
					}
					break;
					case PixelFormat::RGB32:
					{
						int index = yOffset + (xSource << 2);
						rgb.red   = data[index  ];
						rgb.green = data[index+1];
						rgb.blue  = data[index+2];
					}
					break;
					case PixelFormat::BGR32:
					{
						int index = yOffset + (xSource << 2);
						rgb.blue  = data[index  ];
						rgb.green = data[index+1];
						rgb.red   = data[index+2];
					}
					break;
					case PixelFormat::NV12:
					{
						uint8_t y = data[yOffset + xSource];
						uint8_t u = data[uOffset + ((xSource >> 1) << 1)];
						uint8_t v = data[uOffset + ((xSource >> 1) << 1) + 1];
						ColorSys::yuv2rgb(y, u, v, rgb.red, rgb.green, rgb.blue);
					}
					break;
					case PixelFormat::I420:
					{
						int y = data[yOffset + xSource];
						int u = data[uOffset + (xSource >> 1)];
						int v = data[vOffset + (xSource >> 1)];
						ColorSys::yuv2rgb(y, u, v, rgb.red, rgb.green, rgb.blue);
						break;
					}
					break;
#ifdef HAVE_TURBO_JPEG
					case PixelFormat::MJPEG:
					break;
#endif
					case PixelFormat::NO_CHANGE:
						Error(Logger::getInstance("ImageResampler"), "Invalid pixel format given");
					break;
				}
			}
		}
	}
}