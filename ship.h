#ifndef __SHIP_H__
#define __SHIP_H__

#include <memory>
#include "entity.h"
#include "rectangle.h"
#include "movable.h"

class Ship : public Entity, public Movable {
	public:
		Ship(const Rectangle& box);
		virtual ~Ship();

		virtual void move();
		virtual void update();
	protected:	
		virtual const Vector2<float> compute_force() const;
        const Vector2<float> compute_seek_force() const;
        const Vector2<float> compute_flee_force() const;
        const Vector2<float> compute_circular_displacement_force() const;
	private:
		uint8_t life_;	

        float rad_focus_;
        float rad_attack_;
        float rad_near_;
        bool t;
};

typedef std::shared_ptr<Ship> ShipPtr;

#endif
