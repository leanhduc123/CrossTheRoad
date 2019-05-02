#include "stdafx.h"
#include "TextObject.h"

TextObject::TextObject()
{
	rect_.w = 85;
	rect_.h = 50;
}

TextObject::~TextObject()
{

}

void TextObject::SetColor(const int& type)
{
	if (type == BLUE_TEXT)
	{
		SDL_Color color = { 41, 46, 150 };
		text_color = color;
	}
	if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255, 255, 255 };
		text_color = color;
	}
}

void TextObject::CreateGameText(TTF_Font* font, SDL_Renderer* des)
{
	SDL_Surface* object = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
	p_object = SDL_CreateTextureFromSurface(des, object);
	Render(des, NULL);
}