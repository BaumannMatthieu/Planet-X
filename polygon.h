#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <SDL2/SDL.h>
#include <vector>

#include "vector2.h"
#include "renderable.h"

typedef Vector2<float> Point;

class Polygon : public Renderable {
	public:
		Polygon(const std::vector<Point>& points);
		virtual ~Polygon();

		virtual void draw(SDL_Renderer* renderer);
	private:
		std::vector<Point> points_;
};

#endif
