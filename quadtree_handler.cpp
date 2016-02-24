#include <iostream>

#include "quadtree_handler.h"
#include "rectangle.h"

QuadtreeHandler::QuadtreeHandler() {
    Quadtree::set_element_in_quad_func([](const EntityPtr entity, const Quadtree::Rect_t& rect_qt) -> bool {
        Rectangle rect = entity->get_box();
        if(rect.get_pos().x_ + rect.get_size().x_ < rect_qt.x || 
           rect.get_pos().y_ + rect.get_size().y_ < rect_qt.y ||
           rect_qt.x + rect_qt.w < rect.get_pos().x_ ||
           rect_qt.y + rect_qt.h < rect.get_pos().y_) {
            return false;
        }

        return true;
    });
	quadtree_ = std::make_shared<Quadtree>();	
}

QuadtreeHandler::~QuadtreeHandler() {

}

void QuadtreeHandler::insert(const EntityPtr entity_ptr) {
    quadtree_->insert(entity_ptr, quads_);
}

void QuadtreeHandler::update(const EntityPtr entity_ptr) {
	quadtree_->decrease_num_elements(entity_ptr);

	for(auto& quad : quads_[entity_ptr]) {
		quad->remove(entity_ptr, quads_);
	}
	for(auto& quad : quads_[entity_ptr]) {
    		quad->update(quads_);
	}
	quads_[entity_ptr].clear();    	
	
    	quadtree_->insert(entity_ptr, quads_);
}
 

