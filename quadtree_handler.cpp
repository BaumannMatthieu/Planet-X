#include <iostream>

#include "quadtree_handler.h"
#include "rectangle.h"

QuadtreeHandler::QuadtreeHandler() {
	quadtree_ = std::make_shared<Quadtree>();	
}

QuadtreeHandler::~QuadtreeHandler() {

}


void QuadtreeHandler::update(const std::set<EntityPtr>& collisables) {
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
 
void QuadtreeHandler::detect_collisions() const {
    for(auto& collision : quads_) {
        CollisablePtr first = collision.first;
        if(first->isVertice()) {
            for(auto& quadtree : collision.second) {
                for(auto& second : quadtree->get_elements(first)) {
                    if(second->isBox()) {
                        Collisable::vertice_box_collision(first, second); 
                    }
                }
            }
        }
    }
}

QuadtreePtr QuadtreeHandler::get_quadtree() const {
    return quadtree_;
}

