#pragma once
#include <windows.h>
#include <stdbool.h>
#include <wchar.h>

#ifndef MANY_LAYER_INTERFACE_H_INCLUDED
#define MANY_LAYER_INTERFACE_H_INCLUDED

typedef struct {
	int width, height;
} Size;

typedef struct {
	HBITMAP bitmapHandle;
	int x, y;
	double scale;
	bool isHidden;
} Image;

typedef struct {
	wchar_t* content;
	int x, y, width, height, weight;
	wchar_t* font;
	COLORREF color;
	bool isHidden;
} Text;

typedef struct _ManyLayer {
	Image* images;
	int imageCount;
	Text* texts;
	int textCount;
	UINT transparentColor;

	HWND _windowHandle;
	HDC _consoleDeviceContextHandle;

	void (*initialize)(struct _ManyLayer*);
	void (*renderAll)(struct _ManyLayer*);
	void (*applyToDeviceContextHandle)(HDC);

	HBITMAP (*getBitmapHandle)(wchar_t* fileName);
} ManyLayer;

#endif
