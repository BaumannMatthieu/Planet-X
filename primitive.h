#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "vector2.h"
#include "renderable.h"
#include <vector>

typedef Vector2<float> Point;

class Primitive : public Renderable {
	public:
		Primitive();
		Primitive(const std::vector<Point>& points, const Point& pos);
		virtual ~Primitive();

		void translate(const Vector2<float>& vector);
		
		virtual void draw(SDL_Renderer* renderer);
        virtual void update();

		virtual bool is_rectangle() const;
		virtual bool is_polygon() const;
    
        const Point& get_pos() const;
        const std::vector<Point>& get_points() const;

        Primitive& operator=(const Primitive& primitive);
	protected:
		std::vector<Point> points_;
		Point pos_;

};

#endif
