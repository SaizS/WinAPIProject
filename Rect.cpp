#include "framework.h"

Rect::Rect() : pos(0.0f, 0.0f), size(0.0f, 0.0f)
{
}

Rect::Rect(float x, float y, float width, float height)
	: pos(x, y), size(width, height)
{
}

Rect::Rect(Vector pos, Vector size)
	: pos(pos), size(size)
{
}

void Rect::SetRect(float left, float top, float right, float bottom)
{
	pos.x = (left + right) * 0.5f;
	pos.y = (top + bottom) * 0.5f;
	size.x = right - left;
	size.y = bottom - top;
}

bool Rect::Collision(Rect rect)
{
	float minX = min(Right(), rect.Right());
	float maxX = max(Left(), rect.Left());

	float minY = min(Bottom(), rect.Bottom());
	float maxY = max(Top(), rect.Top());

	Vector temp(minX - maxX, minY - maxY);	

	if (temp.x > 0 && temp.y > 0)
		return true;

	return false;
}

bool Rect::Collision(Rect* rect)
{
	float minX = min(Right(), rect->Right());
	float maxX = max(Left(), rect->Left());

	float minY = min(Bottom(), rect->Bottom());
	float maxY = max(Top(), rect->Top());

	Vector temp(minX - maxX, minY - maxY);

	if (temp.x > 0 && temp.y > 0)
	{
		if (temp.x > temp.y)//상하충돌
		{
			if (pos.y > rect->pos.y)//받은 객체가 위에 있다.
			{
				rect->pos.y -= temp.y;
			}
			else
			{
				rect->pos.y += temp.y;
			}
		}
		else//좌우충돌
		{
			if (pos.x > rect->pos.x)//받은 객체가 왼쪽에 있다.
			{
				rect->pos.x -= temp.x;
			}
			else
			{
				rect->pos.x += temp.x;
			}
		}
		return true;
	}		

	return false;
}

bool Rect::Collision(Rect* dest, Rect* src)
{
	float minX = min(Right(), src->Right());
	float maxX = max(Left(), src->Left());

	float minY = min(Bottom(), src->Bottom());
	float maxY = max(Top(), src->Top());

	Vector temp(minX - maxX, minY - maxY);

	if (temp.x > 0 && temp.y > 0)
	{
		if (temp.x > temp.y)//상하충돌
		{
			if (pos.y > src->pos.y)//받은 객체가 위에 있다.
			{
				src->pos.y -= temp.y;
			}
			else
			{
				src->pos.y += temp.y;
			}
		}
		else//좌우충돌
		{
			if (pos.x > src->pos.x)//받은 객체가 왼쪽에 있다.
			{
				src->pos.x -= temp.x;
			}
			else
			{
				src->pos.x += temp.x;
			}
		}

		dest->SetRect(maxX, maxY, minX, minY);
		return true;
	}

	return false;
}

bool Rect::Collision(Vector pos)
{
	if (pos.x > Left() && pos.x < Right())
	{
		if (pos.y > Top() && pos.y < Bottom())
		{
			return true;
		}
	}
	return false;
}
