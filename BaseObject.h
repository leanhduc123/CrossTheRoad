#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "Common_Function.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x, const int& y) { rect_.x = x; rect_.y = y; }
	void SetSize(const int& w, const int& h) { rect_.w = w; rect_.h = h; }
	SDL_Rect GetRect() const { return rect_; }
	SDL_Texture* GetObject() { return p_object; }
    bool LoadImg(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

protected: 
	SDL_Texture* p_object;
	SDL_Rect rect_;
};
#endif // !BASE_OBJECT_H_

