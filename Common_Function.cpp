#include "stdafx.h"
#include "Common_Function.h"
#include "BaseObject.h"
#include "TextObject.h"

bool SDLCommonFunc::CheckImpact(const SDL_Rect& object1, const SDL_Rect& object2)
{
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}
	return false;
}

int SDLCommonFunc::ShowMenu(SDL_Renderer* des, std::string path)
{
	BaseObject g_menu;
	bool ret = g_menu.LoadImg(path, des);
	if (ret == false)
		return -1;
	SDL_Event m_event;
	while (true)
	{
		
		while (SDL_PollEvent(&m_event))
		{
			g_menu.Render(des, NULL);
			switch (m_event.type)
			{
			case SDL_QUIT:
				return -1;
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
				{
					return -1;
			    }
				else if (m_event.key.keysym.sym == SDLK_p)
				{
					return 0;
				}
			default:
				break;
			}
			SDL_RenderPresent(des);
		}
	}
}

