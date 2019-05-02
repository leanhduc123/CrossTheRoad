#include "stdafx.h"
#include "game_map.h"
#include <cstdio>

void GameMap::LoadMap(char* nam)
{
	FILE* fp = NULL;
	fopen_s(&fp, nam, "rb");
	if (fp == NULL)
	{
		return;
	}

	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			fscanf_s(fp, "%d", &game_map.tile[i][j]);
			int val = game_map.tile[i][j];
			if (val > 0)
			{
				if (j > game_map.max_x)
				{
					game_map.max_x = j;
				}
				if (i > game_map.max_y)
				{
					game_map.max_y = i;
				}
			}
		}
	}
	game_map.max_x = (game_map.max_x + 1)*TILE_SIZE;
	game_map.max_y = (game_map.max_y + 1)*TILE_SIZE;

	game_map.start_x = 0;
	game_map.start_y = 0;

	game_map.file_name = nam;
	fclose(fp);

}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
	char file_img[30];
	FILE* fp = NULL;

	for (int i = 0; i < MAX_TILE; i++)
	{
		sprintf_s(file_img, "map/%d.jpg", i);

		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
		{
			continue;
		}

		fclose(fp);

		tile_map[i].LoadImg(file_img, screen);

	}
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
	int x1 = 0;
	int y1 = 0;

	int x2 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;
	

	map_x = game_map.start_x / TILE_SIZE;
	map_y = game_map.start_y / TILE_SIZE;
	x2 = x1 + SCREEN_WIDTH;
	y2 = y1 + SCREEN_HEIGHT;
	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		map_x = game_map.start_x / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int val = game_map.tile[map_y][map_x];
			if (val > 0)
			{
				tile_map[val].SetRect(j, i);
				tile_map[val].Render(screen);
			}
			map_x++;
		}
		map_y++;
	}
}