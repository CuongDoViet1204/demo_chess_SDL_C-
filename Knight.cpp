#include "Knight.h"

Knight::Knight()
{
	kt = 0;
	quan_trang_den = 0;
	lan = 0;
	x = 0;
	y = 0;
	for (int i = 0; i < 8; i++)
		check[i] = false;
}

void Knight::ShowWayKnight(SDL_Surface* des)
{
	if (lan == 0)
	{
		for (int i = 0; i < 8; i++)
			check[i] = false;
		if (x >= 2 && y >= 1)
			if (quan_trang_den == white && trang[x - 2][y - 1] == 0 || quan_trang_den == black && den[x - 2][y - 1] == 0)
			{
				if ((x - 2) % 2 == (y - 1) % 2) p[0].Loading("square_1.png");
				else p[0].Loading("square_2.png");
				p[0].SetRect(rect_.x - SIZE_SQUARE, rect_.y - 2 * SIZE_SQUARE);
				p[0].Show(des);
				check[0] = true;
			}
		if (x >= 2 && y <= 6)
			if (quan_trang_den == white && trang[x - 2][y + 1] == 0 || quan_trang_den == black && den[x - 2][y + 1] == 0)
			{
				if ((x - 2) % 2 == (y + 1) % 2) p[1].Loading("square_1.png");
				else p[1].Loading("square_2.png");
				p[1].SetRect(rect_.x + SIZE_SQUARE, rect_.y - 2 * SIZE_SQUARE);
				p[1].Show(des);
				check[1] = true;
			}
		if (x >= 1 && y <= 5)
			if (quan_trang_den == white && trang[x - 1][y + 2] == 0 || quan_trang_den == black && den[x - 1][y + 2] == 0)
			{
				if ((x - 1) % 2 == (y + 2) % 2) p[2].Loading("square_1.png");
				else p[2].Loading("square_2.png");
				p[2].SetRect(rect_.x + 2 * SIZE_SQUARE, rect_.y - SIZE_SQUARE);
				p[2].Show(des);
				check[2] = true;
			}
		if (x <= 6 && y <= 5)
			if (quan_trang_den == white && trang[x + 1][y + 2] == 0 || quan_trang_den == black && den[x + 1][y + 2] == 0)
			{
				if ((x + 1) % 2 == (y + 2) % 2) p[3].Loading("square_1.png");
				else p[3].Loading("square_2.png");
				p[3].SetRect(rect_.x + 2 * SIZE_SQUARE, rect_.y + SIZE_SQUARE);
				p[3].Show(des);
				check[3] = true;
			}
		if (x <= 5 && y <= 6)
			if (quan_trang_den == white && trang[x + 2][y + 1] == 0 || quan_trang_den == black && den[x + 2][y + 1] == 0)
			{
				if ((x + 2) % 2 == (y + 1) % 2) p[4].Loading("square_1.png");
				else p[4].Loading("square_2.png");
				p[4].SetRect(rect_.x + SIZE_SQUARE, rect_.y + 2 * SIZE_SQUARE);
				p[4].Show(des);
				check[4] = true;
			}
		if (x <= 5 && y >= 1)
			if (quan_trang_den == white && trang[x + 2][y - 1] == 0 || quan_trang_den == black && den[x + 2][y - 1] == 0)
			{
				if ((x + 2) % 2 == (y - 1) % 2) p[5].Loading("square_1.png");
				else p[5].Loading("square_2.png");
				p[5].SetRect(rect_.x - SIZE_SQUARE, rect_.y + 2 * SIZE_SQUARE);
				p[5].Show(des);
				check[5] = true;
			}
		if (x <= 6 && y >= 2)
			if (quan_trang_den == white && trang[x + 1][y - 2] == 0 || quan_trang_den == black && den[x + 1][y - 2] == 0)
			{
				if ((x + 1) % 2 == (y - 2) % 2) p[6].Loading("square_1.png");
				else p[6].Loading("square_2.png");
				p[6].SetRect(rect_.x - 2 * SIZE_SQUARE, rect_.y + SIZE_SQUARE);
				p[6].Show(des);
				check[6] = true;
			}
		if (x >= 1 && y >= 2)
			if (quan_trang_den == white && trang[x - 1][y - 2] == 0 || quan_trang_den == black && den[x - 1][y - 2] == 0)
			{
				if ((x - 1) % 2 == (y - 2) % 2) p[7].Loading("square_1.png");
				else p[7].Loading("square_2.png");
				p[7].SetRect(rect_.x - 2 * SIZE_SQUARE, rect_.y - SIZE_SQUARE);
				p[7].Show(des);
				check[7] = true;
			}
		lan = 1;
	}
	else lan = 0;
}

