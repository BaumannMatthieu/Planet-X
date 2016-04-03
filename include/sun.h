#ifndef __SUN_H__
#define __SUN_H__

#include <memory>
#include "sprite_entity.h"
#include "rectangle.h"

class Sun : public SpriteEntity {
	public:
		Sun();
		virtual ~Sun();

		virtual void update();

    private:
};

typedef std::shared_ptr<Sun> SunPtr;

#endif
