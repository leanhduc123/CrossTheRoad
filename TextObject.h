#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "BaseObject.h"

class TextObject : public BaseObject
{
public:
	enum TextColor
	{
		BLUE_TEXT = 0,
		WHITE_TEXT = 1,
	};
	TextObject();
	~TextObject();

	void SetText(const std::string& text) { str_val = text; }
	void SetColor(const int& type);
	void CreateGameText(TTF_Font* font, SDL_Renderer* des); 
private:
	std::string str_val;
	SDL_Color text_color;
};
#endif // !TEXT_OBJECT_H_

