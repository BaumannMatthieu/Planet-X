#ifndef __PATH_H__
#define __PATH_H__

#include <vector>
#include <memory>
#include "vector2.h"
#include "primitive.h"
class Ship;

class Path {
    public:
        Path(const float radius = 50.0f, const bool repeat = true);
        Path(const std::vector<Point>& points, const float radius = 50.0f, const bool repeat = true);
        ~Path();

        void add_point(const Point& point);
        void clear();

        const Vector2<float> execute(std::shared_ptr<Ship> ship);
    
    protected:
        std::vector<Point> points_;
    private:
        float radius_;
        bool repeat_;
        uint8_t current_destination_;

};

#endif
