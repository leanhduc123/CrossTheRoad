#include "stdafx.h"
#include "MainObject.h"

MainObject::MainObject()
{
	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
	status = -1;
	input_type.down_ = 0;
	input_type.left_ = 0;
	input_type.right_ = 0;
	input_type.up_ = 0;
	score = 0;
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	return ret;
}

void MainObject::Show(SDL_Renderer* des)
{
	if (status == Walk_Left)
	{
		LoadImg("human/testman_left.png", des);
	}
	else
	{
		LoadImg("human/testman.png", des);
	}

	rect_.x = x_pos;
	rect_.y = y_pos;

    SDL_Rect renderQuad = { rect_.x, rect_.y, HUMAN_SIZE, HUMAN_SIZE };
	SDL_RenderCopy(des, p_object, NULL, &renderQuad);
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT :
		{
			status = Walk_Right;
			input_type.right_ = 1;
			input_type.left_ = 0;
		}
		break;
		case SDLK_LEFT:
		{
			status = Walk_Left;
			input_type.right_ = 0;
			input_type.left_ = 1;
		}
		break;
		case SDLK_UP:
		{
			input_type.up_ = 1;
			input_type.down_ = 0;
		}
		break;
		case SDLK_DOWN:
		{
			input_type.down_ = 1;
			input_type.up_ = 0;
		}
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			input_type.right_ = 0;
		}
		break;
		case SDLK_LEFT:
		{
			input_type.left_ = 0;
		}
		break;
		case SDLK_UP:
		{
			input_type.up_ = 0;
		}
		break;
		case SDLK_DOWN:
		{
			input_type.down_ = 0;
		}
		break;
		default:
			break;
		}
	}
}

void MainObject::DoPlayer(Map& map_data, Mix_Chunk* coin_sound)
{
	x_val = 0;
	y_val = 0;
	if (input_type.right_ == 1)
	{
		x_val += 0.5 + float(score) / 100;
	}
	else if (input_type.left_ == 1)
	{
		x_val -= 0.5 + float(score) / 100;
	}
	else if (input_type.down_ == 1)
	{
		y_val += 0.5 + float(score) / 100;
	}
	else if (input_type.up_ == 1)
	{
		y_val -= 0.5 + float(score) / 100;
	}
	x_pos += x_val;
	y_pos += y_val;

	ChecktoMap(map_data, coin_sound);
}

void MainObject::ChecktoMap(Map& map_data, Mix_Chunk* coin_sound)
{
	if (x_pos >= SCREEN_WIDTH + HUMAN_SIZE)
	{
		x_pos = -HUMAN_SIZE;
	}
	else if (x_pos < -HUMAN_SIZE)
	{
		x_pos = 1000;
	}
	if (y_pos >= SCREEN_HEIGHT - HUMAN_SIZE)
	{
		y_pos = SCREEN_HEIGHT - HUMAN_SIZE;
	}
	else if (y_pos <= 0)
	{
		y_pos = 0;
	}

	x1 = x_pos / TILE_SIZE;
	y1 = y_pos / TILE_SIZE;

	x2 = (x_pos + HUMAN_SIZE) / TILE_SIZE;
	y2 = (y_pos + HUMAN_SIZE) / TILE_SIZE;
	
	bool hit = false;

	if (map_data.tile[y1][x1] == 2 && x_pos < x1*TILE_SIZE + 30 && y_pos < y1*TILE_SIZE + 30)
	{
		map_data.tile[y1][x1] = 1;
		hit = true;
	} 

	if (map_data.tile[y1][x2] == 2 && x_pos > x2*TILE_SIZE + 5 && y_pos < y1*TILE_SIZE + 30)
	{
		map_data.tile[y1][x2] = 1;
		hit = true;
	}

	if (map_data.tile[y2][x1] == 2 && x_pos < x1*TILE_SIZE + 30 && y_pos > y2*TILE_SIZE + 5)
	{
		map_data.tile[y2][x1] = 1;
		hit = true;
	}

	if (map_data.tile[y2][x2] == 2 && x_pos > x2*TILE_SIZE + 5 && y_pos > y2*TILE_SIZE + 5)
	{
		map_data.tile[y2][x2] = 1;
		hit = true;
	}

	if (hit)
	{
		score++;
		int ret = Mix_PlayChannel(-1,coin_sound, 0);
		Reset_coin(map_data);
	}
}

void MainObject::Reset_coin(Map& mapdata)
{
	int i = rand() % 15 + 2;
	int j = rand() % 20 + 1;
	mapdata.tile[i][j] = 2;
}

SDL_Rect MainObject::GetRect()
{
	SDL_Rect rect;
	rect.x = x_pos;
	rect.y = y_pos;
	rect.w = HUMAN_SIZE;
	rect.h = HUMAN_SIZE;
	return rect;
}

void MainObject::Restart()
{
	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
	status = -1;
	input_type.down_ = 0;
	input_type.left_ = 0;
	input_type.right_ = 0;
	input_type.up_ = 0;
	score = 0;
}