#ifndef __SHOOT_H__
#define __SHOOT_H__

#include "missile.h"
#include "movable.h"
#include "vertice.h"
#include <memory>

class Shoot : public Missile,
              public Movable,
              public Vertice {
    public:
        Shoot(const Point& position,
              const Point& focus,
              const float speed);
        virtual ~Shoot();
        
		void draw(SDL_Renderer* renderer);
		void update();

        void move();
    
    private:
        float speed_;
        float length_;
};

typedef std::shared_ptr<Shoot> ShootPtr;

#endif