bool Knight::Move(SDL_Event events)
{
	if (lan == 0) return false;
	for (int i = 0; i < 8; i++)
		if (p[i].HandleInputAction(events))
		{
			if (check[i] == false) return false;
			switch (i)
			{
			case 0: if (quan_trang_den == white && den[x - 2][y - 1] != 0) return false;
					if (quan_trang_den == black && trang[x - 2][y - 1] != 0) return false;
					rect_.x = p[i].GetRect().x;
					rect_.y = p[i].GetRect().y;
					if (quan_trang_den == white) trang[x][y] = 0;
					else den[x][y] = 0;
					x -= 2;
					y -= 1;
					if (quan_trang_den == white) trang[x][y] = knight;
					else den[x][y] = knight;
					lan = 0;
					return true;
			case 1: if (quan_trang_den == white && den[x - 2][y + 1] != 0) return false;
					if (quan_trang_den == black && trang[x - 2][y + 1] != 0) return false;
					rect_.x = p[i].GetRect().x;
					rect_.y = p[i].GetRect().y;
					if (quan_trang_den == white) trang[x][y] = 0;
					else den[x][y] = 0;
					x -= 2;
					y += 1;
					if (quan_trang_den == white) trang[x][y] = knight;
					else den[x][y] = knight;
					lan = 0;
					return true;
			case 2: if (quan_trang_den == white && den[x - 1][y + 2] != 0) return false;
					if (quan_trang_den == black && trang[x - 1][y + 2] != 0) return false;
					rect_.x = p[i].GetRect().x;
					rect_.y = p[i].GetRect().y;
					if (quan_trang_den == white) trang[x][y] = 0;
					else den[x][y] = 0;
					x -= 1;
					y += 2;
					if (quan_trang_den == white) trang[x][y] = knight;
					else den[x][y] = knight;
					lan = 0;
					return true;
			case 3: if (quan_trang_den == white && den[x + 1][y + 2] != 0) return false;
					if (quan_trang_den == black && trang[x + 1][y + 2] != 0) return false;
					rect_.x = p[i].GetRect().x;
					rect_.y = p[i].GetRect().y;
					if (quan_trang_den == white) trang[x][y] = 0;
					else den[x][y] = 0;
					x += 1;
					y += 2;
					if (quan_trang_den == white) trang[x][y] = knight;
					else den[x][y] = knight;
					lan = 0;
					return true;
			case 4: if (quan_trang_den == white && den[x + 2][y + 1] != 0) return false;
					if (quan_trang_den == black && trang[x + 2][y + 1] != 0) return false;
					rect_.x = p[i].GetRect().x;
					rect_.y = p[i].GetRect().y;
					if (quan_trang_den == white) trang[x][y] = 0;
					else den[x][y] = 0;
					x += 2;
					y += 1;
					if (quan_trang_den == white) trang[x][y] = knight;
					else den[x][y] = knight;
					lan = 0;
					return true;
			case 5: if (quan_trang_den == white && den[x + 2][y - 1] != 0) return false;
					if (quan_trang_den == black && trang[x + 2][y - 1] != 0) return false;
					rect_.x = p[i].GetRect().x;
					rect_.y = p[i].GetRect().y;
					if (quan_trang_den == white) trang[x][y] = 0;
					else den[x][y] = 0;
					x += 2;
					y -= 1;
					if (quan_trang_den == white) trang[x][y] = knight;
					else den[x][y] = knight;
					lan = 0;
					return true;
			case 6: if (quan_trang_den == white && den[x + 1][y - 2] != 0) return false;
					if (quan_trang_den == black && trang[x + 1][y - 2] != 0) return false;
					rect_.x = p[i].GetRect().x;
					rect_.y = p[i].GetRect().y;
					if (quan_trang_den == white) trang[x][y] = 0;
					else den[x][y] = 0;
					x += 1;
					y -= 2;
					if (quan_trang_den == white) trang[x][y] = knight;
					else den[x][y] = knight;
					lan = 0;
					return true;
			case 7: if (quan_trang_den == white && den[x - 1][y - 2] != 0) return false;
					if (quan_trang_den == black && trang[x - 1][y - 2] != 0) return false;
					rect_.x = p[i].GetRect().x;
					rect_.y = p[i].GetRect().y;
					if (quan_trang_den == white) trang[x][y] = 0;
					else den[x][y] = 0;
					x -= 1;
					y -= 2;
					if (quan_trang_den == white) trang[x][y] = knight;
					else den[x][y] = knight;
					lan = 0;
					return true;
			}
		}
	return false;
}

