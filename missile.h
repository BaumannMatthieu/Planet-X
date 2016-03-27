#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "primitive.h"
#include "entity.h"

class Ship;

class Missile : public Entity {
    public:
        Missile(const std::weak_ptr<Ship> caster, const uint8_t degats, const SDL_Color& color);
        virtual ~Missile();
        
	virtual void draw(SDL_Renderer* renderer) = 0;
	virtual void update() = 0;
        virtual bool compute(const Rectangle& rect) const = 0;

        static bool is_castable(Uint32& last_cast_time, const Uint32 cooldown);

        std::weak_ptr<Ship> get_caster() const;
        const uint8_t get_damage() const;

	bool is_missile() const;
    
    protected:
        std::weak_ptr<Ship> caster_; 
        uint8_t degats_;
                
        SDL_Color color_;
};

typedef std::shared_ptr<Missile> MissilePtr;

#endif
