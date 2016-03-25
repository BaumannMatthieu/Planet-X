#include <ctime>
#include "vector2.h"
#include "context_scene.h"
#include "rectangle.h"
#include "blaster_ship.h"
#include "player.h"
#include "sun.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

PlayerPtr player;

ContextScene::ContextScene() {
	std::srand(std::time(0));
    
    player = std::make_shared<Player>();
    player->init_missile_handler();
    
	entitys_.insert(player);
    avoidables_.insert(player);
    life_bars_ui_.insert(std::make_shared<LifeUi>(player));    


    std::set<EnemyShipPtr> group_ships;
    EnemyShipPtr leader;

    for(unsigned int i = 0; i < 7; i++) {
        BlasterPtr blaster = std::make_shared<Blaster>(Point(rand()%WINDOW_WIDTH, rand()%WINDOW_HEIGHT));
        blaster->init_missile_handler();

        entitys_.insert(blaster);
        avoidables_.insert(blaster);
        life_bars_ui_.insert(std::make_shared<LifeUi>(blaster));    

        if(i >= 1 && i < 7) {
            group_ships.insert(blaster);
        } else if(i == 0) {
            leader = blaster;
        }
    }

    group_ = std::make_shared<GroupShips>(group_ships, leader);

	SunPtr sun = std::make_shared<Sun>();
	entitys_.insert(sun);
    avoidables_.insert(sun);
    
    for(auto& collisable : entitys_) {
        quadtree_handler_.insert(collisable);
    }
}

ContextScene::~ContextScene() {

}

void ContextScene::update() {

    update_entitys_content();
    for(auto& entity : entitys_) {
        entity->update();
    }
    
    quadtree_handler_.update(entitys_);

    quadtree_handler_.detect_collisions();

    for(auto& life_ui : life_bars_ui_) {
        life_ui->update();
    }
}
void ContextScene::draw(SDL_Renderer* renderer) {
    for(auto& entity : entitys_) {
        entity->draw(renderer);
    }
    quadtree_handler_.get_quadtree()->draw(renderer);
    
    for(auto& life_ui : life_bars_ui_) {
        life_ui->draw(renderer);
    }
}

const std::set<AvoidablePtr>& ContextScene::get_obstacles() const {
    return avoidables_; 
}   

void ContextScene::add_entity(EntityPtr entity) {
    add_entitys_.push(entity);
}

void ContextScene::delete_entity(EntityPtr entity) {
    entitys_.erase(entity);
}
/*
void ContextScene::add_collisable(CollisablePtr collisable) {
    add_collisables_.push(collisable);
}
*/
void ContextScene::update_entitys_content() {
    while(!add_entitys_.empty()) {
        entitys_.insert(add_entitys_.front());
        add_entitys_.pop();
    }
    
  /*  while(!add_collisables_.empty()) {
        collisables_.push_back(add_collisables_.front());
        quadtree_handler_.insert(add_collisables_.front());
        add_collisables_.pop();
    }*/
}
