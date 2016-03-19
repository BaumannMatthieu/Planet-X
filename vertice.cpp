#include "vertice.h"

Vertice::Vertice(const Point& point) : center_mass_(point) {

}

Vertice::~Vertice() {

}
    
const Point& Vertice::get_position() const {
    return center_mass_;
}

bool Vertice::compute(const Rectangle& rect) const {
   return Rectangle::intersection(Rectangle(center_mass_, 10.f, 10.f), rect); 
}


