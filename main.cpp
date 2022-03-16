#include "Pawn.h"
#include "Castle.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "TextObject.h"
#undef main

static TTF_Font* g_font_text = NULL;
int trang[8][8] = { };
int den[8][8] = { };
BaseObject map[8][8];

void ShowMap()
{
	for (int h = 0; h < SIZE_MAP; h++)
		for (int k = 0; k < SIZE_MAP; k++)
			map[h][k].Show(g_screen);
}

bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL) return false;
	if (TTF_Init() == -1) return false;
	g_font_text = TTF_OpenFont("fontchu.ttf", 60);
	if (g_font_text == NULL) return false;
	return true;
}

template <class A, class B>
void process_eat_white(const A& value1, B* value2, int x, int y)
{
	for (int i = x; i < y; i++)
		if (value2[i].GetX() == value1.GetX() && value2[i].GetY() == value1.GetY())
		{
			den[value1.GetX()][value1.GetY()] = 0;
			int k;
			if (dem_black >= 12)
				k = 12;
			else if (dem_black >= 8)
				k = 11;
			else if (dem_black >= 4)
				k = 10;
			else k = 9;
			value2[i].SetRect(700 + 50 * (dem_black % 4), 50 * k);
			++dem_black;
			break;
		}
}

template <class A, class B>
void process_eat_black(const A& value1, B* value2, int x, int y)
{
	for (int h = x; h < y; h++)
		if (value2[h].GetX() == value1.GetX() && value2[h].GetY() == value1.GetY())
		{
			trang[value1.GetX()][value1.GetY()] = 0;
			int k;
			if (dem_trang >= 12)
				k = 3;
			else if (dem_trang >= 8)
				k = 2;
			else if (dem_trang >= 4)
				k = 1;
			else k = 0;
			value2[h].SetRect(50 * (dem_trang % 4), 50 * k);
			++dem_trang;
			break;
		}
}

template <class A>
void deleteChess(A* value, short& max, int pos)
{
	for (int i = pos; i < max; i++)
		value[i] = value[i + 1];
	--max;
}

template <class A, class B>
void update(A* value, B* value3, short& value1, short& value2, int pos, int wb)
{
	value[value1].SetWB(wb);
	value[value1].SetRect(value3[pos].GetRect().x, value3[pos].GetRect().y);
	value[value1].SetX(value3[pos].GetX());
	value[value1].SetY(value3[pos].GetY());
	deleteChess(value3, value2, pos);
	++value1;
	SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);
	ShowMap();
}

