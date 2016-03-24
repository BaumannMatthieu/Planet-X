#ifndef __CONTEXT_SCENE_H__
#define __CONTEXT_SCENE_H__

#include <queue>

#include "entity.h"
#include "avoidable.h"
#include "quadtree_handler.h"
#include "group_ship.h"

class ContextScene : public Renderable {
    public:
        ContextScene();
        ~ContextScene();

        void update();
        void draw(SDL_Renderer* renderer);

        void add_entity(EntityPtr entity);
        void delete_entity(EntityPtr entity);
  //      void add_collisable(CollisablePtr collisable);
        const std::set<AvoidablePtr>& get_obstacles() const;

    private:
        void update_entitys_content();
    /*    
        std::vector<RenderablePtr> entitys_;
        std::vector<CollisablePtr> collisables_;

        std::queue<RenderablePtr> add_entitys_;
        std::queue<CollisablePtr> add_collisables_;
*/
        GroupShipsPtr group_;

        std::set<AvoidablePtr> avoidables_;
        std::set<EntityPtr> entitys_;
        std::queue<EntityPtr> add_entitys_;

        QuadtreeHandler quadtree_handler_; 
};

#endif 
