#ifndef __SPRITE_ENTITY_H__
#define __SPRITE_ENTITY_H__

#include <memory>
#include <SDL2/SDL.h>
#include "box.h"
#include "renderable.h"

class SpriteEntity : public Renderable,
                     public Box {
	public:
		SpriteEntity(const Rectangle& box);
		virtual ~SpriteEntity();

		void draw(SDL_Renderer* renderer);
		virtual void update() = 0;

	protected:
      	Point pos_sprite_;
		//image...
};

typedef std::shared_ptr<SpriteEntity> SpriteEntityPtr;

#endif
