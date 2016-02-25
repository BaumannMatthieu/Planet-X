#include <ctime>
#include "vector2.h"
#include "context_scene.h"
#include "rectangle.h"
#include "ship.h"
#include "sun.h"

ContextScene::ContextScene() {
	std::srand(std::time(0));
    
    	for(unsigned int i = 0; i < 1; i++) {
        	Rectangle box(Vector2<float>(rand()%1024, rand()%768), 20.f, 20.f);
		    ShipPtr ship = std::make_shared<Ship>(box);

        	entitys_.push_back(ship);
        	quadtree_handler_.insert(ship);
    	}
	SunPtr sun = std::make_shared<Sun>();
	entitys_.push_back(sun);
	quadtree_handler_.insert(sun);
}

ContextScene::~ContextScene() {

}

void ContextScene::update() {
   	for(auto& entity : entitys_) {
            	entity->update();
		//quadtree_handler_.update(entity);
    	}
}
void ContextScene::draw(SDL_Renderer* renderer) {
    for(auto& entity : entitys_) {
        entity->draw(renderer);
    }
}

