#ifndef __SHOOT_H__
#define __SHOOT_H__

#include "missile.h"
#include "movable.h"
#include "vertice.h"
#include <memory>

class Shoot : public Missile,
              public Movable {
    public:
        Shoot(const std::weak_ptr<Ship> caster,
              const Point& position,
              const Point& focus,
              const float speed,
              const SDL_Color& color);
        virtual ~Shoot();
        
		void draw(SDL_Renderer* renderer);
		void update();
        bool compute(const Rectangle& rect) const;

        void move();

        bool isShoot() const;
        
        const Point& get_position() const;
        
        bool isVertice() const;
    
    private:
        Vertice vertice_;
        float speed_;
        float length_;
};

typedef std::shared_ptr<Shoot> ShootPtr;

#endif
