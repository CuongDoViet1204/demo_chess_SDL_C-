#include "Castle.h"

Castle::Castle()
{
	kt = 0;
	quan_trang_den = 0;
	lan = 0;
	x = 0;
	y = 0;
	for (int i = 0; i < 8; i++)
		chieu_doc[i] = chieu_ngang[i] = false;
}

void Castle::ShowWayCastle(SDL_Surface* des)
{
	if (lan == 0)
	{
		for (int i = 0; i < 8; i++)
			chieu_doc[i] = chieu_ngang[i] = false;
		for (int i = x - 1; i >= 0; i--)
			if (trang[i][y] == 0 && den[i][y] == 0)
			{
				if (i % 2 == y % 2)	doc[i].Loading("square_1.png");
				else doc[i].Loading("square_2.png");
				doc[i].SetRect(rect_.x, rect_.y - (x - i) * 50);
				doc[i].Show(des);
				chieu_doc[i] = true;
			}
			else if (quan_trang_den == white && den[i][y] != 0 || quan_trang_den == black && trang[i][y] != 0)
			{
				if (i % 2 == y % 2)	doc[i].Loading("square_1.png");
				else doc[i].Loading("square_2.png");
				doc[i].SetRect(rect_.x, rect_.y - (x - i) * 50);
				doc[i].Show(des);
				chieu_doc[i] = true;
				break;
			}
			else break;
		for (int i = x + 1; i < 8; i++)
			if (trang[i][y] == 0 && den[i][y] == 0)
			{
				if (i % 2 == y % 2)	doc[i].Loading("square_1.png");
				else doc[i].Loading("square_2.png");
				doc[i].SetRect(rect_.x, rect_.y + (i - x) * 50);
				doc[i].Show(des);
				chieu_doc[i] = true;
			}
			else if (quan_trang_den == white && den[i][y] != 0 || quan_trang_den == black && trang[i][y] != 0)
			{
				if (i % 2 == y % 2)	doc[i].Loading("square_1.png");
				else doc[i].Loading("square_2.png");
				doc[i].SetRect(rect_.x, rect_.y + (i - x) * 50);
				doc[i].Show(des);
				chieu_doc[i] = true;
				break;
			}
			else break;
		for (int i = y + 1; i < 8; i++)
			if (trang[x][i] == 0 && den[x][i] == 0)
			{
				if (i % 2 == x % 2) ngang[i].Loading("square_1.png");
				else ngang[i].Loading("square_2.png");
				ngang[i].SetRect(rect_.x + (i - y) * 50, rect_.y);
				ngang[i].Show(des);
				chieu_ngang[i] = true;
			}
			else if (quan_trang_den == white && den[x][i] != 0 || quan_trang_den == black && trang[x][i] != 0)
			{
				if (i % 2 == x % 2) ngang[i].Loading("square_1.png");
				else ngang[i].Loading("square_2.png");
				ngang[i].SetRect(rect_.x + (i - y) * 50, rect_.y);
				ngang[i].Show(des);
				chieu_ngang[i] = true;
				break;
			}
			else break;
		for (int i = y - 1; i >= 0; i--)
			if (trang[x][i] == 0 && den[x][i] == 0)
			{
				if (i % 2 == x % 2) ngang[i].Loading("square_1.png");
				else ngang[i].Loading("square_2.png");
				ngang[i].SetRect(rect_.x - (y - i) * 50, rect_.y);
				ngang[i].Show(des);
				chieu_ngang[i] = true;
			}
			else if (quan_trang_den == white && den[x][i] != 0 || quan_trang_den == black && trang[x][i] != 0)
			{
				if (i % 2 == x % 2) ngang[i].Loading("square_1.png");
				else ngang[i].Loading("square_2.png");
				ngang[i].SetRect(rect_.x - (y - i) * 50, rect_.y);
				ngang[i].Show(des);
				chieu_ngang[i] = true;
				break;
			}
			else break;
		lan = 1;
	}
	else lan = 0;
}

bool Castle::Move(SDL_Event events)
{
	if (lan == 0) return false;
	for (int i = 0; i < 8; i++)
	{
		if (ngang[i].HandleInputAction(events))
		{
			if (chieu_ngang[i] == false) return false;
			if (quan_trang_den == white && den[x][i] != 0) return false;
			if (quan_trang_den == black && trang[x][i] != 0) return false;
			rect_.x = ngang[i].GetRect().x;
			if (quan_trang_den == white) trang[x][y] = 0;
			else den[x][y] = 0;
			y = i;
			if (quan_trang_den == white) trang[x][y] = castle;
			else den[x][y] = castle;
			lan = 0;
			return true;
		}
		if (doc[i].HandleInputAction(events))
		{
			if (quan_trang_den == white && den[i][y] != 0) return false;
			if (quan_trang_den == black && trang[i][y] != 0) return false;
			if (chieu_doc[i] == false) return false;
			rect_.y = doc[i].GetRect().y;
			if (quan_trang_den == white) trang[x][y] = 0;
			else den[x][y] = 0;
			x = i;
			if (quan_trang_den == white) trang[x][y] = castle;
			else den[x][y] = castle;
			lan = 0;
			return true;
		}
	}
	return false;
}

bool Castle::Eat(SDL_Event events)
{
	if (lan == 0) return false;
	for (int i = 0; i < 8; i++)
	{
		if (ngang[i].HandleInputAction(events))
		{
			if (chieu_ngang[i] == false) return false;
			if (quan_trang_den == white && den[x][i] != 0 || quan_trang_den == black && trang[x][i] != 0)
			{
				rect_.x = ngang[i].GetRect().x;
				if (quan_trang_den == white) trang[x][y] = 0;
				else den[x][y] = 0;
				y = i;
				if (quan_trang_den == white) trang[x][y] = castle;
				else den[x][y] = castle;
				lan = 0;
				return true;
			}
			else return false;
		}
		if (doc[i].HandleInputAction(events))
		{
			if (quan_trang_den == white && den[i][y] != 0 || quan_trang_den == black && trang[i][y] != 0)
			{
				if (chieu_doc[i] == false) return false;
				rect_.y = doc[i].GetRect().y;
				if (quan_trang_den == white) trang[x][y] = 0;
				else den[x][y] = 0;
				x = i;
				if (quan_trang_den == white) trang[x][y] = castle;
				else den[x][y] = castle;
				lan = 0;
				return true;
			}
			else return false;
		}
	}
	return false;
}