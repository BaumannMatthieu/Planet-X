#ifndef __COLLISABLE_H__
#define __COLLISABLE_H__

#include <memory>
#include "rectangle.h"

class Collisable;
typedef std::shared_ptr<Collisable> CollisablePtr;

class Collisable {
    public:
        virtual bool compute(const Rectangle& rect) const = 0;

        static void vertice_box_collision(const CollisablePtr first, const CollisablePtr second);

        virtual bool isShip() const;
        virtual bool isShoot() const;

        virtual bool isBox() const;
        virtual bool isVertice() const;
};

#endif
