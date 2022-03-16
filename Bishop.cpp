#include "Bishop.h"

Bishop::Bishop()
{
	kt = 0;
	quan_trang_den = 0;
	lan = 0;
	x = 0;
	y = 0;
	for (int i = 0; i < 8; i++)
		trai[i] = phai[i] = false;
}

void Bishop::ShowWayBishop(SDL_Surface* des)
{
	if (lan == 0)
	{
		for (int i = 0; i < 8; i++)
			trai[i] = phai[i] = false;
		int k = x > (7 - y) ? (7 - y) : x;
		int j = 0;
		for (int i = 1; i <= k; i++)
			if (trang[x - i][y + i] == 0 && den[x - i][y + i] == 0)
			{
				if ((x - i) % 2 == (y + i) % 2) cheo_phai[j].Loading("square_1.png");
				else cheo_phai[j].Loading("square_2.png");
				cheo_phai[j].SetRect(i * 50 + rect_.x, rect_.y - i * 50);
				cheo_phai[j].Show(des);
				phai[j] = true;
				++j;
			}
			else if (quan_trang_den == white && den[x - i][y + i] != 0 || quan_trang_den == black && trang[x - i][y + i] != 0)
			{
				if ((x - i) % 2 == (y + i) % 2) cheo_phai[j].Loading("square_1.png");
				else cheo_phai[j].Loading("square_2.png");
				cheo_phai[j].SetRect(i * 50 + rect_.x, rect_.y - i * 50);
				cheo_phai[j].Show(des);
				phai[j] = true;
				++j;
				break;
			}
			else break;
		k = (7 - x) > y ? y : (7 - x);
		for (int i = 1; i <= k; i++)
			if (trang[x + i][y - i] == 0 && den[x + i][y - i] == 0)
			{
				if ((x + i) % 2 == (y - i) % 2) cheo_phai[j].Loading("square_1.png");
				else cheo_phai[j].Loading("square_2.png");
				cheo_phai[j].SetRect(rect_.x - i * 50, rect_.y + i * 50);
				cheo_phai[j].Show(des);
				phai[j] = true;
				++j;
			}
			else if (quan_trang_den == white && den[x + i][y - i] != 0 || quan_trang_den == black && trang[x + i][y - i] != 0)
			{
				if ((x + i) % 2 == (y - i) % 2) cheo_phai[j].Loading("square_1.png");
				else cheo_phai[j].Loading("square_2.png");
				cheo_phai[j].SetRect(rect_.x - i * 50, rect_.y + i * 50);
				cheo_phai[j].Show(des);
				phai[j] = true;
				++j;
				break;
			}
			else break;
		j = 0;
		k = x > y ? y : x;
		for (int i = 1; i <= k; i++)
			if (trang[x - i][y - i] == 0 && den[x - i][y - i] == 0)
			{
				if ((x - i) % 2 == (y - i) % 2) cheo_trai[j].Loading("square_1.png");
				else cheo_trai[j].Loading("square_2.png");
				cheo_trai[j].SetRect(rect_.x - i * 50, rect_.y - i * 50);
				cheo_trai[j].Show(des);
				trai[j] = true;
				++j;
			}
			else if (quan_trang_den == white && den[x - i][y - i] != 0 || quan_trang_den == black && trang[x - i][y - i] != 0)
			{
				if ((x - i) % 2 == (y - i) % 2) cheo_trai[j].Loading("square_1.png");
				else cheo_trai[j].Loading("square_2.png");
				cheo_trai[j].SetRect(rect_.x - i * 50, rect_.y - i * 50);
				cheo_trai[j].Show(des);
				trai[j] = true;
				++j;
				break;
			}
			else break;
		k = (7 - x) > (7 - y) ? (7 - y) : (7 - x);
		for (int i = 1; i <= k; i++)
			if (trang[x + i][y + i] == 0 && den[x + i][y + i] == 0)
			{
				if ((x + i) % 2 == (y + i) % 2) cheo_trai[j].Loading("square_1.png");
				else cheo_trai[j].Loading("square_2.png");
				cheo_trai[j].SetRect(rect_.x + i * 50, rect_.y + i * 50);
				cheo_trai[j].Show(des);
				trai[j] = true;
				++j;
			}
			else if (quan_trang_den == white && den[x + i][y + i] != 0 || quan_trang_den == black && trang[x + i][y + i] != 0)
			{
				if ((x + i) % 2 == (y + i) % 2) cheo_trai[j].Loading("square_1.png");
				else cheo_trai[j].Loading("square_2.png");
				cheo_trai[j].SetRect(rect_.x + i * 50, rect_.y + i * 50);
				cheo_trai[j].Show(des);
				trai[j] = true;
				++j;
				break;
			}
			else break;
		lan = 1;
	}
	else lan = 0;
}

