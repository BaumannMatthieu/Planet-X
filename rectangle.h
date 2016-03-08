#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include <SDL2/SDL.h>

#include "primitive.h"

class Rectangle : public Primitive {
	public:
		Rectangle() { }
		Rectangle(const Point& pos, const float w, const float h);
		virtual ~Rectangle();	
		
		bool is_rectangle() const override;

        static bool intersection(const Rectangle& r1, const Rectangle& r2);
        static bool intersection(const Point& p, const Rectangle& r);
	    const Vector2<float> get_size() const;
    private:
		float w_, h_;
};

#endif

