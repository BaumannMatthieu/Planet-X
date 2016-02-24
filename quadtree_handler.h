#ifndef __QUADTREE_HANDLER_H__
#define __QUADTREE_HANDLER_H__

#include "entity.h"
#include "quadtree.h"

#include <SDL2/SDL.h>

class QuadtreeHandler {
    public:
        QuadtreeHandler();
        ~QuadtreeHandler();

        void insert(const EntityPtr entity_ptr);
        void update(const EntityPtr entity_ptr);

    private:
        std::unordered_map<EntityPtr, std::set<QuadtreePtr>> quads_;    
        QuadtreePtr quadtree_;
};

#endif
