#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include <SDL2/SDL.h>
#include <memory>
#include "vector2.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

class Renderable {
	public:
		Renderable();
		virtual ~Renderable();

		virtual void draw(SDL_Renderer* renderer) = 0;
    	virtual void update() = 0;
		void draw_line(SDL_Renderer* renderer, const Vector2<float>& first_point, const Vector2<float>& second_point);
};

typedef std::shared_ptr<Renderable> RenderablePtr;

#endif
