#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include <memory>
#include "sprite_entity.h"
#include "rectangle.h"
#include "movable.h"

class Asteroid : public SpriteEntity,
                 public Movable {
	public:
		Asteroid();
		virtual ~Asteroid();

		void update();
        void move();

        bool is_asteroid() const;
    
    private:         
};

typedef std::shared_ptr<Asteroid> AsteroidPtr;

#endif
