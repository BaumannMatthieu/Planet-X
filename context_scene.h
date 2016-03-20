#ifndef __CONTEXT_SCENE_H__
#define __CONTEXT_SCENE_H__

#include <queue>

#include "entity.h"
#include "quadtree_handler.h"

class ContextScene : public Renderable {
    public:
        ContextScene();
        ~ContextScene();

        void update();
        void draw(SDL_Renderer* renderer);

        void add_entity(EntityPtr entity);
        void delete_entity(EntityPtr entity);
  //      void add_collisable(CollisablePtr collisable);

    private:
        void update_entitys_content();
    /*    
        std::vector<RenderablePtr> entitys_;
        std::vector<CollisablePtr> collisables_;

        std::queue<RenderablePtr> add_entitys_;
        std::queue<CollisablePtr> add_collisables_;
*/
        std::set<EntityPtr> entitys_;
        std::queue<EntityPtr> add_entitys_;

        QuadtreeHandler quadtree_handler_; 
};

#endif 
