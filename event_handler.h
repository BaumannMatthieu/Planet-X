#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include <functional>
#include <iostream>

typedef std::function<void(const SDL_Event&)> Callback;

class EventHandler {
	public:
		EventHandler();
		~EventHandler();
	
		void add(const SDL_EventType& event_type,
			 const Callback& callback);

		void handle(const SDL_Event& event);
	private:
		std::map<SDL_EventType, std::vector<Callback>> events_map_;
};

#endif
