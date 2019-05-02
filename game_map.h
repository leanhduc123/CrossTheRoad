#ifndef GAME_MAX_H_
#define GAME_MAX_H_

#include "Common_Function.h"
#include "BaseObject.h"

#define MAX_TILE 20
class TileMap : public BaseObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }

};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }

	void LoadMap(char* nam);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map getMap() const { return game_map; }
	void SetMap(Map& map_data) { game_map = map_data; }
private:
	Map game_map;
	TileMap tile_map[MAX_TILE];
};

#endif // !1


