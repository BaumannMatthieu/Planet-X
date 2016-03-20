#include "player.h"
#include "event_handler.h"
#include "event_data.h"

#include "shoot.h"

extern EventHandler event_handler; 

Player::Player() : Ship(Rectangle(Vector2<float>(WINDOW_WIDTH/2.f - 10.f, WINDOW_HEIGHT/2.f - 10.f), 20.f, 20.f)), stopped_(true), k_(0.5f) {
    mass_ = 5.0f;
    damage_ = 20;
    SDL_Color color_missile = {0, 255, 0, 255};
    missile_handler = std::make_shared<MissileHandler>(color_missile, 100);
    dir_ = box_.center_mass_;
	register_events();
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
            missile_handler->cast_missile(box_.center_mass_, focus_, 20.f);            
        }
	});
}

bool Player::is_player() const {
    return true;
}
