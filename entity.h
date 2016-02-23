#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <memory>
#include <SDL2/SDL.h>
#include "rectangle.h"
#include "movable.h"

class Entity : public Renderable, public Movable {
	public:
		Entity(const Rectangle& box);
		virtual ~Entity();

		virtual void draw(SDL_Renderer* renderer);
		virtual void move();

        const Rectangle& get_box() const;
	private:
		Rectangle box_;
		//image...
};

typedef std::shared_ptr<Entity> EntityPtr;

#endif
