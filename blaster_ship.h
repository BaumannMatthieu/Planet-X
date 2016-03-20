#ifndef __BLASTER_SHIP_H__
#define __BLASTER_SHIP_H__

#include <memory>
#include "ship.h"
#include "scriptable.h"
#include "centered_path.h"

class Blaster : public Ship,
                public Scriptable {
	public:
		Blaster(const Rectangle& box);
		virtual ~Blaster();
        
        void init_missile_handler();

		void update();
	private:
       	float rad_focus_;
        CenteredPathPtr attacking_displacement_;
};

typedef std::shared_ptr<Blaster> BlasterPtr;

#endif
