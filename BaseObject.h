#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_
#include "Common_Function.h"

class BaseObject
{
protected:
	SDL_Rect rect_;
	SDL_Surface* p_object_;
public:
	BaseObject();
	~BaseObject();
	void Show(SDL_Surface* des);
	bool Loading(const char* file_name);
	void SetRect(const int& x, const int& y) { rect_.x = x; rect_.y = y; }
	SDL_Rect GetRect() const { return rect_; }
	SDL_Surface* GetObject() { return p_object_; }
	bool HandleInputAction(SDL_Event events);
};

#endif
