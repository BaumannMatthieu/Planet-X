#ifndef __SHIP_H__
#define __SHIP_H__

#include <memory>
#include "entity.h"
#include "rectangle.h"
#include "movable.h"
#include "scriptable.h"

class Ship : public Entity, public Movable, public Scriptable {
	public:
		Ship(const Rectangle& box);
		virtual ~Ship();

		virtual void move();
		virtual void update();
	private:
		uint8_t life_;	

       	float rad_focus_;
       	float rad_attack_;
       	float rad_near_;
};

typedef std::shared_ptr<Ship> ShipPtr;

#endif
