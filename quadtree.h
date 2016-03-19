#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include <memory>
#include <unordered_map>
#include <set>
#include <iostream>

#include <SDL2/SDL.h>
#include "collisable.h"
#include "rectangle.h"

#define WIDTH_QUAD 1920.0f
#define HEIGHT_QUAD 1080.0f

class Quadtree : public std::enable_shared_from_this<Quadtree>,
                 public Renderable {
	public:
		enum {TOP_LEFT,
	    	  TOP_RIGHT,
  	      	  BOTTOM_LEFT,
     	  	  BOTTOM_RIGHT,
	      	  NONE};
	
	public:
		Quadtree(const std::shared_ptr<Quadtree> parent=nullptr, const uint8_t location=NONE);
		~Quadtree();

		void insert(const CollisablePtr element_ptr, std::unordered_map<CollisablePtr, std::set<std::shared_ptr<Quadtree>>>& quads_map, const uint8_t deep);
		
		void update(std::unordered_map<CollisablePtr, std::set<std::shared_ptr<Quadtree>>>& quads_map);

		static uint8_t max_elements_;
		static uint8_t max_deep_;

		void remove(const CollisablePtr element_ptr, std::unordered_map<CollisablePtr, std::set<std::shared_ptr<Quadtree>>>& quads_map);
			
		void decrease_num_elements(const CollisablePtr element_ptr);
    
        void update() {

        }

        void draw(SDL_Renderer* renderer) {
            rect_.draw(renderer);
            for(auto& child : children_) {
                child->draw(renderer);
            }
        }

	private:    
        void get_all_children_elt(std::set<CollisablePtr>& elts);
        bool is_parent(const CollisablePtr element_ptr);
    	
	private:
		std::shared_ptr<Quadtree> parent_;
	    uint16_t num_elements_;	
		
        Rectangle rect_;
		std::vector<std::shared_ptr<Quadtree>> children_;
		
		std::unordered_map<CollisablePtr, std::set<CollisablePtr>> elements_;
};

typedef std::shared_ptr<Quadtree> QuadtreePtr;

#endif
