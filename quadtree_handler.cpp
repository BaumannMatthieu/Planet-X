#include <iostream>

#include "quadtree_handler.h"
#include "rectangle.h"

QuadtreeHandler::QuadtreeHandler() {
	quadtree_ = std::make_shared<Quadtree>();	
}

QuadtreeHandler::~QuadtreeHandler() {

}


void QuadtreeHandler::update(const std::vector<CollisablePtr>& collisables) {
    quadtree_.reset();
    quads_.clear();

	quadtree_ = std::make_shared<Quadtree>();	
    
	for(auto& col : collisables) {
		quadtree_->insert(col, quads_, 0);
	}
}


void QuadtreeHandler::insert(const CollisablePtr collisable_ptr) {
    quadtree_->insert(collisable_ptr, quads_, 0);
}

void QuadtreeHandler::update(const CollisablePtr collisable_ptr) {
	quadtree_->decrease_num_elements(collisable_ptr);

	for(auto& quad : quads_[collisable_ptr]) {
		quad->remove(collisable_ptr, quads_);
	}
	for(auto& quad : quads_[collisable_ptr]) {
    		quad->update(quads_);
	}
	quads_[collisable_ptr].clear();    	
	
    quadtree_->insert(collisable_ptr, quads_, 0);
}
 
QuadtreePtr QuadtreeHandler::get_quadtree() const {
    return quadtree_;
}

