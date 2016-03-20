#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "primitive.h"
#include "entity.h"

class Missile : public Entity {
    public:
        Missile(const Point& focus, const uint8_t degats, const SDL_Color& color);
        virtual ~Missile();
        
		virtual void draw(SDL_Renderer* renderer) = 0;
		virtual void update() = 0;
        virtual bool compute(const Rectangle& rect) const = 0;

        static bool is_castable(Uint32& last_cast_time, const Uint32 cooldown);

        const uint8_t get_damage() const;
    protected:
        uint8_t degats_;
                
        SDL_Color color_;

        Point focus_;
};

#endif
