#ifndef __QUADTREE_HANDLER_H__
#define __QUADTREE_HANDLER_H__

#include "entity.h"
#include "quadtree.h"

#include "renderable.h"
#include <SDL2/SDL.h>

class QuadtreeHandler : public Renderable {
    public:
        QuadtreeHandler();
        ~QuadtreeHandler();

        void insert(const EntityPtr entity_ptr);
        void update(const EntityPtr entity_ptr);
        virtual void draw(SDL_Renderer* renderer) {
            quadtree_->draw(renderer);
        } 

    private:
        std::unordered_map<EntityPtr, std::set<QuadtreePtr>> quads_;    
        QuadtreePtr quadtree_;
};

#endif
