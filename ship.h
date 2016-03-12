#ifndef __SHIP_H__
#define __SHIP_H__

#include <memory>
#include "entity.h"
#include "rectangle.h"
#include "movable.h"

class Ship : public Entity,
             public Movable {
	public:
		Ship(const Rectangle& box);
		virtual ~Ship();

		void move();
		virtual void update();
	private:
		uint8_t life_;	

};

typedef std::shared_ptr<Ship> ShipPtr;

#endif
