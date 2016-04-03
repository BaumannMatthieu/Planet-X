#ifndef __QUADTREE_HANDLER_H__
#define __QUADTREE_HANDLER_H__

#include "collisable.h"
#include "entity.h"
#include "quadtree.h"
#include <vector>

#include <SDL2/SDL.h>

class QuadtreeHandler {
    public:
        QuadtreeHandler();
        ~QuadtreeHandler();

        void insert(const CollisablePtr collisable_ptr);
        void update(const CollisablePtr collisable_ptr);

        void update(const std::set<EntityPtr>& collisables);
        void detect_collisions() const;

        QuadtreePtr get_quadtree() const;

    private:
        std::unordered_map<CollisablePtr, std::set<QuadtreePtr>> quads_;    
        QuadtreePtr quadtree_;
};

#endif
