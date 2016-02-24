#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include <memory>
#include <unordered_map>
#include <set>
#include <functional>
#include <iostream>

#include <SDL2/SDL.h>
#include "entity.h"

#define WIDTH_QUAD 1024.0f
#define HEIGHT_QUAD 768.0f

class Quadtree : public std::enable_shared_from_this<Quadtree> {
	public:

    		typedef struct Rect_t {
			float x, y, w, h;
		} Rect_t;
    
    		typedef std::function<bool(const EntityPtr, const Rect_t&)> RegisterElementFunc_t;

		enum {TOP_LEFT,
	      	      TOP_RIGHT,
  	      	      BOTTOM_LEFT,
     	  	      BOTTOM_RIGHT,
	      	      NONE};
	
	public:
		Quadtree(const std::shared_ptr<Quadtree> parent=nullptr, const uint8_t location=NONE);
			~Quadtree();

		void insert(const EntityPtr element_ptr, std::unordered_map<EntityPtr, std::set<std::shared_ptr<Quadtree>>>& quads_map);
		
		void update(std::unordered_map<EntityPtr, std::set<std::shared_ptr<Quadtree>>>& quads_map);

		static void set_element_in_quad_func(const RegisterElementFunc_t& func);

		static uint8_t max_elements_;
		static Rect_t global_rect_;

		void remove(const EntityPtr element_ptr, std::unordered_map<EntityPtr, std::set<std::shared_ptr<Quadtree>>>& quads_map);
			
		void decrease_num_elements(const EntityPtr element_ptr);
    
	private:    
        	void get_all_children_elt(std::set<EntityPtr>& elts);
        	bool is_parent(const EntityPtr element_ptr);
    	
	private:
		std::shared_ptr<Quadtree> parent_;
	    	uint16_t num_elements_;	
		Quadtree::Rect_t rect_;
		std::vector<std::shared_ptr<Quadtree>> children_;
		
		std::unordered_map<EntityPtr, std::set<EntityPtr>> elements_;
};

typedef std::shared_ptr<Quadtree> QuadtreePtr;

#endif
