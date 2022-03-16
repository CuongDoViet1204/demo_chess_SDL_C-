#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 675;
const int SCREEN_BPP = 32;
const int SIZE_SQUARE = 50;
const int POS_X = 250;
const int POS_Y = 150;
const int SIZE_MAP = 8;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Event g_even;
static SDL_Surface* g_img_menu = NULL;
static SDL_Surface* g_img_end = NULL;	

enum { white = 1, black = 2};
enum { pawn = 1, castle = 2, bishop = 3, knight = 4, queen = 5, king = 6 };
static int dem_trang = 0;
static int dem_black = 0;

namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void CleanUp();
	int ShowMenu(SDL_Surface* des, TTF_Font* font);
	bool CheckFocusWithRect(int x, int y, const SDL_Rect& rect);
	int ShowUpdate(SDL_Surface* des, int value);
	int ShowEnd(SDL_Surface* des, TTF_Font* font, int person);
}

#endif 

