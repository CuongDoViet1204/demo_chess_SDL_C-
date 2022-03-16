#ifndef CASLTLE_H_
#define CASTLE_H_
#include "Common_Function.h"
#include "BaseObject.h"

extern int trang[8][8];
extern int den[8][8];
class Castle : public BaseObject
{
private:
	int kt;
	int quan_trang_den;
	int lan;
	BaseObject ngang[8];
	bool chieu_ngang[8];
	BaseObject doc[8];
	bool chieu_doc[8];
	int x;
	int y;
public:
	Castle();
	void SetKt(const int& value) { kt = value; }
	int GetKt() const { return kt; }
	void SetWB(const int& value) { quan_trang_den = value; }
	int GetWB() const { return quan_trang_den; }
	void ShowWayCastle(SDL_Surface* des);
	void SetX(const int& value) { x = value; }
	void SetY(const int& value) { y = value; }
	int GetX() const { return x; }
	int GetY() const { return y; }
	void SetLan(const int& value) { lan = value; }
	bool Move(SDL_Event events);
	bool Eat(SDL_Event events);
};
#endif
