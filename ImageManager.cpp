#include "framework.h"

ImageManager* ImageManager::instance = NULL;

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
	for (auto image : totalImage)
		delete image.second;
}

ImageManager* ImageManager::GetInstance()
{
	return instance;
}

void ImageManager::Create()
{
	instance = new ImageManager();
}

void ImageManager::Delete()
{
	delete instance;
}

Image* ImageManager::Add(wstring fileName, int width, int height, COLORREF color)
{
	Image* image = Find(fileName);

	if (image != NULL)
		return image;

	image = new Image(fileName, width, height, color);

	totalImage.insert({ fileName, image });

	return image;
}

Image* ImageManager::Add(wstring fileName, int width, int height, int frameX, int frameY, COLORREF color)
{
	Image* image = Find(fileName);

	if (image != NULL)
		return image;

	image = new Image(fileName, width, height, frameX, frameY, color);

	totalImage.insert({ fileName, image });

	return image;
}

Image* ImageManager::Find(wstring key)
{
	auto iter = totalImage.find(key);

	if (iter != totalImage.end())
		return iter->second;

	return NULL;
}
