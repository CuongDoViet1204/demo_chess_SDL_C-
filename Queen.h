#ifndef QUEEN_H_
#define QUEEN_H_
#include "Common_Function.h"
#include "BaseObject.h"

extern int trang[8][8];
extern int den[8][8];
class Queen : public BaseObject
{
private:
	int kt;
	int quan_trang_den;
	int lan;
	int x;
	int y;
	BaseObject ngang[8];
	bool chieu_ngang[8];
	BaseObject doc[8];
	bool chieu_doc[8];
	BaseObject cheo_trai[8];
	bool trai[8];
	BaseObject cheo_phai[8];
	bool phai[8];
public:
	Queen();
	void SetKt(const int& value) { kt = value; }
	int GetKt() const { return kt; }
	void SetWB(const int& value) { quan_trang_den = value; }
	int GetWB() const { return quan_trang_den; }
	void ShowWayQueen(SDL_Surface* des);
	bool Move(SDL_Event events);
	bool Eat(SDL_Event events);
	void SetX(const int& value) { x = value; }
	void SetY(const int& value) { y = value; }
	int GetX() const { return x; }
	int GetY() const { return y; }
	void SetLan(const int& value) { lan = value; }
};
#endif

