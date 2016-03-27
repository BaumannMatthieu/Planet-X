#include <iostream>
#include <memory>

#include "collisable.h"
#include "shoot.h"
#include "ship.h"

#include "context_scene.h"

extern ContextScene scene;

bool Collisable::isShip() const {
    return false;
}

bool Collisable::is_missile() const {
    return false;
}

bool Collisable::isVertice() const {
    return false;
}

bool Collisable::isBox() const {
    return false;
}

void Collisable::vertice_box_collision(const CollisablePtr first, const CollisablePtr second) {
    if(first->is_missile() && second->isShip()) {
        MissilePtr missile = std::dynamic_pointer_cast<Missile>(first);
        ShipPtr ship = std::dynamic_pointer_cast<Ship>(second);

        if(auto caster = missile->get_caster().lock()) {
            if(!caster->is_player() && !ship->is_player()) {
                return;
            }
        
            if(caster->is_player() && ship->is_player()) {
                return;
            }
        }
        if(missile->compute(ship->get_box())) {
            ship->take_damage(missile->get_damage());        
            scene.delete_entity(missile);
        }
    }
}
