#ifndef __GAME_H__
#define __GAME_H__

#include <memory>
#include "event_registrable.h"
#include "event_handler.h"
#include "context_scene.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

class Game : public EventRegistrable {
	public:
		Game();
		~Game();

		void run();
	private:	
		void get_events();
		void update();
		void render();

		virtual void register_events();
	private:
		SDL_Window* window_;
		SDL_Renderer* renderer_;

		SDL_Event event_;
		
		bool running_;
		Uint32 time_per_frame_;
		Uint32 past_time_;
};

#endif
