#include "Queen.h"

Queen::Queen()
{
	kt = 0;
	quan_trang_den = 0;
	lan = 0;
}

void Queen::ShowWayQueen(SDL_Surface* des)
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

bool Queen::Move(SDL_Event events)
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
			if (quan_trang_den == white) trang[x][y] = queen;
			else den[x][y] = queen;
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
			if (quan_trang_den == white) trang[x][y] = queen;
			else den[x][y] = queen;
			lan = 0;
			return true;
		}
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
				trang[x][y] = queen;
			}
			else
			{
				den[x][y] = 0;
				x -= j;
				y -= j;
				den[x][y] = queen;
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
				trang[x][y] = queen;
			}
			else
			{
				den[x][y] = 0;
				x += j;
				y -= j;
				den[x][y] = queen;
			}
			lan = 0;
			return true;
		}
	}
	return false;
}

bool Queen::Eat(SDL_Event events)
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
				if (quan_trang_den == white) trang[x][y] = queen;
				else den[x][y] = queen;
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
				if (quan_trang_den == white) trang[x][y] = queen;
				else den[x][y] = queen;
				lan = 0;
				return true;
			}
			else return false;
		}
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
					trang[x][y] = queen;
				}
				else
				{
					den[x][y] = 0;
					x -= j;
					y -= j;
					den[x][y] = queen;
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
					trang[x][y] = queen;
				}
				else
				{
					den[x][y] = 0;
					x += j;
					y -= j;
					den[x][y] = queen;
				}
				lan = 0;
				return true;
			}
			else return false;
		}
	}
	return false;
}