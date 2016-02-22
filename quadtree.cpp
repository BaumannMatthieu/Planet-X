#include <memory>
#include <set>
#include <unordered_map>
#include <iostream>
#include "quadtree.h"

uint8_t Quadtree::max_elements_ = 4;
Quadtree::Rect_t Quadtree::global_rect_ = {0.f, 0.f, WIDTH_QUAD, HEIGHT_QUAD};

Quadtree::Quadtree(const RegisterElementFunc_t& func) : func_(func) {
	head_ = std::make_shared<Quad>(nullptr, Quad::NONE);
}

Quadtree::~Quadtree() {
}

void Quadtree::insert(const EntityPtr element_ptr, std::set<QuadPtr>& quads) {
	head_->insert(element_ptr, quads);
}

Quad::Quad(const QuadPtr parent, const uint8_t location) : parent_(parent) {
	num_elements_ = 0;
	if(parent_ == nullptr && location == NONE) {
		rect_ = Quadtree::global_rect_;
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

Quad::~Quad() {
}

void Quad::insert(const EntityPtr element_ptr, std::set<QuadPtr>& quads) {
	if(func_(element_ptr, rect_)) {
		num_elements_++;
		if(children_.empty()) {
			if(elements_.size() < Quadtree::max_elements_) {
				if(elements_.empty()) {
					elements_[element_ptr] = std::set<EntityPtr>();
					return;
				}

				for(auto& kv_inserted : elements_) {
					const EntityPtr element_inserted_ptr(kv_inserted.first());

					elements_[element_ptr].insert(element_inserted_ptr);
					elements_[element_inserted_ptr].insert(element_ptr);
				}
				
				quads.insert(this);
				return;
			}

			children_.push_back(std::make_shared<Quad>(this, TOP_LEFT));
			children_.push_back(std::make_shared<Quad>(this, TOP_RIGHT));
			children_.push_back(std::make_shared<Quad>(this, BOTTOM_LEFT));
			children_.push_back(std::make_shared<Quad>(this, BOTTOM_RIGHT));
		}
		
		for(auto& child_ptr : children_) {
			for(auto& kv_inserted : elements_) {
				const EntityPtr element_already_ptr(kv_inserted.first());
				child_ptr->insert(element_already_ptr);	
			}
			child_ptr->insert(element_ptr);
		}

		if(!elements_.empty())
			elements_.clear();
	}
}

void Quad::update(const EntityPtr element_ptr, std::set<QuadPtr>& quads) {
	if(parent_ == nullptr) {
		return;
	}

	if(!func_(element_ptr, rect_)) { 
		remove(element_ptr);
		quads.erase(this);
	} else {
		for(auto& neighbor_ptr : parent_->children_) {
			if(neighbor_ptr != this) {
				if(quads.find(neighbor_ptr) == quads.end()) {
					if(func_(element_ptr, neighbor_ptr->rect_)) {
						neighbor_ptr->insert(element_ptr, quads);
					}
				}
			}
		}
		parent_->update(element_ptr, quads);
		
	}
}

void Quad::remove(const EntityPtr element_ptr) {
	elements_.erase(element_ptr);
	for(auto& kv_inserted : elements_) {
		kv_inserted.second().erase(element_ptr);
	}

	decrease_num_elements();
}

void Quad::decrease_num_elements() {
	if(parent_ != nullptr) {
		num_elements_--;
		parent_->decrease_num_elements();
	}
}

