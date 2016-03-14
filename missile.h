#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "renderable.h"
#include "primitive.h"

class Missile : public Renderable {
    public:
        Missile(const Point& focus, const Uint32& cooldown, const float degats, const SDL_Color& color);
        virtual ~Missile();
        
		virtual void draw(SDL_Renderer* renderer) = 0;
		virtual void update() = 0;

        static bool is_castable(Uint32& last_cast_time);

    protected:
        float degats_;
        
        SDL_Color color_;

        Point focus_;
};

#endif
