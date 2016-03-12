#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <memory>
#include <SDL2/SDL.h>
#include "box.h"

class Entity : public Renderable,
               public Box {
	public:
		Entity(const Rectangle& box);
		virtual ~Entity();

		void draw(SDL_Renderer* renderer);
		virtual void update() = 0;

	protected:
      	Point pos_sprite_;
		//image...
};

typedef std::shared_ptr<Entity> EntityPtr;

#endif
