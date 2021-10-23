#pragma once

class Rect;
class Vector;

class Image
{
private:
	HDC memDC;
	HBITMAP bitmap;

	POINT originSize;
	POINT frameSize;
	POINT frame;

	COLORREF transColor;
	BLENDFUNCTION blendFunc;

	HDC alphaMemDC;
	HBITMAP alphaBitmap;

public:
	Image(HWND hWnd, wstring fileName, int width, int height, COLORREF color = MAGENTA);
	Image(HWND hWnd, wstring fileName, int width, int height, int frameX, int frameY,
		COLORREF color = MAGENTA);
	Image(wstring fileName, int width, int height, COLORREF color = MAGENTA);
	Image(wstring fileName, int width, int height, int frameX, int frameY,
		COLORREF color = MAGENTA);
	Image();

	~Image();

	void Render(HDC hdc, Rect rc);
	void Render(HDC hdc, Rect rc, POINT curFrame);
	void Render(HDC hdc, Vector pos);
	void Render(HDC hdc, Rect rc, POINT curFrame, int alpha);

	POINT GetFrame() { return frame; }
	POINT GetSize() { return frameSize; }

	HDC GetMemDC() { return memDC; }
};