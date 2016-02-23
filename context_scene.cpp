#include <ctime>
#include "vector2.h"
#include "context_scene.h"
#include "rectangle.h"

ContextScene::ContextScene() {
	std::srand(std::time(0));
    
    for(unsigned int i = 0; i < 50; i++) {
        Rectangle box = Rectangle(Vector2<float>(std::rand()%1024, std::rand()%768), 50.0f, 50.0f);
        
        EntityPtr entity_ptr = std::make_shared<Entity>(box);
        
        entitys_.push_back(entity_ptr);
        quadtree_handler_.insert(entity_ptr);
    }
}

ContextScene::~ContextScene() {

}

void ContextScene::update() {
    for(auto& entity : entitys_) {
        //entity->move();
        //quadtree_handler_.update();
    }
}

void ContextScene::draw(SDL_Renderer* renderer) {
    for(auto& entity : entitys_) {
        entity->draw(renderer);
    }

    // a supprimer
    quadtree_handler_.draw(renderer);
}

