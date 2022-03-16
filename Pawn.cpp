#include "Pawn.h"

Pawn::Pawn()
{
	kt = 0;
	quan_trang_den = 0;
	lan = 0;
	luot = 0;
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;
	x = 0;
	y = 0;
	for (int i = 0; i < 4; i++)
		p[i].SetRect(0, 0);
}

void Pawn::ShowWayPawn(SDL_Surface* des)
{
	if (lan == 0)
	{
		if (quan_trang_den == black)
		{
			if (x + 1 < 8 && x + 1 >= 0 && y < 8 && y >= 0)
				if (trang[x + 1][y] == 0 && den[x + 1][y] == 0)
				{
					if (kt == white) p[tren_1].Loading("square_2.png");
					else p[tren_1].Loading("square_1.png");
					p[tren_1].SetRect(rect_.x, rect_.y + 50);
					p[tren_1].Show(des);
				}
			if (y - 1 >= 0 && y - 1 < 8 && x + 1 >= 0 && x + 1 < 8)
				if (trang[x + 1][y - 1] != 0)
				{
					if (kt == white) p[cheo_trai].Loading("square_1.png");
					else p[cheo_trai].Loading("square_2.png");
					p[cheo_trai].SetRect(rect_.x - 50, rect_.y + 50);
					p[cheo_trai].Show(des);
				}
			if (y + 1 < 8 && y + 1 >= 0 && x + 1 >= 0 && x + 1 < 8)
				if (trang[x + 1][y + 1] != 0)
				{
					if (kt == white) p[cheo_phai].Loading("square_1.png");
					else p[cheo_phai].Loading("square_2.png");
					p[cheo_phai].SetRect(rect_.x + 50, rect_.y + 50);
					p[cheo_phai].Show(des);
				}
		}
		else
		{
			if (y >= 0 && y < 8 && x - 1 >= 0 && x - 1 < 8)
				if (den[x - 1][y] == 0 && trang[x - 1][y] == 0)
				{
					if (kt == white) p[tren_1].Loading("square_2.png");
					else p[tren_1].Loading("square_1.png");
					p[tren_1].SetRect(rect_.x, rect_.y - 50);
					p[tren_1].Show(des);
				}
			if (y - 1 >= 0 && y - 1 < 8 && x - 1 >= 0 && x - 1 < 8)
				if (den[x - 1][y - 1] != 0)
				{
					if (kt == white) p[cheo_trai].Loading("square_1.png");
					else p[cheo_trai].Loading("square_2.png");
					p[cheo_trai].SetRect(rect_.x - 50, rect_.y - 50);
					p[cheo_trai].Show(des);
				}
			if (y + 1 >= 0 && y + 1 < 8 && x - 1 >= 0 && x - 1 < 8)
				if (den[x - 1][y + 1] != 0)
				{
					if (kt == white) p[cheo_phai].Loading("square_1.png");
					else p[cheo_phai].Loading("square_2.png");
					p[cheo_phai].SetRect(rect_.x + 50, rect_.y - 50);
					p[cheo_phai].Show(des);
				}
		}
		if (luot == 0)
		{
			if (quan_trang_den == black)
			{
				if (x + 2 < 8 && x + 2 >= 0 && y < 8 && y >= 0)
					if (trang[x + 2][y] == 0 && trang[x + 1][y] == 0 && den[x + 2][y] == 0 && den[x + 1][y] == 0)
					{
						if (kt == white) p[tren_2].Loading("square_1.png");
						else p[tren_2].Loading("square_2.png");
						p[tren_2].SetRect(rect_.x, rect_.y + 100);
						p[tren_2].Show(des);
					}
			}
			else
			{
				if (y >= 0 && y < 8 && x - 2 >= 0 && x - 2 < 8)
					if (trang[x - 2][y] == 0 && trang[x - 1][y] == 0 && den[x - 2][y] == 0 && den[x - 1][y] == 0)
					{
						if (kt == white) p[tren_2].Loading("square_1.png");
						else p[tren_2].Loading("square_2.png");
						p[tren_2].SetRect(rect_.x, rect_.y - 100);
						p[tren_2].Show(des);
					}
			}
		}
		lan = 1;
	}
	else lan = 0;
}

bool Pawn::Move(SDL_Event events)
{
	if (lan != 1) return false;
	if (quan_trang_den == black && x == 7 && y >= 0 && y < 8) return false;
	if (quan_trang_den == white && x == 0 && y >= 0 && y < 8) return false;
	if (p[tren_1].HandleInputAction(events))
	{
		rect_.x = p[tren_1].GetRect().x;
		rect_.y = p[tren_1].GetRect().y;
		if (quan_trang_den == white)
		{
			trang[x][y] = 0;
			x--;
			trang[x][y] = pawn;
		}
		else
		{
			den[x][y] = 0;
			x++;
			den[x][y] = pawn;		
		}
		if (kt == white)
			kt = black;
		else
			kt = white;
		lan = 0;
		luot = 1;
		return true;
	}	
	if (luot == 0)
		if (p[tren_2].HandleInputAction(events))
		{
			rect_.x = p[tren_2].GetRect().x;
			rect_.y = p[tren_2].GetRect().y;
			if (quan_trang_den == white)
			{
				trang[x][y] = 0;
				x -= 2;
				trang[x][y] = pawn;
			}
			else
			{
				den[x][y] = 0;
				x += 2;
				den[x][y] = pawn;
			}
			lan = 0;
			luot = 1;
			return true;
		}
	return false;
}

bool Pawn::Eat(SDL_Event events)
{
	if (lan != 1) return false;
	if (quan_trang_den == black && x == 7 && y >= 0 && y < 8) return false;
	if (quan_trang_den == white && x == 0 && y >= 0 && y < 8) return false;
	if (p[cheo_trai].HandleInputAction(events))
	{
		rect_.x = p[cheo_trai].GetRect().x;
		rect_.y = p[cheo_trai].GetRect().y;
		if (quan_trang_den == white)
		{
			trang[x][y] = 0;
			x--;
			y--;
			trang[x][y] = pawn;
		}
		else
		{
			den[x][y] = 0;
			x++;
			y--;
			den[x][y] = pawn;
		}
		lan = 0;
		luot = 1;
		return true;
	}
	if (p[cheo_phai].HandleInputAction(events))
	{
		rect_.x = p[cheo_phai].GetRect().x;
		rect_.y = p[cheo_phai].GetRect().y;
		if (quan_trang_den == white)
		{
			trang[x][y] = 0;
			x--;
			y++;
			trang[x][y] = pawn;
		}
		else
		{
			den[x][y] = 0;
			x++;
			y++;
			den[x][y] = pawn;
		}
		lan = 0;
		luot = 1;
		return true;
	}
	return false;
}