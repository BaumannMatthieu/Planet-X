#ifndef __CONTEXT_SCENE_H__
#define __CONTEXT_SCENE_H__

#include "collisable.h"
#include "renderable.h"
#include "quadtree_handler.h"

class ContextScene : public Renderable {
    public:
        ContextScene();
        ~ContextScene();

        virtual void update();
        virtual void draw(SDL_Renderer* renderer);

        void add_entity(RenderablePtr entity);

    private:
        std::vector<RenderablePtr> entitys_;
        QuadtreeHandler quadtree_handler_; 
};

#endif 
