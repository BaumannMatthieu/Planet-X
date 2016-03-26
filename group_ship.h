#ifndef __GROUP_SHIP_H__
#define __GROUP_SHIP_H__

#include <memory>
#include <set>
#include "enemy_ship.h"

class GroupShips {
    public:
	typedef enum {
		SQUARE, 
		TRIANGLE
	} FormationType;

        GroupShips(EnemyShipPtr leader, const FormationType formation);
        virtual ~GroupShips();

        void add_ship(EnemyShipPtr ship);
    
        virtual const Point get_position_ship(const uint8_t id) const = 0;
    
    protected:
        std::set<EnemyShipPtr> ships_;
        EnemyShipPtr leader_;

	FormationType formation_;
};

typedef std::shared_ptr<GroupShips> GroupShipsPtr;

#endif
