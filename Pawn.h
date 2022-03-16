#ifndef PAWN_H_
#define PAWN_H_
#include "Common_Function.h"
#include "BaseObject.h"

extern int trang[8][8];
extern int den[8][8];
class Pawn : public BaseObject
{
private:
	int kt; //đứng tại ô trắng hay đen
	int quan_trang_den; //quân trắng hay quân đen
	int lan;	//click vào lần 1 hay lần 2
	int luot;	//lượt đầu đi 2 ô, các lượt sau đi 1 ô
	BaseObject p[4];
	int x; //vị trí hàng hiện tại
	int y; //vị trí cột hiện tại
public:
	enum { tren_1 = 0, tren_2, cheo_trai, cheo_phai };
	Pawn();
	void SetKt(const int& value) { kt = value; }
	int GetKt() const { return kt; }
	void SetWB(const int& value) { quan_trang_den = value; }
	int GetWB() const { return quan_trang_den; }
	void ShowWayPawn(SDL_Surface* des);
	bool Move(SDL_Event events);
	void SetX(const int& value) { x = value; }
	int GetX() const { return x; }
	void SetY(const int& value) { y = value; }
	int GetY() const { return y; }
	int GetLan() const { return lan; }
	void SetLan(const int& value) { lan = value; }
	bool Eat(SDL_Event events);
};
#endif
