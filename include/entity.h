#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <memory>
#include "renderable.h"
#include "collisable.h"

class Entity : public Renderable, 
               public Collisable {
    public:
        Entity() { }
        virtual ~Entity() { }
                	    
        virtual void draw(SDL_Renderer* renderer) = 0;
		virtual void update() = 0;
        virtual bool compute(const Rectangle& rect) const = 0;

        virtual const Point& get_position() const = 0;
};

typedef std::shared_ptr<Entity> EntityPtr;

#endif
