#include "stdafx.h"
#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
	width_frame = 0;
	height_frame = 0;
	x_pos = 0;
	y_pos = 0;
	x_val = 0;
	y_val = 0;
	max_x = 0;
	max_y = 0;
}

ThreatObject::~ThreatObject()
{

}

bool ThreatObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret != false)
	{
		width_frame = rect_.w;
		height_frame = rect_.h;
	}
	return ret;
}

void ThreatObject::Show(SDL_Renderer* des)
{
	rect_.x = x_pos;
	rect_.y = y_pos;
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame, height_frame };
	SDL_RenderCopy(des, p_object, NULL, &renderQuad);
}

void ThreatObject::DoThreat(const int& score)
{
	if (line_side == 1)
	{
		x_pos += 0.3 + float(score)/100;
		if (x_pos > 1000)
		{
			x_pos = -90;
		}
	}
	else
	{
		x_pos -= 0.3 + float(score)/100;
		if (x_pos < -90)
		{
			x_pos = 1000;
		}
	}
}

SDL_Rect ThreatObject::GetRect()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame;
	rect.h = height_frame;
	return rect;
}