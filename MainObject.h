#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"

class MainObject : public BaseObject
{
public: 
	enum WalkType
	{
		Walk_Right = 0,
		Walk_Left = 1,
	};
	MainObject();
	~MainObject();
	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void DoPlayer(Map& map_data, Mix_Chunk* coin_sound);
	void ChecktoMap(Map& map_data, Mix_Chunk* coin_sound);
	void Reset_coin(Map& mapdata);
	SDL_Rect GetRect();
	void Restart();
	int GetScore() const { return score; }
private:
	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int x1, y1;
	int x2, y2;
	int status;
	int score;
	Input input_type;
};
#endif // !MAIN_OBJECT_H_
