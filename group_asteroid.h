#ifndef __GROUP_ASTEROID_H__
#define __GROUP_ASTEROID_H__

#include <memory>
#include <set>
#include "asteroid.h"
#include "renderable.h"

class GroupAsteroids : public Renderable {
    public:
        GroupAsteroids();
        ~GroupAsteroids();

        void add_asteroid(AsteroidPtr asteroid);
		
        void draw(SDL_Renderer* renderer);
    	void update();

    private:
        void update_cohesion();
        void update_separation();
        void update_alignement();
        
        std::set<AsteroidPtr> asteroids_;

        float cohesion_radius_;
        float separation_radius_;
};

#endif
