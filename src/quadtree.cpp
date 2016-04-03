#include <memory>
#include <set>
#include <unordered_map>
#include <iostream>
#include "../include/quadtree.h"
#include "../include/rectangle.h"

uint8_t Quadtree::max_elements_ = 4;
uint8_t Quadtree::max_deep_ = 5;

Quadtree::Quadtree(const QuadtreePtr parent, const uint8_t location) : parent_(parent), num_elements_(0) {
    if(parent_ == nullptr && location == NONE) {
		rect_ = Rectangle(Vector2<float>(0.f, 0.f), WINDOW_WIDTH, WINDOW_HEIGHT);
		return;
	}

	if(parent_ == nullptr) {
		std::cerr << "error : this node has no parent !" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	const Rectangle parent_rect = parent_->rect_;
    const Vector2<float> parent_rect_pos = parent_rect.get_pos();
	const float w = parent_rect.get_size().x_/2.f;
	const float h = parent_rect.get_size().y_/2.f;

	switch(location) {
		case TOP_LEFT:
			rect_ = Rectangle(parent_rect_pos, w, h);
			break;
		case TOP_RIGHT:
			rect_ = Rectangle(Vector2<float>(parent_rect_pos.x_ + w, parent_rect_pos.y_),
				 w, h);
			break;
		case BOTTOM_LEFT:
			rect_ = Rectangle(Vector2<float>(parent_rect_pos.x_, parent_rect_pos.y_ + h),
				 w, h);
			break;
		case BOTTOM_RIGHT:
			rect_ = Rectangle(Vector2<float>(parent_rect_pos.x_ + w, parent_rect_pos.y_ + h),
			    w, h);
			break;
		default:
			break;
	}
}

Quadtree::~Quadtree() {

}

void Quadtree::insert(const CollisablePtr element_ptr, std::unordered_map<CollisablePtr, std::set<QuadtreePtr>>& quads_map, const uint8_t deep) {
	if(element_ptr->compute(rect_)) {
        num_elements_++;
		if(children_.empty()) {
            if(elements_.size() < max_elements_||deep >= max_deep_) {
				if(elements_.empty()) {
					elements_[element_ptr] = std::set<CollisablePtr>();
	                quads_map[element_ptr].insert(shared_from_this());
					return;
				}

				for(auto& kv_inserted : elements_) {
					const CollisablePtr element_inserted_ptr(kv_inserted.first);

					elements_[element_ptr].insert(element_inserted_ptr);
					elements_[element_inserted_ptr].insert(element_ptr);
				}
				
                quads_map[element_ptr].insert(shared_from_this());
				return;
			}

			children_.push_back(std::make_shared<Quadtree>(shared_from_this(), TOP_LEFT));
			children_.push_back(std::make_shared<Quadtree>(shared_from_this(), TOP_RIGHT));
			children_.push_back(std::make_shared<Quadtree>(shared_from_this(), BOTTOM_LEFT));
			children_.push_back(std::make_shared<Quadtree>(shared_from_this(), BOTTOM_RIGHT));
	        
            for(auto& child_ptr : children_) {
			    for(auto& kv_inserted : elements_) {
				    const CollisablePtr element_already_ptr(kv_inserted.first);
                    quads_map[element_already_ptr].erase(shared_from_this());
				    child_ptr->insert(element_already_ptr, quads_map, deep + 1);	
                }
            }
		    if(!elements_.empty())
			    elements_.clear();
    	}
		
        for(auto& child_ptr : children_) {
		    child_ptr->insert(element_ptr, quads_map, deep + 1);
		}
	}
}

void Quadtree::update(std::unordered_map<CollisablePtr, std::set<QuadtreePtr>>& quads_map) {
	if(parent_ == nullptr) {
		return;
	}

 	if(parent_->num_elements_ < max_elements_ && !parent_->children_.empty()) {
		std::set<CollisablePtr> elts_to_insert; 
		parent_->get_all_children_elt(elts_to_insert);
		    
		parent_->children_.clear();
		parent_->num_elements_ = 0;
		
		for(auto& elt_to_insert : elts_to_insert) {
		    quads_map[elt_to_insert].erase(shared_from_this());
		    parent_->insert(elt_to_insert, quads_map, 0);
		}

		parent_->update(quads_map); 
    }
}

void Quadtree::get_all_children_elt(std::set<CollisablePtr>& elts) {
    for(auto& elt : elements_) {
        elts.insert(elt.first);
    }

    for(auto& child : children_) {
        child->get_all_children_elt(elts);
    }
}

void Quadtree::decrease_num_elements(const CollisablePtr element_ptr) {
    if(is_parent(element_ptr)) {
	    num_elements_--;
        for(auto& child : children_) {
            child->decrease_num_elements(element_ptr);
        }
    }
}

bool Quadtree::is_parent(const CollisablePtr element_ptr) {
    for(auto& child : children_) {
        if(child->is_parent(element_ptr)) {
            return true;
        }
    }

    return (elements_.find(element_ptr) != elements_.end());
}

void Quadtree::remove(const CollisablePtr element_ptr, std::unordered_map<CollisablePtr, std::set<QuadtreePtr>>& quads_map) {
    elements_.erase(element_ptr);

	for(auto& kv_inserted : elements_) {
		kv_inserted.second.erase(element_ptr);
	}
}

std::set<CollisablePtr>& Quadtree::get_elements(CollisablePtr first) {
    return elements_[first];
}
