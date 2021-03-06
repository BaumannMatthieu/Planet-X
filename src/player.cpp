#include "../include/player.h"
#include "../include/event_handler.h"
#include "../include/event_data.h"

#include "../include/shoot.h"
#include "../include/laser_beam.h"

extern EventHandler event_handler; 

Player::Player() : Ship(Rectangle(Vector2<float>(WINDOW_WIDTH/2.f - 10.f, WINDOW_HEIGHT/2.f - 10.f), 20.f, 20.f)), stopped_(true), k_(0.5f) {
    mass_ = 5.0f;
    damage_ = 80;
    dir_ = box_.center_mass_;
	register_events();
}

void Player::init_missile_handler() {
    SDL_Color color_missile = {0, 255, 0, 255};
    std::weak_ptr<Ship> weak_from_this(shared_from_this());
    missile_handler = std::make_shared<MissileHandler>(weak_from_this, color_missile, 100);
}

Player::~Player() {

}

void Player::update() {
    if(!stopped_) {
        force_ = compute_arrive_force(box_.center_mass_, dir_); 
    } else {
        force_ = -velocity_*k_;
    }

    Ship::update();
}

void Player::register_events() {
	event_handler.add(SDL_KEYDOWN, [this] (const EventData& event_data) {
		const Uint8* state = event_data.get_key_state();
        if(state[SDL_SCANCODE_W]) {
            stopped_ = false;
            dir_ = Vector2<float>(box_.center_mass_.x_, box_.center_mass_.y_ - 100.f);
        }
	});

    event_handler.add(SDL_KEYDOWN, [this] (const EventData& event_data) {
		const Uint8* state = event_data.get_key_state();
        if(state[SDL_SCANCODE_S]) {
            stopped_ = false;
            dir_ = Vector2<float>(box_.center_mass_.x_, box_.center_mass_.y_ + 100.f);
        }
	});
    
    event_handler.add(SDL_KEYDOWN, [this] (const EventData& event_data) {
		const Uint8* state = event_data.get_key_state();
        if(state[SDL_SCANCODE_D]) {
            stopped_ = false;
            dir_ = Vector2<float>(box_.center_mass_.x_ + 100.f, box_.center_mass_.y_);
        }
	});

    event_handler.add(SDL_KEYDOWN, [this] (const EventData& event_data) {
		const Uint8* state = event_data.get_key_state();
        if(state[SDL_SCANCODE_A]) {
            stopped_ = false;
            dir_ = Vector2<float>(box_.center_mass_.x_ - 100.f, box_.center_mass_.y_);
        }
	});

	event_handler.add(SDL_KEYUP, [this] (const EventData& event_data) {
		const Uint8* state = event_data.get_key_state();
		if(!state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_A]) {
            stopped_ = true;
        }
	});

    event_handler.add(SDL_MOUSEMOTION, [this] (const EventData& event_data) {
		const Vector2<int> mouse_coord = event_data.get_mouse_coordinates();
        
        focus_ = Vector2<float>(box_.center_mass_.x_ - WINDOW_WIDTH/2 + mouse_coord.x_,
                                box_.center_mass_.y_ - WINDOW_HEIGHT/2 + mouse_coord.y_);
	});

    event_handler.add(SDL_MOUSEBUTTONDOWN, [this] (const EventData& event_data) {
        const Uint32 mouse_bitmask = event_data.get_mouse_bitmask();
        if(mouse_bitmask & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            cast_missile(focus_ - box_.center_mass_);
        }
	});

    event_handler.add(SDL_MOUSEBUTTONDOWN, [this] (const EventData& event_data) {
        const Uint32 mouse_bitmask = event_data.get_mouse_bitmask();
        if(mouse_bitmask & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
            cast_laser(focus_ - box_.center_mass_);

            if(missile_handler->laser_out_of_power()) {
                missile_handler->stop_laser();
            }
        }
    });

    event_handler.add(SDL_MOUSEBUTTONUP, [this] (const EventData& event_data) {
        const Uint32 mouse_bitmask = event_data.get_mouse_bitmask();
        if(!(mouse_bitmask & SDL_BUTTON(SDL_BUTTON_RIGHT))) {
            missile_handler->stop_laser();
	    }
    });
}

const Vector2<float>& Player::get_direction() const {
	return (focus_ - box_.center_mass_);
}

void Player::cast_missile(const Vector2<float>& direction) const {
	missile_handler->cast_missile(box_.center_mass_, direction, 20.f); 
}

void Player::cast_laser(const Vector2<float>& direction) const {
	missile_handler->cast_laser(box_.center_mass_, direction); 
}

bool Player::is_player() const {
    return true;
}
