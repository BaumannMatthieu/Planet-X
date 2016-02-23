#ifndef __CONTEXT_SCENE_H__
#define __CONTEXT_SCENE_H__

#include "entity.h"
#include "renderable.h"
#include "quadtree_handler.h"

class ContextScene : public Renderable {
    public:
        ContextScene();
        ~ContextScene();

        void update();
        virtual void draw(SDL_Renderer* renderer);

    private:
        std::vector<EntityPtr> entitys_;
        QuadtreeHandler quadtree_handler_; 
};

#endif 
