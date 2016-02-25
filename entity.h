#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <memory>
#include <SDL2/SDL.h>
#include "rectangle.h"

class Entity : public Renderable {
	public:
		Entity(const Rectangle& box);
		virtual ~Entity();

		virtual void draw(SDL_Renderer* renderer);
		virtual void update() = 0;

        	const Rectangle& get_box() const;
	protected:
		Rectangle box_;
		//image...
};

typedef std::shared_ptr<Entity> EntityPtr;

#endif
