#ifndef __SHIP_H__
#define __SHIP_H__

#include <memory>
#include "sprite_entity.h"
#include "rectangle.h"
#include "movable.h"
#include "missile.h"
#include "missile_handler.h"

class Ship : public SpriteEntity,
             public Movable,
             public std::enable_shared_from_this<Ship> {
	public:
		Ship(const Rectangle& box);
		virtual ~Ship();

        virtual void init_missile_handler() = 0;

		void move();
		virtual void update();
        
        void take_damage(const MissilePtr missile);

        virtual bool is_player() const;
        bool isShip() const;
        bool isDead() const;
        const int16_t get_life() const;
        

        virtual void cast_missile(const Vector2<float>& direction) const = 0;
    
    protected:
        MissileHandlerPtr missile_handler;
        uint8_t damage_;

    private:
		int16_t life_;	
};

typedef std::shared_ptr<Ship> ShipPtr;

#endif
