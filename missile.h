#ifndef __MISSILE_H__
#define __MISSILE_H__

class Missile : public Movable,
                public Renderable {
    public:
        Missile(const float degats, const Uint32 cooldown);
        virtual ~Missile();

		virtual void draw(SDL_Renderer* renderer) = 0;
		virtual void update() = 0;
    
    protected:
        float degats_;
        Uint32 cooldown_;
};

#endif
