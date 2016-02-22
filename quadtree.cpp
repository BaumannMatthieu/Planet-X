#include <memory>
#include <set>
#include <unordered_map>
#include "quadtree.h"

template<typename T>
uint8_t Quadtree<T>::max_elements_ = 4;

template<typename T>
Quadtree<T>::Quadtree() : parent_(nullptr) {
	
}

template<typename T>
Quadtree<T>::~Quadtree() {
	
}

template<typename T>
void Quadtree<T>::insert(const T& element) {
	if(elements_.size() < max_elements_) {
		const TPtr element_insert_ptr(&element);

		for(auto& element_ptr : elements_) {
			const TPtr element_already_ptr(element_ptr.first());

			elements_[element_insert_ptr].insert(element_already_ptr);
			elements_[element_already_ptr].insert(element_insert_ptr);
		}
		return;
	}
	
	children_.push_back(std::make_shared<Quadtree>());
	children_.push_back(std::make_shared<Quadtree>());
	children_.push_back(std::make_shared<Quadtree>());
	children_.push_back(std::make_shared<Quadtree>());

		
}

/*template<>
const std::set& Quadtree<Primitive>::get_location(const Primitive& element) {
}*/

template<typename T>
void Quadtree<T>::update() {

}

template<typename T>
void Quadtree<T>::remove_element(const T& element) {

}

