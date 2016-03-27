#ifndef __MISSILE_HANDLER_H__
#define __MISSILE_HANDLER_H__

#include <memory>
#include "missile.h"
#include "laser_beam.h"

class MissileHandler {
    public:
        MissileHandler(const std::weak_ptr<Ship> caster, const SDL_Color& color, const Uint32 missile_cooldown=250, const Uint32 laser_cooldown=2000);
        virtual ~MissileHandler();

        void cast_missile(const Point& pos, const Vector2<float>& direction, const float speed);      	      void cast_laser(const Point& pos, const Vector2<float>& direction);
    	void stop_laser();
    private:
        std::weak_ptr<Ship> caster_;
        Uint32 last_cast_time_;
        
        SDL_Color color_;
        Uint32 missile_cooldown_;
	
	LaserBeamPtr laser_;
	Uint32 laser_cooldown_;
	bool laser_launching_;
};

typedef std::shared_ptr<MissileHandler> MissileHandlerPtr;
#endif
