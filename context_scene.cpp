#include <ctime>
#include "vector2.h"
#include "context_scene.h"
#include "rectangle.h"
#include "blaster_ship.h"
#include "player.h"
#include "sun.h"

PlayerPtr player;

ContextScene::ContextScene() {
	std::srand(std::time(0));
    
    for(unsigned int i = 0; i < 1; i++) {
        Rectangle box(Vector2<float>(rand()%1024, rand()%768), 20.f, 20.f);
        BlasterPtr blaster = std::make_shared<Blaster>(box);

        entitys_.push_back(blaster);
        //quadtree_handler_.insert(ship);
    }
	SunPtr sun = std::make_shared<Sun>();
	entitys_.push_back(sun);
	//quadtree_handler_.insert(sun);

    player = std::make_shared<Player>();
	entitys_.push_back(player);
	//quadtree_handler_.insert(player);
}

ContextScene::~ContextScene() {

}

void ContextScene::update() {
    update_entitys_content();
    for(auto& entity : entitys_) {
            entity->update();
            /* We know the type is an entity or a missile who
             * are derived from both renderable and collisable
             * a static_cast is a good option */
             //quadtree_handler_.update(entity);
    }
}
void ContextScene::draw(SDL_Renderer* renderer) {
    for(auto& entity : entitys_) {
        entity->draw(renderer);
    }
}

void ContextScene::add_entity(RenderablePtr entity) {
    add_entitys_.push(entity);
}

void ContextScene::update_entitys_content() {
    while(!add_entitys_.empty()) {
        entitys_.push_back(add_entitys_.front());
        add_entitys_.pop();
    }
}
