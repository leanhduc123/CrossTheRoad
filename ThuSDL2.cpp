// ThuSDL2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Common_Function.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "TextObject.h"

BaseObject g_background;
BaseObject Menu;
TTF_Font* g_font_text = NULL;
//Khoi tao window, screen, audio va text
bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Cross the road", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_JPG;
			if (!(IMG_Init(imgFlags) && imgFlags))
					success = false;
		}
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		return false;
	}

	if (TTF_Init() == -1)
	{
		return -1;
	}
	g_font_text = TTF_OpenFont("COOPBL.ttf", 30);
	if (g_font_text == NULL)
	{
		return false;
	}

	return success;
}
// Load background
bool LoadBkground()
{
	bool ret = g_background.LoadImg("g2.jpg", g_screen);
	if (ret == false)
		return false;
	return true;
}
// Tao menu sau khi va cham
int ShowEnd(SDL_Renderer* des, std::string path, TextObject text, TTF_Font* font, std::string val, TextObject text2, std::string val2)
{
	BaseObject g_menu;
	bool ret = g_menu.LoadImg(path, des);
	if (ret == false)
		return -1;
	SDL_Event m_event;
	text.SetColor(0);
	text.SetText(val);
	text.SetRect(548, 208);
	text.SetSize(20, 38);

	text2.SetColor(0);
	text2.SetText(val2);
	text2.SetRect(587, 270);
	text2.SetSize(20, 38);
	while (true)
	{

		while (SDL_PollEvent(&m_event))
		{
			g_menu.Render(des, NULL);
			text.CreateGameText(font, des);
			text2.CreateGameText(font, des);
			//text.CreateGameText(font, des);
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

// Giai phong wwindow sau khi ket thuc chuong trinh
void Close()
{
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();

}

// Tao danh sach quan ly threat
std::vector<ThreatObject*> MakeThreatList()
{
	std::vector<ThreatObject*> list_threat;

	ThreatObject* threat_object = new ThreatObject[7*14];
	int con = 0;
	int a;

	for (int i = 0; i < 14; i++)
	{
		int pos_ = (rand() % 10) * 10;
		a = rand() % 2;
		for (int j = 0; j < 4; j++)
		{
			ThreatObject* p_threat = (threat_object + con);
			p_threat->get_line_side(a);
			con++;
			if (p_threat != NULL)
			{
				int x = rand() % 10;
				int xe = rand() % 3;
				if (a == 1)
				{
					if (xe == 1) p_threat->LoadImg("threat//1_right.jpg", g_screen);
					else if (xe == 2) p_threat->LoadImg("threat//2_right.jpg", g_screen);
					else p_threat->LoadImg("threat//3_right.jpg", g_screen);
					p_threat->set_x_pos(pos_);
					pos_ += 100 + x * 30;
				}
				else
				{
					if (xe == 1) p_threat->LoadImg("threat//1_left.jpg", g_screen);
					else if (xe == 2) p_threat->LoadImg("threat//2_left.jpg", g_screen);
					else p_threat->LoadImg("threat//3_left.jpg", g_screen);
					p_threat->set_x_pos(1000 - 90 - pos_);
					pos_ += 100 + x * 30;
				}

				p_threat->set_y_pos(50*(i+1));
				
				list_threat.push_back(p_threat);
			}
		}
	}
	return list_threat;
}

int main(int argv, char* arc[])
{
	srand(time(NULL));
	if (InitData() == false)
		return -1;
	int check = SDLCommonFunc::ShowMenu(g_screen, "menu.jpg");  // tao menu cho game
	if (check == -1)
		return -1; 
	if (LoadBkground() == false)
		return -1;
	//Khoi tao Tile Map
	GameMap game_map;
	game_map.LoadMap("map/map01");
	game_map.LoadTiles(g_screen); 
	//Khoi tao text score
	TextObject score_game;
	score_game.SetColor(1);
	TextObject score_result;
	TextObject high_score;

	std::vector<ThreatObject*> threatlist = MakeThreatList();	//Khoi tao threat
	MainObject p_player;  //Khoi tao nhan vat chinh

	//Load file am thanh
	g_coin_sound = Mix_LoadWAV("Coin.wav");
	g_crash_sound = Mix_LoadWAV("Car_Hit.wav");
	g_theme = Mix_LoadMUS("theme_song.mp3");

	int score = 0;
	int max_score = 0;

	bool is_quit = false;
	while (!is_quit)
	{
		while (SDL_PollEvent(&even) != 0)
		{
			if (even.type == SDL_QUIT)
			{
				is_quit = true;
			}
			p_player.HandleInputAction(even, g_screen);  //Bat dieu kien
		}

		//Mo nhac
		if (!Mix_PlayingMusic())
			Mix_PlayMusic(g_theme, 1);

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);
		//Render background va map
		g_background.Render(g_screen, NULL);
		game_map.DrawMap(g_screen);

		Map map_data = game_map.getMap();
		// Nhan vat di chuyen va an vang
		p_player.DoPlayer(map_data, g_coin_sound);

		//Tao text score hien thi khi choi
		score = p_player.GetScore();
		std::string score_val = std::to_string(score);
		std::string score_text("Score: ");
		score_text += score_val;
		score_game.SetText(score_text);
		score_game.SetRect(430, 2);
		score_game.CreateGameText(g_font_text, g_screen);

		p_player.Show(g_screen);  //Render nhan vat ra man hinh
		int con = 0; 
		for (int i = 0; i < 14; i++)
			for (int j = 0; j < 4; j++)
		{
			ThreatObject* p_threat = threatlist.at(con);
			con++;
			p_threat->DoThreat(score);   //Di chuyen threat
			p_threat->Show(g_screen);    //Render threat

			//Check va cham
			bool check_impact = SDLCommonFunc::CheckImpact(p_player.GetRect(), p_threat->GetRect());
			if (check_impact)
			{
				if (score > max_score)
					max_score = score;
				int crash = Mix_PlayChannel(-1, g_crash_sound, 0);
				int restart_ = ShowEnd(g_screen, "map/end.jpg", score_result, g_font_text, score_val, high_score, std::to_string(max_score));

				if (restart_ == -1)
				{
					Close();
					return 0;
				}
				else
				{
					p_player.Restart();
				}
			}
		 
		}
		game_map.SetMap(map_data);
		SDL_RenderPresent(g_screen);
	}
	Close();
	return 0;
}