bool Knight::Eat(SDL_Event events)
{
	if (lan == 0) return false;
	for (int i = 0; i < 8; i++)
		if (p[i].HandleInputAction(events))
		{
			if (check[i] == false) return false;
			switch (i)
			{
			case 0: if (quan_trang_den == white && den[x - 2][y - 1] != 0 || quan_trang_den == black && trang[x - 2][y - 1] != 0) 
					{
						rect_.x = p[i].GetRect().x;
						rect_.y = p[i].GetRect().y;
						if (quan_trang_den == white) trang[x][y] = 0;
						else den[x][y] = 0;
						x -= 2;
						y -= 1;
						if (quan_trang_den == white) trang[x][y] = knight;
						else den[x][y] = knight;
						lan = 0;
						return true;
					}		
			case 1: if (quan_trang_den == white && den[x - 2][y + 1] != 0 || quan_trang_den == black && trang[x - 2][y + 1] != 0)
					{
						rect_.x = p[i].GetRect().x;
						rect_.y = p[i].GetRect().y;
						if (quan_trang_den == white) trang[x][y] = 0;
						else den[x][y] = 0;
						x -= 2;
						y += 1;
						if (quan_trang_den == white) trang[x][y] = knight;
						else den[x][y] = knight;
						lan = 0;
						return true;
					}			
			case 2: if (quan_trang_den == white && den[x - 1][y + 2] != 0 || quan_trang_den == black && trang[x - 1][y + 2] != 0)
					{
						rect_.x = p[i].GetRect().x;
						rect_.y = p[i].GetRect().y;
						if (quan_trang_den == white) trang[x][y] = 0;
						else den[x][y] = 0;
						x -= 1;
						y += 2;
						if (quan_trang_den == white) trang[x][y] = knight;
						else den[x][y] = knight;
						lan = 0;
						return true;
					}				
			case 3: if (quan_trang_den == white && den[x + 1][y + 2] != 0 || quan_trang_den == black && trang[x + 1][y + 2] != 0)
					{
						rect_.x = p[i].GetRect().x;
						rect_.y = p[i].GetRect().y;
						if (quan_trang_den == white) trang[x][y] = 0;
						else den[x][y] = 0;
						x += 1;
						y += 2;
						if (quan_trang_den == white) trang[x][y] = knight;
						else den[x][y] = knight;
						lan = 0;
						return true;
					}				
			case 4: if (quan_trang_den == white && den[x + 2][y + 1] != 0 || quan_trang_den == black && trang[x + 2][y + 1] != 0)
					{
						rect_.x = p[i].GetRect().x;
						rect_.y = p[i].GetRect().y;
						if (quan_trang_den == white) trang[x][y] = 0;
						else den[x][y] = 0;
						x += 2;
						y += 1;
						if (quan_trang_den == white) trang[x][y] = knight;
						else den[x][y] = knight;
						lan = 0;
						return true;
					}				
			case 5: if (quan_trang_den == white && den[x + 2][y - 1] != 0 || quan_trang_den == black && trang[x + 2][y - 1] != 0)
					{
						rect_.x = p[i].GetRect().x;
						rect_.y = p[i].GetRect().y;
						if (quan_trang_den == white) trang[x][y] = 0;
						else den[x][y] = 0;
						x += 2;
						y -= 1;
						if (quan_trang_den == white) trang[x][y] = knight;
						else den[x][y] = knight;
						lan = 0;
						return true;
					}			
			case 6: if (quan_trang_den == white && den[x + 1][y - 2] != 0 || quan_trang_den == black && trang[x + 1][y - 2] != 0)
					{
						rect_.x = p[i].GetRect().x;
						rect_.y = p[i].GetRect().y;
						if (quan_trang_den == white) trang[x][y] = 0;
						else den[x][y] = 0;
						x += 1;
						y -= 2;
						if (quan_trang_den == white) trang[x][y] = knight;
						else den[x][y] = knight;
						lan = 0;
						return true;
					}		
			case 7: if (quan_trang_den == white && den[x - 1][y - 2] != 0 || quan_trang_den == black && trang[x - 1][y - 2] != 0)
					{
						rect_.x = p[i].GetRect().x;
						rect_.y = p[i].GetRect().y;
						if (quan_trang_den == white) trang[x][y] = 0;
						else den[x][y] = 0;
						x -= 1;
						y -= 2;
						if (quan_trang_den == white) trang[x][y] = knight;
						else den[x][y] = knight;
						lan = 0;
						return true;
					}			
			}
		}
	return false;
}