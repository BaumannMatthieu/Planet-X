#ifndef __CONTEXT_SCENE_H__
#define __CONTEXT_SCENE_H__

#include <memory>
#include <queue>

#include "entity.h"
#include "avoidable.h"
#include "quadtree_handler.h"
#include "group_ship.h"
#include "group_asteroid.h"
#include "life_ui.h"

class ContextScene : public Renderable {
    public:
        ContextScene();
        ~ContextScene();

        void update();
        void draw(SDL_Renderer* renderer);

        void add_entity(EntityPtr entity);
        void delete_entity(EntityPtr entity);
        
        const std::set<AvoidablePtr>& get_obstacles() const;

    private:
        void update_entitys_content();

        std::set<GroupShipsPtr> groups_;
        GroupAsteroids group_asteroids_;

        std::set<AvoidablePtr> avoidables_;
       
        std::set<EntityPtr> entitys_;
        std::queue<EntityPtr> add_entitys_;

        std::set<LifeUiPtr> life_bars_ui_;

        QuadtreeHandler quadtree_handler_; 
};

typedef std::shared_ptr<ContextScene> ContextScenePtr;

#endif 
