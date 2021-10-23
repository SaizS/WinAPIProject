#pragma once

class ImageManager
{
private:
	static ImageManager* instance;

	map<wstring, Image*> totalImage;

	ImageManager();
	~ImageManager();

public:
	static ImageManager* GetInstance();
	static void Create();
	static void Delete();

	Image* Add(wstring fileName, int width, int height, COLORREF color = MAGENTA);
	Image* Add(wstring fileName, int width, int height, int frameX, int frameY, COLORREF color = MAGENTA);

	Image* Find(wstring key);

};