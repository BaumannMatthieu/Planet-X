#ifndef __COLLISABLE_H__
#define __COLLISABLE_H__

#include <memory>
#include "rectangle.h"

class Collisable {
    public:
        virtual bool compute(const Rectangle& rect) const = 0;
};

typedef std::shared_ptr<Collisable> CollisablePtr;

#endif
