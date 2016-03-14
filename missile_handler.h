#ifndef __MISSILE_HANDLER_H__
#define __MISSILE_HANDLER_H__

#include "missile.h"

class MissileHandler {
    public:
        MissileHandler();
        virtual ~MissileHandler();

        void cast_missile(const Point& pos, const Point& focus);        

    private:
        Uint32 last_cast_time_;
};

#endif
