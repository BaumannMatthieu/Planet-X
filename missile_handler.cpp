#include "missile_handler.h"
#include "context_scene.h"
#include "shoot.h"
#include "laser_beam.h"

extern ContextScene scene;

MissileHandler::MissileHandler(const std::weak_ptr<Ship> caster, const SDL_Color& color, const Uint32 missile_cooldown, const Uint32 laser_cooldown) : caster_(caster),
						 color_(color),
						 missile_cooldown_(missile_cooldown),
						 laser_(nullptr),
                         laser_cooldown_(laser_cooldown),
						 laser_launching_(false) {

}

MissileHandler::~MissileHandler() {

}

void MissileHandler::cast_missile(const Point& pos, const Vector2<float>& direction, const float speed) {
    if(Shoot::is_castable(last_cast_time_, missile_cooldown_)) {
        ShootPtr shoot_ptr = std::make_shared<Shoot>(caster_, pos, direction, speed, color_);  
        scene.add_entity(shoot_ptr);
    }
}

void MissileHandler::cast_laser(const Point& pos, const Vector2<float>& direction) {
    if(LaserBeam::is_castable(last_laser_cast_time_, laser_cooldown_) && !laser_launching_) {
        laser_ = std::make_shared<LaserBeam>(caster_, pos, direction, color_);  
        scene.add_entity(laser_);
	
	    laser_launching_ = true;
	    last_laser_time_off_ = SDL_GetTicks();
    }
}

void MissileHandler::stop_laser() {
	if(laser_launching_) {
		scene.delete_entity(laser_);
		laser_launching_ = false;
	    last_laser_cast_time_ = SDL_GetTicks();
    }
}

bool MissileHandler::laser_out_of_power() {
    return LaserBeam::is_castable(last_laser_time_off_, 5000);
}

bool MissileHandler::laser_damage_time() {
    return LaserBeam::is_castable(last_laser_damage_time_, 100);
}
