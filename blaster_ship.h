#ifndef __BLASTER_SHIP_H__
#define __BLASTER_SHIP_H__

#include <memory>
#include "enemy_ship.h"
#include "centered_path.h"

class Blaster : public EnemyShip {
	public:
		Blaster(const Rectangle& box);
		virtual ~Blaster();
        

    private:
        CenteredPathPtr attacking_displacement_;
};

typedef std::shared_ptr<Blaster> BlasterPtr;

#endif
