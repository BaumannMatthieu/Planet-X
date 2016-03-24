#include "missile.h"
#include "vector2.h"

Missile::Missile(const std::weak_ptr<Ship> caster, const uint8_t degats, const SDL_Color& color) : caster_(caster), degats_(degats), color_(color) {

}

bool Missile::is_castable(Uint32& last_cast_time, const Uint32 cooldown) {
    if(SDL_GetTicks() - last_cast_time >= cooldown) {
        last_cast_time = SDL_GetTicks();
        return true;
    }
    return false;
}

Missile::~Missile() {

}

const uint8_t Missile::get_damage() const {
    return degats_;
}

std::weak_ptr<Ship> Missile::get_caster() const {
    return caster_;
}
