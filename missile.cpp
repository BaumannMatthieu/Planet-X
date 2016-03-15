#include "missile.h"
#include "vector2.h"

Missile::Missile(const Point& focus, const float degats, const SDL_Color& color) : degats_(degats), color_(color), focus_(focus) {
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

