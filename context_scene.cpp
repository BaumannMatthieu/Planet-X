#include <ctime>
#include "vector2.h"
#include "context_scene.h"
#include "rectangle.h"

ContextScene::ContextScene() {
	std::srand(std::time(0));
    
    	for(unsigned int i = 0; i < 50; i++) {
        	Rectangle box(Vector2<float>(rand()%1024, rand()%768), 50.f, 50.f);
		EntityPtr entity = std::make_shared<Entity>(box);

        	entitys_.push_back(entity);
        	quadtree_handler_.insert(entity);
    	}
}

ContextScene::~ContextScene() {

}

void ContextScene::update() {
    for(auto& entity : entitys_) {
            entity->move();
            quadtree_handler_.update(entity);
    }
}
void ContextScene::draw(SDL_Renderer* renderer) {
    for(auto& entity : entitys_) {
        entity->draw(renderer);
    }
}