int main(int arc, char* argv[])
{
	if (Init() == false) return 0;
	//Show Menu
	int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_text);
	if (ret_menu == 1) return 0;

	//show background
	g_bkground = SDLCommonFunc::LoadImage("bk_Gr.png");
	if (g_bkground == NULL) return 0;

	//setup map
	for (int i = 0; i < SIZE_MAP; i++)
		if (i % 2 == 0)
			for (int j = 0; j < SIZE_MAP; j += 2)
			{
				map[i][j].Loading("screen_white.png");
				map[i][j].SetRect(POS_X + j * SIZE_SQUARE, POS_Y + i * SIZE_SQUARE);
				map[i][j + 1].Loading("screen_black.png");
				map[i][j + 1].SetRect(POS_X + (j + 1) * SIZE_SQUARE, POS_Y + i * SIZE_SQUARE);
			}
		else
			for (int j = 0; j < SIZE_MAP; j += 2)
			{
				map[i][j].Loading("screen_black.png");
				map[i][j].SetRect(POS_X + j * SIZE_SQUARE, POS_Y + i * SIZE_SQUARE);
				map[i][j + 1].Loading("screen_white.png");
				map[i][j + 1].SetRect(POS_X + (j + 1) * SIZE_SQUARE, POS_Y + i * SIZE_SQUARE);
			}
	bool is_quit = false;
	while (true)
	{
		int luot = 0;
		//init chess
		for (int i = 0; i < 8; i++)
			den[1][i] = trang[6][i] = pawn;
		den[0][0] = den[0][7] = trang[7][0] = trang[7][7] = castle;
		den[0][1] = den[0][6] = trang[7][1] = trang[7][6] = knight;
		den[0][2] = den[0][5] = trang[7][2] = trang[7][5] = bishop;
		den[0][4] = trang[7][4] = king;
		den[0][3] = trang[7][3] = queen;

		//show Pawn
		Pawn chessPawnWhite[8];
		Pawn chessPawnBlack[8];
		short pawnWhite = 8, pawnBlack = 8;
		for (int i = 0; i < 8; i++)
		{
			chessPawnWhite[i].SetWB(white);
			chessPawnWhite[i].SetRect(map[6][i].GetRect().x, map[6][i].GetRect().y);
			chessPawnWhite[i].Loading("quan_tot_trang.png");
			chessPawnWhite[i].SetX(6);
			chessPawnWhite[i].SetY(i);
			chessPawnWhite[i].Show(g_screen);
			if (i % 2 == 0)
				chessPawnWhite[i].SetKt(white);
			else
				chessPawnWhite[i].SetKt(black);
			chessPawnBlack[i].SetWB(black);
			chessPawnBlack[i].SetRect(map[1][i].GetRect().x, map[1][i].GetRect().y);
			chessPawnBlack[i].Loading("quan_tot_den.png");
			chessPawnBlack[i].SetX(1);
			chessPawnBlack[i].SetY(i);
			chessPawnBlack[i].Show(g_screen);
			if (i % 2 == 1)
				chessPawnBlack[i].SetKt(white);
			else
				chessPawnBlack[i].SetKt(black);
		}

		//show Castle
		Castle chessCastleWhite[10];
		Castle chessCastleBlack[10];
		short castleWhite = 2, castleBlack = 2;
		for (int i = 0; i < 2; i++)
		{
			chessCastleWhite[i].SetWB(white);
			chessCastleWhite[i].SetRect(map[7][7 * i].GetRect().x, map[7][7 * i].GetRect().y);
			chessCastleWhite[i].Loading("quan_xe_trang.png");
			chessCastleWhite[i].Show(g_screen);
			chessCastleWhite[i].SetX(7);
			chessCastleWhite[i].SetY(7 * i);
			if (i % 2 == 1)
				chessCastleWhite[i].SetKt(white);
			else
				chessCastleWhite[i].SetKt(black);
			chessCastleBlack[i].SetWB(black);
			chessCastleBlack[i].SetRect(map[0][7 * i].GetRect().x, map[0][7 * i].GetRect().y);
			chessCastleBlack[i].Loading("quan_xe_den.png");
			chessCastleBlack[i].Show(g_screen);
			chessCastleBlack[i].SetX(0);
			chessCastleBlack[i].SetY(7 * i);
			if (i % 2 == 0)
				chessCastleBlack[i].SetKt(white);
			else
				chessCastleBlack[i].SetKt(black);
		}

		//show Knight
		Knight chessKnightWhite[10];
		Knight chessKnightBlack[10];
		short knightWhite = 2, knightBlack = 2;
		for (int i = 0; i < 2; i++)
		{
			chessKnightWhite[i].SetWB(white);
			chessKnightWhite[i].SetRect(map[7][5 * i + 1].GetRect().x, map[7][5 * i + 1].GetRect().y);
			chessKnightWhite[i].Loading("quan_ma_trang.png");
			chessKnightWhite[i].Show(g_screen);
			chessKnightWhite[i].SetX(7);
			chessKnightWhite[i].SetY(5 * i + 1);
			chessKnightBlack[i].SetWB(black);
			chessKnightBlack[i].SetRect(map[0][5 * i + 1].GetRect().x, map[0][5 * i + 1].GetRect().y);
			chessKnightBlack[i].Loading("quan_ma_den.png");
			chessKnightBlack[i].Show(g_screen);
			chessKnightBlack[i].SetX(0);
			chessKnightBlack[i].SetY(5 * i + 1);
		}

		//show Bishop
		Bishop chessBishopWhite[10];
		Bishop chessBishopBlack[10];
		short bishopWhite = 2, bishopBlack = 2;
		for (int i = 0; i < 2; i++)
		{
			chessBishopWhite[i].SetWB(white);
			chessBishopWhite[i].SetRect(map[7][3 * i + 2].GetRect().x, map[7][3 * i + 2].GetRect().y);
			chessBishopWhite[i].Loading("quan_tinh_trang.png");
			chessBishopWhite[i].Show(g_screen);
			chessBishopWhite[i].SetX(7);
			chessBishopWhite[i].SetY(3 * i + 2);
			if (i % 2 == 0)
				chessBishopWhite[i].SetKt(black);
			else chessBishopWhite[i].SetKt(white);
			chessBishopBlack[i].SetWB(black);
			chessBishopBlack[i].SetRect(map[0][3 * i + 2].GetRect().x, map[0][3 * i + 2].GetRect().y);
			chessBishopBlack[i].Loading("quan_tinh_den.png");
			chessBishopBlack[i].Show(g_screen);
			chessBishopBlack[i].SetX(0);
			chessBishopBlack[i].SetY(3 * i + 2);
			if (i % 2 == 1)
				chessBishopBlack[i].SetKt(black);
			else chessBishopBlack[i].SetKt(white);
		}

		//show Queen
		Queen chessQueenWhite[9];
		Queen chessQueenBlack[9];
		short queenWhite = 1, queenBlack = 1;
		chessQueenWhite[0].SetWB(white);
		chessQueenWhite[0].SetRect(map[7][3].GetRect().x, map[7][3].GetRect().y);
		chessQueenWhite[0].Loading("quan_hau_trang.png");
		chessQueenWhite[0].Show(g_screen);
		chessQueenWhite[0].SetX(7);
		chessQueenWhite[0].SetY(3);
		chessQueenBlack[0].SetWB(black);
		chessQueenBlack[0].SetRect(map[0][3].GetRect().x, map[0][3].GetRect().y);
		chessQueenBlack[0].Loading("quan_hau_den.png");
		chessQueenBlack[0].Show(g_screen);
		chessQueenBlack[0].SetX(0);
		chessQueenBlack[0].SetY(3);

		//show King
		King chessKingWhite;
		King chessKingBlack;
		chessKingWhite.SetWB(white);
		chessKingWhite.SetRect(map[7][4].GetRect().x, map[7][4].GetRect().y);
		chessKingWhite.Loading("quan_vua_trang.png");
		chessKingWhite.Show(g_screen);
		chessKingWhite.SetX(7);
		chessKingWhite.SetY(4);
		chessKingBlack.SetWB(black);
		chessKingBlack.SetRect(map[0][4].GetRect().x, map[0][4].GetRect().y);
		chessKingBlack.Loading("quan_vua_den.png");
		chessKingBlack.Show(g_screen);
		chessKingBlack.SetX(0);
		chessKingBlack.SetY(4);

		//---------------------GAME PLAY!!!--------------------------
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);
		ShowMap();
		bool person_1_win = false;
		bool person_2_win = false;
		while (!is_quit)
		{
			while (SDL_PollEvent(&g_even))
			{
				if (g_even.type == SDL_QUIT)
				{
					is_quit = true;
					break;
				}
				//WHITE ROUND
				if (luot == 0)
				{
					//check White Pawn
					for (int i = 0; i < pawnWhite; i++)
					{
						if (chessPawnWhite[i].HandleInputAction(g_even))
						{
							for (int h = 0; h < 10; h++)
							{
								if (h < pawnWhite)
									if (h != i) chessPawnWhite[h].SetLan(0);
								if (h < castleWhite)
									chessCastleWhite[h].SetLan(0);
								if (h < bishopWhite)
									chessBishopWhite[h].SetLan(0);
								if (h < knightWhite)
									chessKnightWhite[h].SetLan(0);
								if (h < queenWhite)
									chessQueenWhite[h].SetLan(0);
								if (h == 0)
									chessKingWhite.SetLan(0);
							}
							ShowMap();
							chessPawnWhite[i].ShowWayPawn(g_screen);
							break;
						}
						else if (chessPawnWhite[i].Move(g_even))
						{
							ShowMap();
							luot = 1;
							break;
						}
						else if (chessPawnWhite[i].Eat(g_even))
						{
							if (den[chessPawnWhite[i].GetX()][chessPawnWhite[i].GetY()] == pawn)
								process_eat_white(chessPawnWhite[i], chessPawnBlack, 0, pawnBlack);
							else if (den[chessPawnWhite[i].GetX()][chessPawnWhite[i].GetY()] == castle)
								process_eat_white(chessPawnWhite[i], chessCastleBlack, 0, castleBlack);
							else if (den[chessPawnWhite[i].GetX()][chessPawnWhite[i].GetY()] == knight)
								process_eat_white(chessPawnWhite[i], chessKnightBlack, 0, knightBlack);
							else if (den[chessPawnWhite[i].GetX()][chessPawnWhite[i].GetY()] == bishop)
								process_eat_white(chessPawnWhite[i], chessBishopBlack, 0, bishopBlack);
							else if (den[chessPawnWhite[i].GetX()][chessPawnWhite[i].GetY()] == queen)
								process_eat_white(chessPawnWhite[i], chessQueenBlack, 0, queenBlack);
							else if (den[chessPawnWhite[i].GetX()][chessPawnWhite[i].GetY()] == king)
								person_1_win = true;
							luot = 1;
							ShowMap();
							break;
						}
					}

					//check White Castle
					for (int i = 0; i < castleWhite; i++)
					{
						if (chessCastleWhite[i].HandleInputAction(g_even))
						{
							for (int h = 0; h < 10; h++)
							{
								if (h < pawnWhite)
									chessPawnWhite[h].SetLan(0);
								if (h < castleWhite)
									if (h != i) chessCastleWhite[h].SetLan(0);
								if (h < bishopWhite)
									chessBishopWhite[h].SetLan(0);
								if (h < knightWhite)
									chessKnightWhite[h].SetLan(0);
								if (h < queenWhite)
									chessQueenWhite[h].SetLan(0);
								if (h == 0)
									chessKingWhite.SetLan(0);
							}
							ShowMap();
							chessCastleWhite[i].ShowWayCastle(g_screen);
							break;
						}
						else if (chessCastleWhite[i].Move(g_even))
						{
							ShowMap();
							luot = 1;
							break;
						}
						else if (chessCastleWhite[i].Eat(g_even))
						{
							if (den[chessCastleWhite[i].GetX()][chessCastleWhite[i].GetY()] == pawn)
								process_eat_white(chessCastleWhite[i], chessPawnBlack, 0, pawnBlack);
							else if (den[chessCastleWhite[i].GetX()][chessCastleWhite[i].GetY()] == castle)
								process_eat_white(chessCastleWhite[i], chessCastleBlack, 0, castleBlack);
							else if (den[chessCastleWhite[i].GetX()][chessCastleWhite[i].GetY()] == knight)
								process_eat_white(chessCastleWhite[i], chessKnightBlack, 0, knightBlack);
							else if (den[chessCastleWhite[i].GetX()][chessCastleWhite[i].GetY()] == bishop)
								process_eat_white(chessCastleWhite[i], chessBishopBlack, 0, bishopBlack);
							else if (den[chessCastleWhite[i].GetX()][chessCastleWhite[i].GetY()] == queen)
								process_eat_white(chessCastleWhite[i], chessQueenBlack, 0, queenBlack);
							else if (den[chessCastleWhite[i].GetX()][chessCastleWhite[i].GetY()] == king)
								person_1_win = true;
							luot = 1;
							ShowMap();
							break;
						}
					}

					//check White Bishop
					for (int i = 0; i < bishopWhite; i++)
					{
						if (chessBishopWhite[i].HandleInputAction(g_even))
						{
							for (int h = 0; h < 10; h++)
							{
								if (h < pawnWhite)
									chessPawnWhite[h].SetLan(0);
								if (h < castleWhite)
									chessCastleWhite[h].SetLan(0);
								if (h < bishopWhite)
									if (h != i) chessBishopWhite[h].SetLan(0);
								if (h < knightWhite)
									chessKnightWhite[h].SetLan(0);
								if (h < queenWhite)
									chessQueenWhite[h].SetLan(0);
								if (h == 0)
									chessKingWhite.SetLan(0);
							}
							ShowMap();
							chessBishopWhite[i].ShowWayBishop(g_screen);
							break;
						}
						else if (chessBishopWhite[i].Move(g_even))
						{
							ShowMap();
							luot = 1;
							break;
						}
						else if (chessBishopWhite[i].Eat(g_even))
						{
							if (den[chessBishopWhite[i].GetX()][chessBishopWhite[i].GetY()] == pawn)
								process_eat_white(chessBishopWhite[i], chessPawnBlack, 0, pawnBlack);
							else if (den[chessBishopWhite[i].GetX()][chessBishopWhite[i].GetY()] == castle)
								process_eat_white(chessBishopWhite[i], chessCastleBlack, 0, castleBlack);
							else if (den[chessBishopWhite[i].GetX()][chessBishopWhite[i].GetY()] == knight)
								process_eat_white(chessBishopWhite[i], chessKnightBlack, 0, knightBlack);
							else if (den[chessBishopWhite[i].GetX()][chessBishopWhite[i].GetY()] == bishop)
								process_eat_white(chessBishopWhite[i], chessBishopBlack, 0, bishopBlack);
							else if (den[chessBishopWhite[i].GetX()][chessBishopWhite[i].GetY()] == queen)
								process_eat_white(chessBishopWhite[i], chessQueenBlack, 0, queenBlack);
							else if (den[chessBishopWhite[i].GetX()][chessBishopWhite[i].GetY()] == king)
								person_1_win = true;
							luot = 1;
							ShowMap();
							break;
						}
					}

					//check White Knight
					for (int i = 0; i < knightWhite; i++)
					{
						if (chessKnightWhite[i].HandleInputAction(g_even))
						{
							for (int h = 0; h < 10; h++)
							{
								if (h < pawnWhite)
									chessPawnWhite[h].SetLan(0);
								if (h < castleWhite)
									chessCastleWhite[h].SetLan(0);
								if (h < bishopWhite)
									chessBishopWhite[h].SetLan(0);
								if (h < knightWhite)
									if (h != i) chessKnightWhite[h].SetLan(0);
								if (h < queenWhite)
									chessQueenWhite[h].SetLan(0);
								if (h == 0)
									chessKingWhite.SetLan(0);
							}
							ShowMap();
							chessKnightWhite[i].ShowWayKnight(g_screen);
							break;
						}
						else if (chessKnightWhite[i].Move(g_even))
						{
							ShowMap();
							luot = 1;
							break;
						}
						else if (chessKnightWhite[i].Eat(g_even))
						{
							if (den[chessKnightWhite[i].GetX()][chessKnightWhite[i].GetY()] == pawn)
								process_eat_white(chessKnightWhite[i], chessPawnBlack, 0, pawnBlack);
							else if (den[chessKnightWhite[i].GetX()][chessKnightWhite[i].GetY()] == castle)
								process_eat_white(chessKnightWhite[i], chessCastleBlack, 0, castleBlack);
							else if (den[chessKnightWhite[i].GetX()][chessKnightWhite[i].GetY()] == knight)
								process_eat_white(chessKnightWhite[i], chessKnightBlack, 0, knightBlack);
							else if (den[chessKnightWhite[i].GetX()][chessKnightWhite[i].GetY()] == bishop)
								process_eat_white(chessKnightWhite[i], chessBishopBlack, 0, bishopBlack);
							else if (den[chessKnightWhite[i].GetX()][chessKnightWhite[i].GetY()] == queen)
								process_eat_white(chessKnightWhite[i], chessQueenBlack, 0, queenBlack);
							else if (den[chessKnightWhite[i].GetX()][chessKnightWhite[i].GetY()] == king)
								person_1_win = true;
							luot = 1;
							ShowMap();
							break;
						}
					}

					//check White Queen
					for (int i = 0; i < queenWhite; i++)
					{
						if (chessQueenWhite[i].HandleInputAction(g_even))
						{
							for (int h = 0; h < 10; h++)
							{
								if (h < pawnWhite)
									chessPawnWhite[h].SetLan(0);
								if (h < castleWhite)
									chessCastleWhite[h].SetLan(0);
								if (h < bishopWhite)
									chessBishopWhite[h].SetLan(0);
								if (h < knightWhite)
									chessKnightWhite[h].SetLan(0);
								if (h < queenWhite)
									if (h != i) chessQueenWhite[h].SetLan(0);
								if (h == 0)
									chessKingWhite.SetLan(0);
							}
							ShowMap();
							chessQueenWhite[i].ShowWayQueen(g_screen);
							break;
						}
						else if (chessQueenWhite[i].Move(g_even))
						{
							ShowMap();
							luot = 1;
							break;
						}
						else if (chessQueenWhite[i].Eat(g_even))
						{
							if (den[chessQueenWhite[i].GetX()][chessQueenWhite[i].GetY()] == pawn)
								process_eat_white(chessQueenWhite[i], chessPawnBlack, 0, pawnBlack);
							else if (den[chessQueenWhite[i].GetX()][chessQueenWhite[i].GetY()] == castle)
								process_eat_white(chessQueenWhite[i], chessCastleBlack, 0, castleBlack);
							else if (den[chessQueenWhite[i].GetX()][chessQueenWhite[i].GetY()] == knight)
								process_eat_white(chessQueenWhite[i], chessKnightBlack, 0, knightBlack);
							else if (den[chessQueenWhite[i].GetX()][chessQueenWhite[i].GetY()] == bishop)
								process_eat_white(chessQueenWhite[i], chessBishopBlack, 0, bishopBlack);
							else if (den[chessQueenWhite[i].GetX()][chessQueenWhite[i].GetY()] == queen)
								process_eat_white(chessQueenWhite[i], chessQueenBlack, 0, queenBlack);
							else if (den[chessQueenWhite[i].GetX()][chessQueenWhite[i].GetY()] == king)
								person_1_win = true;
							luot = 1;
							ShowMap();
							break;
						}
					}

					//check White King
					if (chessKingWhite.HandleInputAction(g_even))
					{
						for (int h = 0; h < 10; h++)
						{
							if (h < pawnWhite)
								chessPawnWhite[h].SetLan(0);
							if (h < castleWhite)
								chessCastleWhite[h].SetLan(0);
							if (h < bishopWhite)
								chessBishopWhite[h].SetLan(0);
							if (h < knightWhite)
								chessKnightWhite[h].SetLan(0);
							if (h < queenWhite)
								chessQueenWhite[h].SetLan(0);
						}
						ShowMap();
						chessKingWhite.ShowWayKing(g_screen);
					}
					else if (chessKingWhite.Move(g_even))
					{
						ShowMap();
						luot = 1;
					}
					else if (chessKingWhite.Eat(g_even))
					{
						if (den[chessKingWhite.GetX()][chessKingWhite.GetY()] == pawn)
							process_eat_white(chessKingWhite, chessPawnBlack, 0, pawnBlack);
						else if (den[chessKingWhite.GetX()][chessKingWhite.GetY()] == castle)
							process_eat_white(chessKingWhite, chessCastleBlack, 0, castleBlack);
						else if (den[chessKingWhite.GetX()][chessKingWhite.GetY()] == knight)
							process_eat_white(chessKingWhite, chessKnightBlack, 0, knightBlack);
						else if (den[chessKingWhite.GetX()][chessKingWhite.GetY()] == bishop)
							process_eat_white(chessKingWhite, chessBishopBlack, 0, bishopBlack);
						else if (den[chessKingWhite.GetX()][chessKingWhite.GetY()] == queen)
							process_eat_white(chessKingWhite, chessQueenBlack, 0, queenBlack);
						else if (den[chessKingWhite.GetX()][chessKingWhite.GetY()] == king)
							person_1_win = true;
						luot = 1;
						ShowMap();
					}
				}

				//BLACK ROUND
				else
				{
					//check Black Pawn
					for (int i = 0; i < pawnBlack; i++)
					{
						if (chessPawnBlack[i].HandleInputAction(g_even))
						{
							for (int h = 0; h < 10; h++)
							{
								if (h < pawnBlack)
									if (h != i) chessPawnBlack[h].SetLan(0);
								if (h < castleBlack)
									chessCastleBlack[h].SetLan(0);
								if (h < bishopBlack)
									chessBishopBlack[h].SetLan(0);
								if (h < knightBlack)
									chessKnightBlack[h].SetLan(0);
								if (h < queenBlack)
									chessQueenBlack[h].SetLan(0);
								if (h == 0)
									chessKingBlack.SetLan(0);
							}
							ShowMap();
							chessPawnBlack[i].ShowWayPawn(g_screen);
							break;
						}
						else if (chessPawnBlack[i].Move(g_even))
						{
							ShowMap();
							luot = 0;
							break;
						}
						else if (chessPawnBlack[i].Eat(g_even))
						{
							if (trang[chessPawnBlack[i].GetX()][chessPawnBlack[i].GetY()] == pawn)
								process_eat_black(chessPawnBlack[i], chessPawnWhite, 0, pawnWhite);
							else if (trang[chessPawnBlack[i].GetX()][chessPawnBlack[i].GetY()] == castle)
								process_eat_black(chessPawnBlack[i], chessCastleWhite, 0, castleWhite);
							else if (trang[chessPawnBlack[i].GetX()][chessPawnBlack[i].GetY()] == knight)
								process_eat_black(chessPawnBlack[i], chessKnightWhite, 0, knightWhite);
							else if (trang[chessPawnBlack[i].GetX()][chessPawnBlack[i].GetY()] == bishop)
								process_eat_black(chessPawnBlack[i], chessBishopWhite, 0, bishopWhite);
							else if (trang[chessPawnBlack[i].GetX()][chessPawnBlack[i].GetY()] == queen)
								process_eat_black(chessPawnBlack[i], chessQueenWhite, 0, queenWhite);
							else if (trang[chessPawnBlack[i].GetX()][chessPawnBlack[i].GetY()] == king)
								person_2_win = true;
							luot = 0;
							ShowMap();
							break;
						}
					}

					//check Black Castle
					for (int i = 0; i < castleBlack; i++)
					{
						if (chessCastleBlack[i].HandleInputAction(g_even))
						{
							for (int h = 0; h < 10; h++)
							{
								if (h < pawnBlack)
									chessPawnBlack[h].SetLan(0);
								if (h < castleBlack)
									if (h != i) chessCastleBlack[h].SetLan(0);
								if (h < bishopBlack)
									chessBishopBlack[h].SetLan(0);
								if (h < knightBlack)
									chessKnightBlack[h].SetLan(0);
								if (h < queenBlack)
									chessQueenBlack[h].SetLan(0);
								if (h == 0)
									chessKingBlack.SetLan(0);
							}
							ShowMap();
							chessCastleBlack[i].ShowWayCastle(g_screen);
							break;
						}
						else if (chessCastleBlack[i].Move(g_even))
						{
							ShowMap();
							luot = 0;
							break;
						}
						else if (chessCastleBlack[i].Eat(g_even))
						{
							if (trang[chessCastleBlack[i].GetX()][chessCastleBlack[i].GetY()] == pawn)
								process_eat_black(chessCastleBlack[i], chessPawnWhite, 0, pawnWhite);
							else if (trang[chessCastleBlack[i].GetX()][chessCastleBlack[i].GetY()] == castle)
								process_eat_black(chessCastleBlack[i], chessCastleWhite, 0, castleWhite);
							else if (trang[chessCastleBlack[i].GetX()][chessCastleBlack[i].GetY()] == knight)
								process_eat_black(chessCastleBlack[i], chessKnightWhite, 0, knightWhite);
							else if (trang[chessCastleBlack[i].GetX()][chessCastleBlack[i].GetY()] == bishop)
								process_eat_black(chessCastleBlack[i], chessBishopWhite, 0, bishopWhite);
							else if (trang[chessCastleBlack[i].GetX()][chessCastleBlack[i].GetY()] == queen)
								process_eat_black(chessCastleBlack[i], chessQueenWhite, 0, queenWhite);
							else if (trang[chessCastleBlack[i].GetX()][chessCastleBlack[i].GetY()] == king)
								person_2_win = true;
							luot = 0;
							ShowMap();
							break;
						}
					}

					//check Black Bishop
					for (int i = 0; i < bishopBlack; i++)
					{
						if (chessBishopBlack[i].HandleInputAction(g_even))
						{
							for (int h = 0; h < 10; h++)
							{
								if (h < pawnBlack)
									chessPawnBlack[h].SetLan(0);
								if (h < castleBlack)
									chessCastleBlack[h].SetLan(0);
								if (h < bishopBlack)
									if (h != i) chessBishopBlack[h].SetLan(0);
								if (h < knightBlack)
									chessKnightBlack[h].SetLan(0);
								if (h < queenBlack)
									chessQueenBlack[h].SetLan(0);
								if (h == 0)
									chessKingBlack.SetLan(0);
							}
							ShowMap();
							chessBishopBlack[i].ShowWayBishop(g_screen);
							break;
						}
						else if (chessBishopBlack[i].Move(g_even))
						{
							ShowMap();
							luot = 0;
							break;
						}
						else if (chessBishopBlack[i].Eat(g_even))
						{
							if (trang[chessBishopBlack[i].GetX()][chessBishopBlack[i].GetY()] == pawn)
								process_eat_black(chessBishopBlack[i], chessPawnWhite, 0, pawnWhite);
							else if (trang[chessBishopBlack[i].GetX()][chessBishopBlack[i].GetY()] == castle)
								process_eat_black(chessBishopBlack[i], chessCastleWhite, 0, castleWhite);
							else if (trang[chessBishopBlack[i].GetX()][chessBishopBlack[i].GetY()] == knight)
								process_eat_black(chessBishopBlack[i], chessKnightWhite, 0, knightWhite);
							else if (trang[chessBishopBlack[i].GetX()][chessBishopBlack[i].GetY()] == bishop)
								process_eat_black(chessBishopBlack[i], chessBishopWhite, 0, bishopWhite);
							else if (trang[chessBishopBlack[i].GetX()][chessBishopBlack[i].GetY()] == queen)
								process_eat_black(chessBishopBlack[i], chessQueenWhite, 0, queenWhite);
							else if (trang[chessBishopBlack[i].GetX()][chessBishopBlack[i].GetY()] == king)
								person_2_win = true;
							luot = 0;
							ShowMap();
							break;
						}
					}

					//check Black Knight
					for (int i = 0; i < knightBlack; i++)
					{
						if (chessKnightBlack[i].HandleInputAction(g_even))
						{
							for (int h = 0; h < 10; h++)
							{
								if (h < pawnBlack)
									chessPawnBlack[h].SetLan(0);
								if (h < castleBlack)
									chessCastleBlack[h].SetLan(0);
								if (h < bishopBlack)
									chessBishopBlack[h].SetLan(0);
								if (h < knightBlack)
									if (h != i) chessKnightBlack[h].SetLan(0);
								if (h < queenBlack)
									chessQueenBlack[h].SetLan(0);
								if (h == 0)
									chessKingBlack.SetLan(0);
							}
							ShowMap();
							chessKnightBlack[i].ShowWayKnight(g_screen);
							break;
						}
						else if (chessKnightBlack[i].Move(g_even))
						{
							ShowMap();
							luot = 0;
							break;
						}
						else if (chessKnightBlack[i].Eat(g_even))
						{
							if (trang[chessKnightBlack[i].GetX()][chessKnightBlack[i].GetY()] == pawn)
								process_eat_black(chessKnightBlack[i], chessPawnWhite, 0, pawnWhite);
							else if (trang[chessKnightBlack[i].GetX()][chessKnightBlack[i].GetY()] == castle)
								process_eat_black(chessKnightBlack[i], chessCastleWhite, 0, castleWhite);
							else if (trang[chessKnightBlack[i].GetX()][chessKnightBlack[i].GetY()] == knight)
								process_eat_black(chessKnightBlack[i], chessKnightWhite, 0, knightWhite);
							else if (trang[chessKnightBlack[i].GetX()][chessKnightBlack[i].GetY()] == bishop)
								process_eat_black(chessKnightBlack[i], chessBishopWhite, 0, bishopWhite);
							else if (trang[chessKnightBlack[i].GetX()][chessKnightBlack[i].GetY()] == queen)
								process_eat_black(chessKnightBlack[i], chessQueenWhite, 0, queenWhite);
							else if (trang[chessKnightBlack[i].GetX()][chessKnightBlack[i].GetY()] == king)
								person_2_win = true;
							luot = 0;
							ShowMap();
							break;
						}
					}

					//check Black Queen
					for (int i = 0; i < queenBlack; i++)
					{
						if (chessQueenBlack[i].HandleInputAction(g_even))
						{
							for (int h = 0; h < 10; h++)
							{
								if (h < pawnBlack)
									chessPawnBlack[h].SetLan(0);
								if (h < castleBlack)
									chessCastleBlack[h].SetLan(0);
								if (h < bishopBlack)
									chessBishopBlack[h].SetLan(0);
								if (h < knightBlack)
									chessKnightBlack[h].SetLan(0);
								if (h < queenBlack)
									if (h != i) chessQueenBlack[h].SetLan(0);
								if (h == 0)
									chessKingBlack.SetLan(0);
							}
							ShowMap();
							chessQueenBlack[i].ShowWayQueen(g_screen);
							break;
						}
						else if (chessQueenBlack[i].Move(g_even))
						{
							ShowMap();
							luot = 0;
							break;
						}
						else if (chessQueenBlack[i].Eat(g_even))
						{
							if (trang[chessQueenBlack[i].GetX()][chessQueenBlack[i].GetY()] == pawn)
								process_eat_black(chessQueenBlack[i], chessPawnWhite, 0, pawnWhite);
							else if (trang[chessQueenBlack[i].GetX()][chessQueenBlack[i].GetY()] == castle)
								process_eat_black(chessQueenBlack[i], chessCastleWhite, 0, castleWhite);
							else if (trang[chessQueenBlack[i].GetX()][chessQueenBlack[i].GetY()] == knight)
								process_eat_black(chessQueenBlack[i], chessKnightWhite, 0, knightWhite);
							else if (trang[chessQueenBlack[i].GetX()][chessQueenBlack[i].GetY()] == bishop)
								process_eat_black(chessQueenBlack[i], chessBishopWhite, 0, bishopWhite);
							else if (trang[chessQueenBlack[i].GetX()][chessQueenBlack[i].GetY()] == queen)
								process_eat_black(chessQueenBlack[i], chessQueenWhite, 0, queenWhite);
							else if (trang[chessQueenBlack[i].GetX()][chessQueenBlack[i].GetY()] == king)
								person_2_win = true;
							luot = 0;
							ShowMap();
							break;
						}
					}

					//check Black King
					if (chessKingBlack.HandleInputAction(g_even))
					{
						for (int h = 0; h < 10; h++)
						{
							if (h < pawnBlack)
								chessPawnBlack[h].SetLan(0);
							if (h < castleBlack)
								chessCastleBlack[h].SetLan(0);
							if (h < bishopBlack)
								chessBishopBlack[h].SetLan(0);
							if (h < knightBlack)
								chessKnightBlack[h].SetLan(0);
							if (h < queenBlack)
								chessQueenBlack[h].SetLan(0);
						}
						ShowMap();
						chessKingBlack.ShowWayKing(g_screen);
					}
					else if (chessKingBlack.Move(g_even))
					{
						ShowMap();
						luot = 0;
					}
					else if (chessKingBlack.Eat(g_even))
					{
						if (trang[chessKingBlack.GetX()][chessKingBlack.GetY()] == pawn)
							process_eat_black(chessKingBlack, chessPawnWhite, 0, pawnWhite);
						else if (trang[chessKingBlack.GetX()][chessKingBlack.GetY()] == castle)
							process_eat_black(chessKingBlack, chessCastleWhite, 0, castleWhite);
						else if (trang[chessKingBlack.GetX()][chessKingBlack.GetY()] == knight)
							process_eat_black(chessKingBlack, chessKnightWhite, 0, knightWhite);
						else if (trang[chessKingBlack.GetX()][chessKingBlack.GetY()] == bishop)
							process_eat_black(chessKingBlack, chessBishopWhite, 0, bishopWhite);
						else if (trang[chessKingBlack.GetX()][chessKingBlack.GetY()] == queen)
							process_eat_black(chessKingBlack, chessQueenWhite, 0, queenWhite);
						else if (trang[chessKingBlack.GetX()][chessKingBlack.GetY()] == king)
							person_2_win = true;
						luot = 0;
						ShowMap();
						break;
					}
				}
			}

			if (person_1_win) break;
			if (person_2_win) break;
			//update Pawn
			if (luot == 1)
			{
				for (int i = 0; i < pawnWhite; i++)
					if (chessPawnWhite[i].GetX() == 0)
					{
						int ret_update = SDLCommonFunc::ShowUpdate(g_screen, white);
						if (ret_update == 0) is_quit = true;
						if (ret_update == castle)
						{
							chessCastleWhite[castleWhite].Loading("quan_xe_trang.png");
							update(chessCastleWhite, chessPawnWhite, castleWhite, pawnWhite, i, white);
						}
						else if (ret_update == bishop)
						{
							chessBishopWhite[bishopWhite].Loading("quan_tinh_trang.png");
							update(chessBishopWhite, chessPawnWhite, bishopWhite, pawnWhite, i, white);
						}
						else if (ret_update == knight)
						{
							chessKnightWhite[knightWhite].Loading("quan_ma_trang.png");
							update(chessKnightWhite, chessPawnWhite, knightWhite, pawnWhite, i, white);
						}
						else if (ret_update == queen)
						{
							chessQueenWhite[queenWhite].Loading("quan_hau_trang.png");
							update(chessQueenWhite, chessPawnWhite, queenWhite, pawnWhite, i, white);
						}
					}
			}
			else
			{
				for (int i = 0; i < pawnBlack; i++)
					if (chessPawnBlack[i].GetX() == 7)
					{
						int ret_update = SDLCommonFunc::ShowUpdate(g_screen, black);
						if (ret_update == 0) is_quit = true;
						if (ret_update == castle)
						{
							chessCastleBlack[castleBlack].Loading("quan_xe_den.png");
							update(chessCastleBlack, chessPawnBlack, castleBlack, pawnBlack, i, black);
						}
						else if (ret_update == bishop)
						{
							chessBishopBlack[bishopBlack].Loading("quan_tinh_den.png");
							update(chessBishopBlack, chessPawnBlack, bishopBlack, pawnBlack, i, black);
						}
						else if (ret_update == knight)
						{
							chessKnightBlack[knightBlack].Loading("quan_ma_den.png");
							update(chessKnightBlack, chessPawnBlack, knightBlack, pawnBlack, i, black);
						}
						else if (ret_update == queen)
						{
							chessQueenBlack[queenBlack].Loading("quan_hau_den.png");
							update(chessQueenBlack, chessPawnBlack, queenBlack, pawnBlack, i, black);
						}
					}
			}

			//show chess
			for (int i = 0; i < 10; i++)
			{
				if (i < pawnWhite)
					chessPawnWhite[i].Show(g_screen);
				if (i < pawnBlack)
					chessPawnBlack[i].Show(g_screen);
				if (i < bishopWhite)
					chessBishopWhite[i].Show(g_screen);
				if (i < bishopBlack)
					chessBishopBlack[i].Show(g_screen);
				if (i < castleWhite)
					chessCastleWhite[i].Show(g_screen);
				if (i < castleBlack)
					chessCastleBlack[i].Show(g_screen);
				if (i < knightWhite)
					chessKnightWhite[i].Show(g_screen);
				if (i < knightBlack)
					chessKnightBlack[i].Show(g_screen);
				if (i < queenWhite)
					chessQueenWhite[i].Show(g_screen);
				if (i < queenBlack)
					chessQueenBlack[i].Show(g_screen);
				chessKingWhite.Show(g_screen);
				chessKingBlack.Show(g_screen);
			}
			if (SDL_Flip(g_screen) == -1) return 0;
		}
		if (is_quit) break;
		if (person_1_win)
		{
			int ret_end = SDLCommonFunc::ShowEnd(g_screen, g_font_text, 1);
			if (ret_end == 0) break;
		}
		if (person_2_win)
		{
			int ret_end = SDLCommonFunc::ShowEnd(g_screen, g_font_text, 2);
			if (ret_end == 0) break;
		}
	}
	
	SDLCommonFunc::CleanUp();
	SDL_Quit();
	return 1;
}