#ifndef __SQUARE_GROUP_SHIP_H__
#define __SQUARE_GROUP_SHIP_H__

#include <memory>
#include <set>
#include "group_ship.h"

class SquareGroupShips : public GroupShips {
	public:
		SquareGroupShips(EnemyShipPtr leader);
		virtual ~SquareGroupShips();

        	const Point get_position_ship(const uint8_t id) const;
};

typedef std::shared_ptr<SquareGroupShips> SquareGroupShipsPtr;

#endif
