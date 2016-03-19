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
	entitys_.push_back(player);
	collisables_.push_back(player);
    
    for(unsigned int i = 0; i < 5; i++) {
        Rectangle box(Vector2<float>(rand()%WINDOW_WIDTH, rand()%WINDOW_HEIGHT), 20.f, 20.f);
        BlasterPtr blaster = std::make_shared<Blaster>(box);

        entitys_.push_back(blaster);
        collisables_.push_back(blaster);
    }

	SunPtr sun = std::make_shared<Sun>();
	entitys_.push_back(sun);
	collisables_.push_back(sun);
    
    for(auto& collisable : collisables_) {
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
    
    quadtree_handler_.update(collisables_);
}
void ContextScene::draw(SDL_Renderer* renderer) {
    for(auto& entity : entitys_) {
        entity->draw(renderer);
    }
    quadtree_handler_.get_quadtree()->draw(renderer);
}

void ContextScene::add_entity(RenderablePtr entity) {
    add_entitys_.push(entity);
}

void ContextScene::add_collisable(CollisablePtr collisable) {
    add_collisables_.push(collisable);
}

void ContextScene::update_entitys_content() {
    while(!add_entitys_.empty()) {
        entitys_.push_back(add_entitys_.front());
        add_entitys_.pop();
    }
    
    while(!add_collisables_.empty()) {
        collisables_.push_back(add_collisables_.front());
        quadtree_handler_.insert(add_collisables_.front());
        add_collisables_.pop();
    }
}
