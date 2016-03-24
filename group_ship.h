#ifndef __GROUP_SHIP_H__
#define __GROUP_SHIP_H__

#include <memory>
#include <set>
#include "enemy_ship.h"

class GroupShips {
    public:
        GroupShips(EnemyShipPtr leader);
        GroupShips(const std::set<EnemyShipPtr> ships, const EnemyShipPtr leader);
        virtual ~GroupShips();

        void add_ship(EnemyShipPtr ship);
        
    private:
        std::set<EnemyShipPtr> ships_;
        EnemyShipPtr leader_;
};

typedef std::shared_ptr<GroupShips> GroupShipsPtr;

#endif
