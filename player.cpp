#include "player.h"
#include "event_handler.h"

#include "shoot.h"

extern EventHandler event_handler; 

Player::Player() : Ship(Rectangle(Vector2<float>(512.f, 384.f), 20.f, 20.f)), stopped_(true), ready_to_cast_(false), k_(0.5f) {
    mass_ = 5.0f;
    SDL_Color color_missile = {0, 255, 0, 255};
    missile_handler = std::make_shared<MissileHandler>(color_missile, 100);
	register_events();
}

Player::~Player() {

}

void Player::update() {
    if(!stopped_) {
        focus_ = Vector2<float>(center_mass_.x_ - 512 + mouse_.x_,
                                center_mass_.y_ - 384 + mouse_.y_);

        force_ = compute_arrive_force(center_mass_, focus_); 
    } else {
        force_ = -velocity_*k_;
    }

    if(ready_to_cast_) {
        missile_handler->cast_missile(center_mass_, focus_);            
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
            mouse_ = Vector2<float>(event.motion.x, event.motion.y);
            focus_ = Vector2<float>(center_mass_.x_ - 512 + event.motion.x,
                                    center_mass_.y_ - 384 + event.motion.y);
        }
	});

    event_handler.add(SDL_MOUSEBUTTONDOWN, [this] (const SDL_Event& event) {
        if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            missile_handler->cast_missile(center_mass_, focus_);            
            ready_to_cast_ = true;
        }
	});

    event_handler.add(SDL_MOUSEBUTTONUP, [this] (const SDL_Event& event) {
        if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
            ready_to_cast_ = false; 
        }
	});
}

bool Player::is_player() const {
    return true;
}
