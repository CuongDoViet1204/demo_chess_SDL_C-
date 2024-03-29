#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_
#include "BaseObject.h"
#include <SDL_ttf.h>
#include <string>

class TextObject : public BaseObject
{
private:
	std::string str_val_;
	SDL_Color text_color_;
public:
	enum TextColor { RED_TEXT = 0, WHITE_TEXT, BLACK_TEXT };
	TextObject();
	~TextObject();
	void SetText(const std::string& text) { str_val_ = text; }
	void SetColor(const int& type);
	void CreateGameText(TTF_Font* font, SDL_Surface* des);
};
#endif
