#include "missile.h"
#include "vector2.h"

Uint32 last_cast_time = 0;

Missile::Missile(const Point& focus, const Uint32& cooldown, const float degats, const SDL_Color& color) : cooldown_(cooldown), degats_(degats), color_(color), focus_(focus) {

}

bool Missile::is_castable() const {
    if(SDL_GetTicks() - last_cast_time >= cooldown_) {
        last_cast_time = SDL_GetTicks();
        return true;
    }
    return false;
}

Missile::~Missile() {

}

