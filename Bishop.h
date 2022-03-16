#ifndef BISHOP_H_
#define BISHOP_H_
#include "Common_Function.h"
#include "BaseObject.h"

extern int trang[8][8];
extern int den[8][8];
class Bishop : public BaseObject
{
private:
	int kt;
	int quan_trang_den;
	int lan;
	int x;
	int y;
	BaseObject cheo_trai[8];
	bool trai[8];
	BaseObject cheo_phai[8];
	bool phai[8];
public:
	Bishop();
	void SetKt(const int& value) { kt = value; }
	int GetKt() const { return kt; }
	void SetWB(const int& value) { quan_trang_den = value; }
	int GetWB() const { return quan_trang_den; }
	void ShowWayBishop(SDL_Surface* des);
	void SetX(const int& value) { x = value; }
	void SetY(const int& value) { y = value; }
	int GetX() const { return x; }
	int GetY() const { return y; }
	void SetLan(const int& value) { lan = value; }
	bool Move(SDL_Event events);
	bool Eat(SDL_Event events);
};
#endif

