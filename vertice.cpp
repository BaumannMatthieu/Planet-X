#include "vertice.h"

Vertice::Vertice(const Point& point) : point_(point) {

}

Vertice::~Vertice() {

}
    
const Point& Vertice::get_position() const {
    return point_;
}

bool Vertice::compute(const Rectangle& rect) const {
   return Rectangle::intersection(point_, rect); 
}


