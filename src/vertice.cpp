#include "../include/vertice.h"

Vertice::Vertice(const Point& point) : center_mass_(point) {

}

Vertice::~Vertice() {

}
    
const Point& Vertice::get_position() const {
    return center_mass_;
}

