#ifndef __LIFE_UI_H__
#define __LIFE_UI_H__

#include <memory>
#include "rectangle.h"
#include "ship.h"

class LifeUi : public Renderable {
    public:
        LifeUi(const ShipPtr ship);
        virtual ~LifeUi();

		void draw(SDL_Renderer* renderer);
    	void update();

    private:
        float length_max_;
        float length_;
        Vector2<float> offset_;

        ShipPtr ship_;
        Rectangle rect_;
};

typedef std::shared_ptr<LifeUi> LifeUiPtr;

#endif
