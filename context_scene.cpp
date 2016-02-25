#include <ctime>
#include "vector2.h"
#include "context_scene.h"
#include "rectangle.h"

ContextScene::ContextScene() {
	std::srand(std::time(0));
    
/*        Rectangle box1 = Rectangle(Vector2<float>(524, 20), 50.0f, 50.0f);
        EntityPtr entity_ptr1 = std::make_shared<Entity>(box1);
        Rectangle box2 = Rectangle(Vector2<float>(540, 30), 50.0f, 50.0f);
        EntityPtr entity_ptr2 = std::make_shared<Entity>(box2);
        Rectangle box3 = Rectangle(Vector2<float>(570, 50), 50.0f, 50.0f);
        EntityPtr entity_ptr3 = std::make_shared<Entity>(box3);
        Rectangle box4 = Rectangle(Vector2<float>(560, 25), 50.0f, 50.0f);
        EntityPtr entity_ptr4 = std::make_shared<Entity>(box4);
        Rectangle box5 = Rectangle(Vector2<float>(519, 90), 50.0f, 50.0f);
        EntityPtr entity_ptr5 = std::make_shared<Entity>(box5);
        
        entitys_.push_back(entity_ptr1);
        quadtree_handler_.insert(entity_ptr1);
        entitys_.push_back(entity_ptr2);
        quadtree_handler_.insert(entity_ptr2);
        entitys_.push_back(entity_ptr3);
        quadtree_handler_.insert(entity_ptr3);
        entitys_.push_back(entity_ptr4);
        quadtree_handler_.insert(entity_ptr4);
        entitys_.push_back(entity_ptr5);
        quadtree_handler_.insert(entity_ptr5);*/
        /*entitys_.push_back(entity_ptr1);
        quadtree_handler_.insert(entity_ptr1);
        entitys_.push_back(entity_ptr2);
        quadtree_handler_.insert(entity_ptr2);*/

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

    // a supprimer
    //quadtree_handler_.draw(renderer);
    quadtree_handler_.draw(renderer);
}

