#include <memory>
#include <set>
#include <unordered_map>
#include <iostream>
#include "quadtree.h"

uint8_t Quadtree::max_elements_ = 4;

Quadtree::Rect_t Quadtree::global_rect_ = {0.f, 0.f, WIDTH_QUAD, HEIGHT_QUAD};

static Quadtree::RegisterElementFunc_t element_in_quad_func = nullptr;

void Quadtree::set_element_in_quad_func(const RegisterElementFunc_t& func) {
    std::cout << "jkshdf" << std::endl;
    element_in_quad_func = func;
}

Quadtree::Quadtree(const QuadtreePtr parent, const uint8_t location) : parent_(parent) {
	num_elements_ = 0;
	if(parent_ == nullptr && location == NONE) {
		rect_ = global_rect_;
		return;
	}

	if(parent_ == nullptr) {
		std::cerr << "error : this node has no parent !" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	const Quadtree::Rect_t parent_rect = parent_->rect_;
	const float w = parent_rect.w/2.f;
	const float h = parent_rect.h/2.f;

	switch(location) {
		case TOP_LEFT:
			rect_ = {parent_rect.x, parent_rect.y,
				 w, h};
			break;
		case TOP_RIGHT:
			rect_ = {parent_rect.x + w, parent_rect.y,
				 w, h};
			break;
		case BOTTOM_LEFT:
			rect_ = {parent_rect.x, parent_rect.y + h,
				 w, h};
			break;
		case BOTTOM_RIGHT:
			rect_ = {parent_rect.x + w, parent_rect.y + h,
				 w, h};
			break;
		default:
			break;
	}
}

Quadtree::~Quadtree() {

}

void Quadtree::insert(const EntityPtr element_ptr, std::set<QuadtreePtr>& quads) {
	if(element_in_quad_func(element_ptr, rect_)) {
		num_elements_++;
		if(children_.empty()) {
            if(elements_.size() < max_elements_) {
				if(elements_.empty()) {
					elements_[element_ptr] = std::set<EntityPtr>();
                    quads.insert(shared_from_this());
					return;
				}

				for(auto& kv_inserted : elements_) {
					const EntityPtr element_inserted_ptr(kv_inserted.first);

					elements_[element_ptr].insert(element_inserted_ptr);
					elements_[element_inserted_ptr].insert(element_ptr);
				}
				
                quads.insert(shared_from_this());
				return;
			}

			children_.push_back(std::make_shared<Quadtree>(shared_from_this(), TOP_LEFT));
			children_.push_back(std::make_shared<Quadtree>(shared_from_this(), TOP_RIGHT));
			children_.push_back(std::make_shared<Quadtree>(shared_from_this(), BOTTOM_LEFT));
			children_.push_back(std::make_shared<Quadtree>(shared_from_this(), BOTTOM_RIGHT));
		}
		
		for(auto& child_ptr : children_) {
			for(auto& kv_inserted : elements_) {
				const EntityPtr element_already_ptr(kv_inserted.first);
				child_ptr->insert(element_already_ptr, quads);	
			}
			child_ptr->insert(element_ptr, quads);
		}

		if(!elements_.empty())
			elements_.clear();
	}
}

void Quadtree::update(const EntityPtr element_ptr, std::set<QuadtreePtr>& quads) {
	if(parent_ == nullptr) {
		return;
	}

	if(!element_in_quad_func(element_ptr, rect_)) { 
		remove(element_ptr);
		quads.erase(shared_from_this());

        if(parent_->num_elements_ < max_elements_) {
            for(auto& neighbor_ptr : parent_->children_) {
                for(auto& kv_inserted : neighbor_ptr->elements_) {
                    parent_->elements_.insert(kv_inserted);
                }
                neighbor_ptr->elements_.clear();   
                neighbor_ptr->children_.clear();   
            }
        }
	} else {
		for(auto& neighbor_ptr : parent_->children_) {
			if(neighbor_ptr != shared_from_this()) {
				if(quads.find(neighbor_ptr) == quads.end()) {
					if(element_in_quad_func(element_ptr, neighbor_ptr->rect_)) {
						neighbor_ptr->insert(element_ptr, quads);
					}
				}
			}
		}
		parent_->update(element_ptr, quads);
	}
}

void Quadtree::remove(const EntityPtr element_ptr) {
	elements_.erase(element_ptr);
	for(auto& kv_inserted : elements_) {
		kv_inserted.second.erase(element_ptr);
	}

	decrease_num_elements();
}

void Quadtree::decrease_num_elements() {
	if(parent_ != nullptr) {
		num_elements_--;
		parent_->decrease_num_elements();
	}
}
