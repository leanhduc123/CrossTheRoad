#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"

class ThreatObject : public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();
	void set_x_val(const float& xval) { x_val = xval; }
	void set_y_val(const float& yval) { y_val = yval; }

	void set_x_pos(const float& xp) { x_pos = xp; }
	void set_y_pos(const float& yp) { y_pos = yp; }
	void get_line_side(const int& a) { line_side = a; }

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void DoThreat(const int& score);
	SDL_Rect GetRect();
private: 

	float x_pos;
	float y_pos;
	
	float x_val;
	float y_val;

	int max_x;
	int max_y;
	float status;
	int width_frame;
	int height_frame;
	int line_side;
};
#endif // !THREAT_OBJECT_H_

