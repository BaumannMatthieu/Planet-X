#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include <SDL2/SDL.h>
#include "vector2.h"

class Renderable {
	public:
		Renderable();
		virtual ~Renderable();

		virtual void draw(SDL_Renderer* renderer) = 0;
		void draw_line(SDL_Renderer* renderer, const Vector2<float>& first_point, const Vector2<float>& second_point);
};

#endif
