#include "missile_handler.h"
#include "context_scene.h"
#include "shoot.h"

extern ContextScene scene_;

MissileHandler::MissileHandler() {

}

MissileHandler::~MissileHandler() {

}

void MissileHandler::cast_missile(const Point& pos, const Point& focus) {
    if(Shoot::is_castable(last_cast_time_)) {
        ShootPtr shoot_ptr = std::make_shared<Shoot>(pos, focus, 20.f);  
        scene_.add_entity(shoot_ptr);
    }
}
