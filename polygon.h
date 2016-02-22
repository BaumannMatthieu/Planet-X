#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <SDL2/SDL.h>

#include "primitive.h"

class Polygon : public Primitive {
	public:
		Polygon(const std::vector<Point>& points);
		virtual ~Polygon();

		void rotate(const float ang);
		void scale(const float factor);
};

#endif
