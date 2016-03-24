#ifndef __ENEMY_SHIP_H__
#define __ENEMY_SHIP_H__

#include <memory>
#include "ship.h"
#include "scriptable.h"

class EnemyShip : public Ship,
                  public Scriptable {
    public:
        EnemyShip(const Rectangle& box);
        virtual ~EnemyShip();
        
        void init_missile_handler();

        const float get_max_avoidance_force() const;
		
        void update();
	protected:
       	float rad_focus_;

        float max_avoidance_force_;
};

typedef std::shared_ptr<EnemyShip> EnemyShipPtr;

#endif
