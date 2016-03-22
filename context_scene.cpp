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
    
    for(unsigned int i = 0; i < 5; i++) {
        Rectangle box(Vector2<float>(rand()%WINDOW_WIDTH, rand()%WINDOW_HEIGHT), 30.f, 30.f);
        BlasterPtr blaster = std::make_shared<Blaster>(box);
        blaster->init_missile_handler();

        entitys_.insert(blaster);
        avoidables_.insert(blaster);
    }

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
}
void ContextScene::draw(SDL_Renderer* renderer) {
    for(auto& entity : entitys_) {
        entity->draw(renderer);
    }
    quadtree_handler_.get_quadtree()->draw(renderer);
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
