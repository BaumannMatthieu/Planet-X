#include "player.h"
#include "event_handler.h"

#include "shoot.h"
#include "context_scene.h"

extern EventHandler event_handler; 
extern ContextScene scene_;

Player::Player() : Ship(Rectangle(Vector2<float>(512.f, 384.f), 20.f, 20.f)),
                   stopped_(true), k_(0.5f) {
    mass_ = 5.0f;
	register_events();
}

Player::~Player() {

}

void Player::update() {
    if(!stopped_) {
        force_ = compute_arrive_force(center_mass_, focus_); 
    } else {
        force_ = -velocity_*k_;
    }
    Ship::update();
}

void Player::register_events() {
	event_handler.add(SDL_KEYDOWN, [this] (const SDL_Event& event) {
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_z) {
            stopped_ = false;
        }
	});

	event_handler.add(SDL_KEYUP, [this] (const SDL_Event& event) {
		if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_z) {
            stopped_ = true;
        }
	});

    event_handler.add(SDL_MOUSEMOTION, [this] (const SDL_Event& event) {
		if(event.type == SDL_MOUSEMOTION) {
            focus_ = Vector2<float>(center_mass_.x_ - 512 + event.motion.x,
                                    center_mass_.y_ - 384 + event.motion.y);
        }
	});

    event_handler.add(SDL_MOUSEBUTTONDOWN, [this] (const SDL_Event& event) {
        if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            if(Shoot::is_castable()) {
                ShootPtr shoot_ptr = std::make_shared<Shoot>(center_mass_, focus_, 20.f);  
                scene_.add_entity(shoot_ptr);
            }
        }
	});

}

