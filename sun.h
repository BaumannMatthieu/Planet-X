#ifndef __SUN_H__
#define __SUN_H__

#include <memory>
#include "entity.h"
#include "rectangle.h"
#include "movable.h"

class Sun : public Entity {
	public:
		Sun();
		virtual ~Sun();

		virtual void update();

    private:
};

typedef std::shared_ptr<Sun> SunPtr;

#endif
