#ifndef __CONTEXT_SCENE_H__
#define __CONTEXT_SCENE_H__

#include <queue>

#include "collisable.h"
#include "renderable.h"
#include "quadtree_handler.h"

class ContextScene : public Renderable {
    public:
        ContextScene();
        ~ContextScene();

        void update();
        void draw(SDL_Renderer* renderer);

        void add_entity(RenderablePtr entity);

    private:
        void update_entitys_content();
        
        std::vector<RenderablePtr> entitys_;
        std::queue<RenderablePtr> add_entitys_;

        QuadtreeHandler quadtree_handler_; 
};

#endif 
