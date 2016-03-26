#ifndef __TRIANGLE_GROUP_SHIP_H__
#define __TRIANGLE_GROUP_SHIP_H__

#include <memory>
#include <set>
#include "group_ship.h"

class TriangleGroupShips : public GroupShips {
	public:
		TriangleGroupShips(EnemyShipPtr leader);
		virtual ~TriangleGroupShips();

        	const Point get_position_ship(const uint8_t id) const;
};

typedef std::shared_ptr<TriangleGroupShips> TriangleGroupShipsPtr;

#endif
