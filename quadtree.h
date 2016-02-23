#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include <memory>
#include <unordered_map>
#include <set>
#include <functional>

#include "entity.h"

#define WIDTH_QUAD 1024.0f
#define HEIGHT_QUAD 768.0f

/*
class Quad;
class Quadtree {
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
		static uint8_t max_elements_;
		static Rect_t global_rect_;

		Quadtree(const RegisterElementFunc_t& func);
		~Quadtree();
		
		void insert(const EntityPtr element_ptr, std::set<std::shared_ptr<Quad>>& quads);
	private:
		std::shared_ptr<Quad> head_;
};

class Quad {
	public: 
        Quad(const std::shared_ptr<Quad> parent, const uint8_t location);
		~Quad();

		void insert(const EntityPtr element_ptr, std::set<std::shared_ptr<Quad>>& quads);
		void update(const EntityPtr element_ptr, std::set<std::shared_ptr<Quad>>& quads);
	
	private:	
		void remove(const EntityPtr element_ptr);
		void decrease_num_elements();
	
	private:
		std::shared_ptr<Quad> parent_;
		uint16_t num_elements_;
		
		Quadtree::Rect_t rect_;
		std::vector<std::shared_ptr<Quad>> children_;
		
		std::unordered_map<EntityPtr, std::set<EntityPtr>> elements_;
};

typedef std::shared_ptr<Quad> QuadPtr;
*/
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

       	void insert(const EntityPtr element_ptr, std::set<std::shared_ptr<Quadtree>>& quads);
		void update(const EntityPtr element_ptr, std::set<std::shared_ptr<Quadtree>>& quads);
	
        static void set_element_in_quad_func(const RegisterElementFunc_t& func);

	    static uint8_t max_elements_;
		static Rect_t global_rect_;

    private:    
		void remove(const EntityPtr element_ptr);
		void decrease_num_elements();
	
	private:
		std::shared_ptr<Quadtree> parent_;
		uint16_t num_elements_;
		
		Quadtree::Rect_t rect_;
		std::vector<std::shared_ptr<Quadtree>> children_;
		
		std::unordered_map<EntityPtr, std::set<EntityPtr>> elements_;
};

typedef std::shared_ptr<Quadtree> QuadtreePtr;

#endif
