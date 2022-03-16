#include "BaseObject.h"

BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;
}

BaseObject::~BaseObject()
{
	if (p_object_) SDL_FreeSurface(p_object_);
}

bool BaseObject::Loading(const char* file_name)
{
	p_object_ = SDLCommonFunc::LoadImage(file_name);
	if (p_object_ == NULL)
		return false;
	return true;
}

void BaseObject::Show(SDL_Surface* des)
{
	if (p_object_ != NULL)
		rect_ = SDLCommonFunc::ApplySurface(p_object_, des, rect_.x, rect_.y);
}

bool BaseObject::HandleInputAction(SDL_Event events)
{
	if (events.type == SDL_MOUSEBUTTONDOWN)
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			int x = events.button.x;
			int y = events.button.y;
			if (x >= rect_.x && x <= rect_.x + 50 && y >= rect_.y && y <= rect_.y + 50)
				return true;
		}
	return false;
}