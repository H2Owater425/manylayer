#pragma once

#include <windows.h>
#include "ManyLayer.h"

#pragma comment (lib, "msimg32.lib")

#ifndef MANY_LAYER_IMPLEMENTATION_H_INCLUDED
#define MANY_LAYER_IMPLEMENTATION_H_INCLUDED

#define CONSOLE_WIDTH 160
#define CONSOLE_HEIGHT 45

static double RESOLUTION_MULTIPLIER = 1;
int WINDOW_WIDTH, WINDOW_HEIGHT;

inline int getDotPerInch(HWND windowHandle) {
	const FARPROC function = GetProcAddress(GetModuleHandleW(L"user32"), "GetDpiForWindow");

	return function == NULL ? 96 : ((UINT(__stdcall*)(HWND))function)(windowHandle);
}

inline Size getBitmapSize(HBITMAP bitmapHandle) {
	BITMAP bitmap;
	
	GetObjectW(bitmapHandle, sizeof(BITMAP), &bitmap);

	return (Size){ bitmap.bmWidth, bitmap.bmHeight };
}

inline HDC getNewBufferDeviceContextHandle(HDC compatibleDeviceContextHandle) {
	const HDC bufferDeviceContextHandle = CreateCompatibleDC(compatibleDeviceContextHandle);
	const HBITMAP backBitmapHandle = CreateCompatibleBitmap(compatibleDeviceContextHandle, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	SelectObject(bufferDeviceContextHandle, backBitmapHandle);
	DeleteObject(backBitmapHandle);

	return bufferDeviceContextHandle;
}

inline void renderBitmapToBufferDeviceContextHandle(HDC bufferDeviceContextHandle, Image* image, UINT transparentColor) {
	if(image->scale != 0) {
		const HDC bitmapDeviceContextHandle = CreateCompatibleDC(bufferDeviceContextHandle);
		const Size bitmapSize = getBitmapSize(image->bitmapHandle);
		const double scale = image->scale * RESOLUTION_MULTIPLIER;

		SelectObject(bitmapDeviceContextHandle, image->bitmapHandle);

		TransparentBlt(bufferDeviceContextHandle, (int)(image->x * RESOLUTION_MULTIPLIER), (int)(image->y * RESOLUTION_MULTIPLIER), bitmapSize.width * scale, bitmapSize.height * scale, bitmapDeviceContextHandle, 0, 0, bitmapSize.width, bitmapSize.height, transparentColor);
		DeleteDC(bitmapDeviceContextHandle);
	}
}

inline void renderTextToBufferDeviceContextHandle(HDC bufferDeviceContextHandle, Text* text) {
	const HFONT fontHandle = CreateFontW(text->height, text->width, 0, 0, text->weight, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, text->font);
	PAINTSTRUCT paint;
	
	SelectObject(bufferDeviceContextHandle, fontHandle);
	SetBkMode(bufferDeviceContextHandle, TRANSPARENT);
	SetTextColor(bufferDeviceContextHandle, text->color);
	TextOutW(bufferDeviceContextHandle, (int)(text->x * RESOLUTION_MULTIPLIER), (int)(text->y * RESOLUTION_MULTIPLIER), text->content, lstrlenW(text->content));
	EndPaint(GetConsoleWindow(), &paint);
	DeleteObject(fontHandle);
}

inline void applyToDeviceContextHandle(HDC distributionDeviceContextHandle, HDC sourceDeviceContextHandle) {
	BitBlt(distributionDeviceContextHandle, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, sourceDeviceContextHandle, 0, 0, SRCCOPY);
}

inline HDC getRenderedBufferDeviceContext(ManyLayer* manyLayer) {
	const const HDC bufferDeviceContext = getNewBufferDeviceContextHandle(manyLayer->_consoleDeviceContextHandle);

	for(int i = 0; i < manyLayer->imageCount; i++) {
		if(!manyLayer->images[i].isHidden) {
			renderBitmapToBufferDeviceContextHandle(bufferDeviceContext, manyLayer->images + i, manyLayer->transparentColor);
		}
	}

	for(int i = 0; i < manyLayer->textCount; i++) {
		if(!manyLayer->texts[i].isHidden) {
			renderTextToBufferDeviceContextHandle(bufferDeviceContext, manyLayer->texts + i);
		}
	}

	return bufferDeviceContext;
}

inline HBITMAP _getBitmapHandle(wchar_t* fileName) {
	return LoadImageW(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

inline void _renderAll(ManyLayer* manyLayer) {
	const const HDC bufferDeviceContext = getRenderedBufferDeviceContext(manyLayer);
	
	if(manyLayer->applyToDeviceContextHandle != NULL) {
		manyLayer->applyToDeviceContextHandle(bufferDeviceContext);
	}

	applyToDeviceContextHandle(manyLayer->_consoleDeviceContextHandle, bufferDeviceContext);
	DeleteDC(bufferDeviceContext);
}

inline void _initialize(ManyLayer* manyLayer) {
	manyLayer->_windowHandle = GetConsoleWindow();
	manyLayer->_consoleDeviceContextHandle = GetDC(manyLayer->_windowHandle);

	RESOLUTION_MULTIPLIER = getDotPerInch(manyLayer->_windowHandle) / (double)192;
	WINDOW_WIDTH = (int)(CONSOLE_WIDTH * 16 * RESOLUTION_MULTIPLIER);
	WINDOW_HEIGHT = (int)(CONSOLE_HEIGHT * 32 * RESOLUTION_MULTIPLIER);
}

#endif
