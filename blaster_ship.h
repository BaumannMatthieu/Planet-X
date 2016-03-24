#ifndef __BLASTER_SHIP_H__
#define __BLASTER_SHIP_H__

#include <memory>
#include "enemy_ship.h"
#include "centered_path.h"

class Blaster : public EnemyShip {
	public:
		Blaster(const Point& position);
		virtual ~Blaster();
        
        void cast_missile(const Vector2<float>& direction) const;

    private:
        CenteredPathPtr attacking_displacement_;
};

typedef std::shared_ptr<Blaster> BlasterPtr;

#endif