bool Bishop::Move(SDL_Event events)
{
	if (lan == 0) return false;
	for (int i = 0; i < 8; i++)
	{
		if (cheo_trai[i].HandleInputAction(events))
		{
			if (trai[i] == false) return false;
			int j = (rect_.x - cheo_trai[i].GetRect().x) / 50;
			if (quan_trang_den == white && den[x - j][y - j] != 0) return false;
			if (quan_trang_den == black && trang[x - j][y - j] != 0) return false;
			rect_.x = cheo_trai[i].GetRect().x;
			rect_.y = cheo_trai[i].GetRect().y;
			if (quan_trang_den == white)
			{
				trang[x][y] = 0;
				x -= j;
				y -= j;
				trang[x][y] = bishop;
			}
			else
			{
				den[x][y] = 0;
				x -= j;
				y -= j;
				den[x][y] = bishop;
			}
			lan = 0;
			return true;
		}
		if (cheo_phai[i].HandleInputAction(events))
		{
			if (phai[i] == false) return false;
			int j = (rect_.x - cheo_phai[i].GetRect().x) / 50;
			if (quan_trang_den == white && den[x + j][y - j] != 0) return false;
			if (quan_trang_den == black && trang[x + j][y - j] != 0) return false;
			rect_.x = cheo_phai[i].GetRect().x;
			rect_.y = cheo_phai[i].GetRect().y;
			if (quan_trang_den == white)
			{
				trang[x][y] = 0;
				x += j;
				y -= j;
				trang[x][y] = bishop;
			}
			else
			{
				den[x][y] = 0;
				x += j;
				y -= j;
				den[x][y] = bishop;
			}
			lan = 0;
			return true;
		}
	}
	return false;
}

bool Bishop::Eat(SDL_Event events)
{
	if (lan == 0) return false;
	for (int i = 0; i < 8; i++)
	{
		if (cheo_trai[i].HandleInputAction(events))
		{
			if (trai[i] == false) return false;
			int j = (rect_.x - cheo_trai[i].GetRect().x) / 50;
			if (quan_trang_den == white && den[x - j][y - j] != 0 || quan_trang_den == black && trang[x - j][y - j] != 0)
			{
				rect_.x = cheo_trai[i].GetRect().x;
				rect_.y = cheo_trai[i].GetRect().y;
				if (quan_trang_den == white)
				{
					trang[x][y] = 0;
					x -= j;
					y -= j;
					trang[x][y] = bishop;
				}
				else
				{
					den[x][y] = 0;
					x -= j;
					y -= j;
					den[x][y] = bishop;
				}
				lan = 0;
				return true;
			}
			else return false;
		}
		if (cheo_phai[i].HandleInputAction(events))
		{
			if (phai[i] == false) return false;
			int j = (rect_.x - cheo_phai[i].GetRect().x) / 50;
			if (quan_trang_den == white && den[x + j][y - j] != 0 || quan_trang_den == black && trang[x + j][y - j] != 0)
			{
				rect_.x = cheo_phai[i].GetRect().x;
				rect_.y = cheo_phai[i].GetRect().y;
				if (quan_trang_den == white)
				{
					trang[x][y] = 0;
					x += j;
					y -= j;
					trang[x][y] = bishop;
				}
				else
				{
					den[x][y] = 0;
					x += j;
					y -= j;
					den[x][y] = bishop;
				}
				lan = 0;
				return true;
			}
			else return false;
		}
	}
	return false;
}