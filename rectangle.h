#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include <SDL2/SDL.h>

#include "primitive.h"

class Rectangle : public Primitive {
	public:
		Rectangle();
		Rectangle(const Point& pos, const float w, const float h);
		Rectangle(const Rectangle& rect);
		virtual ~Rectangle();	
		
		bool is_rectangle() const override;

        static bool intersection(const Rectangle& r1, const Rectangle& r2);
        static bool intersection(const Point& p, const Rectangle& r);
        /**
         * Segment defined by two point (p1, p2) intersecting a rectangle r
         */
        static bool intersection(const Point& p1, const Point& p2, const Rectangle& r);
	    const Vector2<float> get_size() const;
        
        Rectangle& operator=(const Rectangle& rect);
    private:
		float w_, h_;
};

#endif

