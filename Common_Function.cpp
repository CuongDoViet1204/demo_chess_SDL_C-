#include "Common_Function.h"
#include "TextObject.h"

SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path)
{
	SDL_Surface* load_image = NULL;
	SDL_Surface* optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str());
	if (load_image != NULL)
	{
		optimize_image = SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);
		if (optimize_image != NULL)
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 88, 88, 88);
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
	}
	return optimize_image;
}

SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset = { x, y };
	SDL_BlitSurface(src, NULL, des, &offset);
	return offset;
}

void SDLCommonFunc::CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
	SDL_FreeSurface(g_img_menu);
	SDL_FreeSurface(g_img_end);
}

bool SDLCommonFunc::CheckFocusWithRect(int x, int y, const SDL_Rect& rect)
{
	if (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
		return true;
	return false;
}

int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font)
{
	g_img_menu = LoadImage("open.jpg");
	if (g_img_menu == NULL) return 1;
	const int KmenuItemNum = 2;
	SDL_Rect pos_arr[KmenuItemNum];
	pos_arr[0].x = 200;
	pos_arr[0].y = 200;
	pos_arr[1].x = 200;
	pos_arr[1].y = 300;
	TextObject text_menu[KmenuItemNum];
	text_menu[0].SetText("Play Game");
	text_menu[0].SetColor(TextObject::WHITE_TEXT);
	text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);
	text_menu[1].SetText("Exit");
	text_menu[1].SetColor(TextObject::WHITE_TEXT);
	text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

	bool selected[KmenuItemNum] = { false, false };
	int xm = 0;
	int ym = 0;
	SDL_Event m_event;
	while (true)
	{
		SDLCommonFunc::ApplySurface(g_img_menu, des, 0, 0);
		for (int i = 0; i < KmenuItemNum; i++)
			text_menu[i].CreateGameText(font, des);
		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT: return 1;
			case SDL_MOUSEMOTION:
			{
				xm = m_event.motion.x;
				ym = m_event.motion.y;
				for (int i = 0; i < KmenuItemNum; i++)
				{
					if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
					{
						if (selected[i] == false)
						{
							selected[i] = true;
							text_menu[i].SetColor(TextObject::BLACK_TEXT);
						}
					}
					else
					{
						if (selected[i] == true)
						{
							selected[i] = false;
							text_menu[i].SetColor(TextObject::WHITE_TEXT);
						}
					}
				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				xm = m_event.button.x;
				ym = m_event.button.y;
				for (int i = 0; i < KmenuItemNum; i++)
				{
					if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
						return i;
				}
			}
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
					return 1;
			default: break;
			}
			SDL_Flip(des);
		}
	}
	return 1;
}

int SDLCommonFunc::ShowEnd(SDL_Surface* des, TTF_Font* font, int person)
{
	g_img_end = LoadImage("end.png");
	if (g_img_end == NULL) return 0;
	TextObject textEnd[3];
	if (person == 1)
		textEnd[0].SetText("Player 1 Win!!!");
	else
		textEnd[0].SetText("Player 2 Win!!!");
	textEnd[1].SetText("Play Again");
	textEnd[2].SetText("Exit");
	for (int i = 0; i < 3; i++)
		textEnd[i].SetColor(TextObject::WHITE_TEXT);
	textEnd[0].SetRect(100, 150);
	textEnd[1].SetRect(150, 250);
	textEnd[2].SetRect(150, 350);
	bool selected[2] = { false, false };
	int xm = 0;
	int ym = 0;
	SDL_Event m_event;
	while (true)
	{
		SDLCommonFunc::ApplySurface(g_img_end, des, 0, 0);
		for (int i = 0; i < 3; i++)
			textEnd[i].CreateGameText(font, des);
		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT: return 0;
			case SDL_MOUSEMOTION:
			{
				xm = m_event.motion.x;
				ym = m_event.motion.y;
				for (int i = 1; i < 3; i++)
				{
					if (CheckFocusWithRect(xm, ym, textEnd[i].GetRect()))
					{
						if (selected[i - 1] == false)
						{
							selected[i - 1] = true;
							textEnd[i].SetColor(TextObject::RED_TEXT);
						}
					}
					else
					{
						if (selected[i - 1] == true)
						{
							selected[i - 1] = false;
							textEnd[i].SetColor(TextObject::WHITE_TEXT);
						}
					}
				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				xm = m_event.button.x;
				ym = m_event.button.y;
				for (int i = 1; i < 3; i++)
				{
					if (CheckFocusWithRect(xm, ym, textEnd[i].GetRect()))
						if (i == 2)
							return 0;
						else return 1;
				}
			}
			default: break;
			}
			SDL_Flip(des);
		}
	}
	return 0;
}

int SDLCommonFunc::ShowUpdate(SDL_Surface* des, int value)
{
	SDL_Surface* img_update = LoadImage("bk_Gr_update.png");
	if (img_update == NULL) return 0;
	SDL_Surface* img_chess;
	bool check[4] = { false, false, false, false };
	SDL_Event m_event;
	BaseObject update[4];
	while (true)
	{
		std::string s[4];
		s[0] = "quan_xe_";
		s[1] = "quan_tinh_";
		s[2] = "quan_ma_";
		s[3] = "quan_hau_";
		if (value == white)
			for (int i = 0; i < 4; i++)
				s[i] += "trang_";
		else
			for (int i = 0; i < 4; i++)
				s[i] += "den_";
		SDLCommonFunc::ApplySurface(img_update, des, 270, 287);
		for (int i = 0; i < 4; i++)
			if (check[i] == true)
			{
				s[i] += "2.png";
				update[i].Loading(s[i].c_str());
				update[i].SetRect(270 + i * 90, 292);
				update[i].Show(des);
			}
			else
			{
				s[i] += "1.png";
				update[i].Loading(s[i].c_str());
				update[i].SetRect(270 + i * 90 + 15, 303);
				update[i].Show(des);
			}
		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT: return 0;
			case SDL_MOUSEMOTION:
			{
				int xm = m_event.motion.x;
				int ym = m_event.motion.y;
				for (int i = 0; i < 4; i++)
					if (CheckFocusWithRect(xm, ym, update[i].GetRect()))
					{
						if (check[i] == false) check[i] = true;
					}
					else
					{
						if (check[i] == true) check[i] = false;
					}
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				if (m_event.button.button == SDL_BUTTON_LEFT)
				{
					int xm = m_event.button.x;
					int ym = m_event.button.y;
					for (int i = 0; i < 4; i++)
						if (CheckFocusWithRect(xm, ym, update[i].GetRect()))
							return i + 2;
				}
				break;
			}
			default: break;
			}
			SDL_Flip(des);
		}
	}
	return 0;
}