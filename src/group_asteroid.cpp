#include "../include/group_asteroid.h"

GroupAsteroids::GroupAsteroids() : cohesion_radius_(100.f), separation_radius_(70.f) {

}

GroupAsteroids::~GroupAsteroids() {

}

void GroupAsteroids::add_asteroid(AsteroidPtr asteroid) {
    asteroids_.insert(asteroid);
}

void GroupAsteroids::draw(SDL_Renderer* renderer) {
    
}

void GroupAsteroids::update() {
    update_cohesion();
    update_separation();
    update_alignement();
}

void GroupAsteroids::update_cohesion() {
    for(auto& asteroid : asteroids_) {
        Point barycenter(0.f, 0.f);
        Point pos_asteroid = asteroid->get_position();
        uint16_t count = 0;
        for(auto& asteroid_neigh : asteroids_) {
            Point pos_asteroid_neigh = asteroid_neigh->get_position();
            Vector2<float> d = pos_asteroid_neigh - pos_asteroid;
            if(asteroid != asteroid_neigh && d.get_norme() < cohesion_radius_) {
                barycenter = barycenter + pos_asteroid_neigh;
                count++;
            }
        }
        if(count != 0) {
            barycenter = barycenter/count;
            asteroid->add_force(asteroid->compute_arrive_force(pos_asteroid,
                                                               barycenter)); 
        }
    }
}

void GroupAsteroids::update_separation() {
    for(auto& asteroid : asteroids_) {
        Vector2<float> sep(0.f, 0.f);
        Point pos_asteroid = asteroid->get_position();
        uint16_t count = 0;
        for(auto& asteroid_neigh : asteroids_) {
            Point pos_asteroid_neigh = asteroid_neigh->get_position();
            Vector2<float> d = pos_asteroid_neigh - pos_asteroid;
            if(asteroid != asteroid_neigh && d.get_norme() < separation_radius_) {
                sep = sep + d;
                count++;
            }
        }
        if(count != 0) {
            //sep = sep/count;
            asteroid->add_force(asteroid->compute_arrive_force(pos_asteroid,
                                                               pos_asteroid - sep)); 
        }
    }
}

void GroupAsteroids::update_alignement() {
    for(auto& asteroid : asteroids_) {
        Vector2<float> align(0.f, 0.f);
        Point pos_asteroid = asteroid->get_position();
        uint16_t count = 0;
        for(auto& asteroid_neigh : asteroids_) {
            Point pos_asteroid_neigh = asteroid_neigh->get_position();
            Vector2<float> d = pos_asteroid_neigh - pos_asteroid;
            if(asteroid != asteroid_neigh && d.get_norme() < cohesion_radius_) {
                Vector2<float> vel_neigh = asteroid_neigh->get_velocity();
                vel_neigh.normalize();
                align = align + vel_neigh;
                count++;
            }
        }
        if(count != 0) {
            align = align/count;
            asteroid->add_force(asteroid->compute_arrive_force(pos_asteroid,
                                                               pos_asteroid + align*500.f)); 
        }
    }
}



