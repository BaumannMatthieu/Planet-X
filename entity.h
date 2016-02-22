#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <memory>
#include <SDL2/SDL.h>
#include "rectangle.h"

class Entity : public Renderable {
	public:
		Entity();
		virtual ~Entity();

		virtual void draw(SDL_Renderer* renderer);
	private:
		Rectangle box_;
		//image...
};

typedef std::shared_ptr<Entity> EntityPtr;

#endif
