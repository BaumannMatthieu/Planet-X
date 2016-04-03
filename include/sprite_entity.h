#ifndef __SPRITE_ENTITY_H__
#define __SPRITE_ENTITY_H__

#include <memory>
#include <SDL2/SDL.h>
#include "box.h"
#include "entity.h"
#include "avoidable.h"

class SpriteEntity : public Entity,
                     public Avoidable {
	public:
		SpriteEntity(const Rectangle& box);
		virtual ~SpriteEntity();

		void draw(SDL_Renderer* renderer);
		virtual void update() = 0;

        bool compute(const Rectangle& rect) const;
        
        const Point& get_position() const;
        void set_position(const Point& position);
    
        const Rectangle& get_box() const;

        bool isBox() const;

	protected:
        Box box_;
      	Point pos_sprite_;
		//image...
};

typedef std::shared_ptr<SpriteEntity> SpriteEntityPtr;

#endif
