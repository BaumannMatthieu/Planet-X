#include "../include/renderable.h"
#include "../include/player.h"

extern PlayerPtr player;

Renderable::Renderable() {

}

Renderable::~Renderable() {

}

void Renderable::draw_line(SDL_Renderer* renderer, const Vector2<float>& first_point, const Vector2<float>& second_point) {	
    Point player_pos = player->get_position();
    
    SDL_RenderDrawLine(renderer,
                       first_point.x_ - player_pos.x_ + WINDOW_WIDTH/2,
                       first_point.y_ - player_pos.y_ + WINDOW_HEIGHT/2,
			           second_point.x_ - player_pos.x_ + WINDOW_WIDTH/2,
                       second_point.y_ - player_pos.y_ + WINDOW_HEIGHT/2);
}
