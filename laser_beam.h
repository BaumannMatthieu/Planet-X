#ifndef __LASER_BEAM_H__
#define __LASER_BEAM_H__

#include "missile.h"
#include "movable.h"
#include "vertice.h"
#include <memory>

class LaserBeam : public Missile,
              	  public Movable {
    public:
        LaserBeam(const std::weak_ptr<Ship> caster,
              	  const Point& position,
                  const Vector2<float>& direction,
                  const SDL_Color& color);
        virtual ~LaserBeam();
        
	void draw(SDL_Renderer* renderer);
	void update();
        
	bool compute(const Rectangle& rect) const;

        void move();

        const Point& get_position() const;
	const Point& get_focus() const;       
 
        bool isVertice() const;
    
    private:
        Vector2<float> direction_;
        
	float length_;

        Vertice position_;
        Vertice end_position_;
};

typedef std::shared_ptr<LaserBeam> LaserBeamPtr;

#endif
