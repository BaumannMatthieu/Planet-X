#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include <SDL2/SDL.h>

#include "primitive.h"

class Rectangle : public Primitive {
	public:
		Rectangle(const Vector2<float>& pos, const float w, const float h);
		virtual ~Rectangle();

	private:
		float w_, h_;
};

#endif

