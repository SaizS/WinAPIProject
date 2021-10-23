#include "framework.h"

Image::Image(HWND hWnd, wstring fileName, int width, int height, COLORREF color)
{
	HDC hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);
	alphaBitmap = CreateCompatibleBitmap(hdc, width, height);
	ReleaseDC(hWnd, hdc);

	bitmap = (HBITMAP)LoadImage(hInst, fileName.c_str(), IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);

	SelectObject(memDC, bitmap);
	SelectObject(alphaMemDC, alphaBitmap);

	originSize = { width, height };
	frameSize = { width, height };
	frame = { 1, 1 };

	transColor = color;
}

Image::Image(HWND hWnd, wstring fileName, int width, int height, int frameX, int frameY, COLORREF color)
{
	HDC hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);
	alphaBitmap = CreateCompatibleBitmap(hdc, width, height);
	ReleaseDC(hWnd, hdc);

	bitmap = (HBITMAP)LoadImage(hInst, fileName.c_str(), IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);

	SelectObject(memDC, bitmap);
	SelectObject(alphaMemDC, alphaBitmap);

	originSize = { width, height };
	frameSize = { width / frameX, height /frameY};
	frame = { frameX, frameY };

	transColor = color;
}

Image::Image(wstring fileName, int width, int height, COLORREF color)
{	
	HDC hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	ReleaseDC(hWnd, hdc);

	bitmap = (HBITMAP)LoadImage(hInst, fileName.c_str(), IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);

	SelectObject(memDC, bitmap);

	originSize = { width, height };
	frameSize = { width, height };
	frame = { 1, 1 };

	transColor = color;
}

Image::Image(wstring fileName, int width, int height, int frameX, int frameY, COLORREF color)
{
	HDC hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	ReleaseDC(hWnd, hdc);

	bitmap = (HBITMAP)LoadImage(hInst, fileName.c_str(), IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);

	SelectObject(memDC, bitmap);

	originSize = { width, height };
	frameSize = { width / frameX, height / frameY };
	frame = { frameX, frameY };

	transColor = color;
}

Image::Image()
{
}

Image::~Image()
{
	DeleteDC(memDC);
	DeleteObject(bitmap);
}

void Image::Render(HDC hdc, Rect rc)
{
	GdiTransparentBlt(hdc, 
		(int)(rc.pos.x - rc.HalfSize().x),
		(int)(rc.pos.y - rc.HalfSize().y),
		(int)rc.size.x, (int)rc.size.y,
		memDC, 0, 0, frameSize.x, frameSize.y, transColor);
}

void Image::Render(HDC hdc, Rect rc, POINT curFrame)
{
	GdiTransparentBlt(hdc,
		(int)(rc.pos.x - rc.HalfSize().x),
		(int)(rc.pos.y - rc.HalfSize().y),
		(int)rc.size.x, (int)rc.size.y,
		memDC,
		frameSize.x * curFrame.x,
		frameSize.y * curFrame.y,
		frameSize.x, frameSize.y, transColor);
}

void Image::Render(HDC hdc, Vector pos)
{
	BitBlt(hdc,
		(int)(pos.x - originSize.x * 0.5f), (int)(pos.y - originSize.y * 0.5f),
		(int)originSize.x, (int)originSize.y,
		memDC, 0, 0, SRCCOPY);
}

void Image::Render(HDC hdc, Rect rc, POINT curFrame, int alpha)
{
	blendFunc.SourceConstantAlpha = (BYTE)alpha;

	BitBlt(alphaMemDC, frameSize.x * curFrame.x, frameSize.y * curFrame.y,
		frameSize.x, frameSize.y, hdc, (int)rc.Left(), (int)rc.Top(), SRCCOPY);

	GdiTransparentBlt(alphaMemDC, 0, 0, originSize.x, originSize.y, memDC, 0, 0,
		originSize.x, originSize.y, transColor);

	GdiAlphaBlend(hdc, (int)rc.Left(), (int)rc.Top(), (int)rc.size.x, (int)rc.size.y
		, alphaMemDC, (int)(frameSize.x * curFrame.x), (int)(frameSize.y * curFrame.y), (int)frameSize.x, (int)frameSize.y, blendFunc);
}
