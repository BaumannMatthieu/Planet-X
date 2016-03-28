#include <memory>
#include "laser_beam.h"
#include "ship.h"
#include "player.h"

LaserBeam::LaserBeam(const std::weak_ptr<Ship> caster, const Point& position, const Vector2<float>& direction, const SDL_Color& color) : Missile(caster, 20, color),
				 direction_(direction),
                                 length_(600.f),
                                 position_(position),
				 end_position_(position) {
	velocity_ = Vector2<float>(0.f, 0.f);
	
	direction_.normalize();
}

LaserBeam::~LaserBeam() {

}
        
void LaserBeam::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
	Renderable::draw_line(renderer, position_.center_mass_, end_position_.center_mass_);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void LaserBeam::update() {
	if(auto caster = caster_.lock()) {
		if(caster->is_player()) {
        		PlayerPtr player = std::dynamic_pointer_cast<Player>(caster);
			
			direction_ = player->get_direction();
			direction_.normalize();	
		}
	}

	move();
	end_position_.center_mass_ = position_.center_mass_ + direction_*length_;
}

void LaserBeam::move() {
	if(auto caster = caster_.lock()) {
		position_ = caster->get_position();		
	}
}

bool LaserBeam::compute(const Rectangle& rect) const {
	return  Rectangle::intersection(position_.center_mass_, end_position_.center_mass_, rect) ||
		Rectangle::intersection(position_.center_mass_, rect); 
}

const Point& LaserBeam::get_position() const {
	return position_.center_mass_;
}

bool LaserBeam::isVertice() const {
	return true;
}
