#include "event_data.h"

EventData::EventData() {

}

EventData::~EventData() {

}

const Uint8* EventData::get_key_state() const {
    return key_state_;
}

const Vector2<int>& EventData::get_mouse_coordinates() const {
    return mouse_coordinates_;
}

const Uint32 EventData::get_mouse_bitmask() const {
    return mouse_bitmask_;
}

void EventData::update_event_queue() {
    key_state_ = SDL_GetKeyboardState(NULL);
    mouse_bitmask_ = SDL_GetMouseState(&(mouse_coordinates_.x_), &(mouse_coordinates_.y_));
}

