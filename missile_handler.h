#ifndef __MISSILE_HANDLER_H__
#define __MISSILE_HANDLER_H__

#include <memory>
#include "missile.h"

class MissileHandler {
    public:
        MissileHandler(const std::weak_ptr<Ship> caster, const SDL_Color& color, const Uint32 cooldown=250);
        virtual ~MissileHandler();

        void cast_missile(const Point& pos, const Vector2<float>& direction, const float speed);        
    private:
        std::weak_ptr<Ship> caster_;
        Uint32 last_cast_time_;
        
        SDL_Color color_;
        Uint32 cooldown_;
};

typedef std::shared_ptr<MissileHandler> MissileHandlerPtr;
#endif
