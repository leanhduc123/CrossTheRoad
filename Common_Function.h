#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <ctime>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event even;

static Mix_Chunk* g_coin_sound = NULL;
static Mix_Chunk* g_crash_sound = NULL;
static Mix_Music* g_theme = NULL;


const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const int SCREEN_BPP = 32;

const int Color_Key_R = 255;
const int Color_Key_G = 255;
const int Color_key_B = 25;

const int RENDER_DRAW_COLOR = 255;

#define TILE_SIZE 50
#define MAX_MAP_X 20
#define MAX_MAP_Y 16
#define HUMAN_SIZE 25

#define GOLD 4



typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
};
typedef struct Map
{
	int start_x;
	int start_y;

	int max_x;
	int max_y;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name;
};

namespace SDLCommonFunc
{
	bool CheckImpact(const SDL_Rect& object1, const SDL_Rect& object2);
	int ShowMenu(SDL_Renderer* des, std::string path);
}
#endif // !COMMON_FUNCTION_H_
