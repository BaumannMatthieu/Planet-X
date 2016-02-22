#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include <memory>
#include <unordered_map>
#include <set>

#define WIDTH_QUAD 1024
#define HEIGHT_QUAD 768

template<typename T>
class Quadtree {
	typedef std::shared_ptr<Quadtree> QuadtreePtr;
	typedef std::shared_ptr<T> TPtr;

	enum {TOP_LEFT,
	      TOP_RIGHT,
	      BOTTOM_LEFT,
	      BOTTOM_RIGHT};

	public:
		Quadtree();
		~Quadtree();

		void insert(const T& element);
		void update();
		void remove_element(const T& element);
		
	private:
//		const std::set& Quadtree<T>::get_location(const T& element);
		
		QuadtreePtr parent_;

		std::vector<QuadtreePtr> children_;
		std::unordered_map<TPtr, std::set<TPtr>> elements_;

		static uint8_t max_elements_;
};

#endif
