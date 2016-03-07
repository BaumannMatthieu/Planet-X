#ifndef __PATH_H__
#define __PATH_H__

#include <vector>
#include <memory>
#include "vector2.h"
#include "primitive.h"
#include "movable.h"

class Path {
    public:
        Path(const float radius = 50.0f, const bool repeat = true);
        Path(const std::vector<Point>& points, const float radius = 50.0f, const bool repeat = true);
        ~Path();

        void add_point(const Point& point);

        const Vector2<float> execute(std::shared_ptr<Movable> movable);
    private:
    
        uint8_t current_destination_;

        float radius_;
        std::vector<Point> points_;
        bool repeat_;
};

#endif
