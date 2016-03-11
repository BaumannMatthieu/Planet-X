#ifndef __SHOOT_H__
#define __SHOOT_H__

#include "missile.h"
#include "movable.h"
#include "vertice.h"
#include <memory>

class Shoot : virtual public Missile,
              public Movable,
              public Vertice {
    public:
        Shoot(const Point& position, const Point& focus);
        virtual ~Shoot();
        
		void draw(SDL_Renderer* renderer);
		void update();

        virtual void move();
};

typedef std::shared_ptr<Shoot> ShootPtr;

#endif
