#ifndef KING_H_
#define KING_H_
#include "Common_Function.h"
#include "BaseObject.h"

extern int trang[8][8];
extern int den[8][8];
class King : public BaseObject
{
private:
	int kt;
	int quan_trang_den;
	int lan;
	int x;
	int y;
	BaseObject p[8];
	bool check[8];
public:
	King();
	void SetKt(const int& value) { kt = value; }
	int GetKt() const { return kt; }
	void SetWB(const int& value) { quan_trang_den = value; }
	int GetWB() const { return quan_trang_den; }
	void ShowWayKing(SDL_Surface* des);
	bool Move(SDL_Event events);
	bool Eat(SDL_Event events);
	void SetX(const int& value) { x = value; }
	void SetY(const int& value) { y = value; }
	int GetX() const { return x; }
	int GetY() const { return y; }
	void SetLan(const int& value) { lan = value; }
};
#endif

